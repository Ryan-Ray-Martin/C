#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>


#include "QueryProtocol.h"
#include "MovieSet.h"
#include "MovieIndex.h"
#include "DocIdMap.h"
#include "htll/Hashtable.h"
#include "QueryProcessor.h"
#include "FileParser.h"
#include "FileCrawler.h"

#define BUFFER_SIZE 1000

int Cleanup();

DocIdMap docs;
Index docIndex;

#define SEARCH_RESULT_LENGTH 1500

char movieSearchResult[SEARCH_RESULT_LENGTH];

void sigchld_handler(int s) {
  write(0, "Handling zombies...\n", 20);
  // waitpid() might overwrite errno, so we save and restore it:
  int saved_errno = errno;

  while (waitpid(-1, NULL, WNOHANG) > 0);

  errno = saved_errno;
}


void sigint_handler(int sig) {
  write(0, "Ahhh! SIGINT!\n", 14);
  Cleanup();
  exit(0);
}

int HandleConnections(int sock_fd) {
  int acceptId = accept(sock_fd, NULL, NULL);
  if (acceptId == -1) {
      perror("Cannot accept client on server.\n");
      exit(1);
  }
  printf("Accepted client.");
  return acceptId;
}

void Setup(char *dir) {
  struct sigaction sa;

  sa.sa_handler = sigchld_handler;  // reap all dead processes
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = SA_RESTART;
  if (sigaction(SIGCHLD, &sa, NULL) == -1) {
    perror("sigaction");
    exit(1);
  }

  struct sigaction kill;

  kill.sa_handler = sigint_handler;
  kill.sa_flags = 0;  // or SA_RESTART
  sigemptyset(&kill.sa_mask);

  if (sigaction(SIGINT, &kill, NULL) == -1) {
    perror("sigaction");
    exit(1);
  }

  printf("Crawling directory tree starting at: %s\n", dir);
  // Create a DocIdMap
  docs = CreateDocIdMap();
  CrawlFilesToMap(dir, docs);
  printf("Crawled %d files.\n", NumElemsInHashtable(docs));

  // Create the index
  docIndex = CreateIndex();

  // Index the files
  printf("Parsing and indexing files...\n");
  ParseTheFiles(docs, docIndex);
  printf("%d entries in the index.\n", NumElemsInHashtable(docIndex->ht));
}

int Cleanup() {
  DestroyOffsetIndex(docIndex);
  DestroyDocIdMap(docs);
  return 0;
}

int makeSocket(struct addrinfo *respPtr) {
    int sock_Fd = socket(respPtr->ai_family, respPtr->ai_socktype, respPtr->ai_protocol);
    if (sock_Fd < 0) {
        perror("Cannot make socket.\n");
        exit(1);
    }
    return sock_Fd;
}

void bindSocket (int sock_Fd, struct addrinfo *respPtr) {
    int bind_ID = bind(sock_Fd, respPtr->ai_addr, respPtr->ai_addrlen);
    if (bind_ID < 0) {
        perror("Cannot bind the socket with the server.\n");
        exit(1);
    }
    printf("Socket bind with server.\n");
}

void socketListen(int sock_Fd) {
    int listen_ID = listen(sock_Fd, 20);
    if (listen_ID == -1) {
        perror ("Cannot listen to the client on the server.\n");
        exit(1);
    }
    printf("Client listening.\n");
}

int socketAccept(int sock_Fd) {
    int accept_ID = accept(sock_Fd, NULL, NULL);
    if (accept_ID == -1) {
        perror("Cannot accept client on server.\n");
        exit(1);
    }
    printf("Client accepted.\n");
    return accept_ID;
}
void confirmation(int accept_ID) {
    int confirm_ID = SendAck(accept_ID);
    if (confirm_ID != 0) {
        perror("Confirmation from server to client failure.\n");
        exit(1);
    }
}

void checkConfirmation(char resp[]) {
    if (CheckAck(resp) != 0) {
        perror("Waiting for confirmation.\n");
        exit(1);
    }
}

void destroyServer(char resp[], int sock_Fd, int accept_ID) {
    if (CheckKill(resp) == 0) {
        printf("Destroy server.\n");
        close(sock_Fd);
        close(accept_ID);
        Cleanup();
        exit(1);
    }
}

struct addrinfo *makeAddressInfo(char* commandline) {
    struct addrinfo res;
    struct addrinfo *respPtr;
    memset(&res, 0, sizeof(res));
    res.ai_family = AF_UNSPEC;
    res.ai_socktype = SOCK_STREAM;
    res.ai_flags = AI_PASSIVE;
    int address = getaddrinfo(NULL, commandline, &res, &respPtr);
    if (address < 0) {
        perror("Cannot create addrinfo struct.\n");
        exit(1);
    }
    return respPtr;
}

void zeroMovies(int accept_ID, char resp[], int len) {
    int response = 0;
    int numOfResponses = send(accept_ID, &response, sizeof(response), 0);
    if (numOfResponses < 0) {
        perror("Cannot send server responses to client.\n");
        exit(1);
    }
    char *noMessages = "Query has no results.\n";
    len = recv(accept_ID, resp, len, 0);
    resp[len] = '\0';
    if (CheckAck(resp) != 0) {
        perror("Waiting for confirmation.\n");
        exit(1);
    }
    int checking = send(accept_ID, noMessages, sizeof(noMessages), 0);
    if (checking == -1) {
        perror("Cannot send message if null.\n");
        exit(1);
    }
}

void deliverMovieNum(SearchResultIter iter, int accept_ID) {
    int response = NumResultsInIter(iter);
    int numOfResponses = send(accept_ID, &response, sizeof(response), 0);
    if (numOfResponses < 0) {
        perror("Cannot deliver number of responses.\n");
        exit(1);
    }
    printf("Number sent.\n");
}

void deliverMovies(SearchResultIter iter, SearchResult output, int listen_ID, char resp[]) {
    SearchResultGet(iter, output);
    char destination[1000];
    CopyRowFromFile(output, docs, destination);
    int deliveryResult = send(listen_ID, destination, sizeof(destination)-1, 0);
    if (deliveryResult == -1) {
        perror("Cannot deliver movie to client.\n");
        exit(1);
    }
    int waitForAck = recv(listen_ID, resp, 999, 0);
    if (waitForAck == -1) {
        perror("Cannot receive acknowledgement.\n");
        exit(1);
    }
    resp[waitForAck] = '\0';
    char *placer = resp;
    if (CheckAck(placer) != 0) {
        perror("Cannot acknowledge1.\n");
        exit(1);
    }
}

void checkForArguments(int argc) {
    if (argc != 3) {
        perror("Invalid input.\n");
        exit(1);
    }
}

int main(int argc, char **argv) {
    // Get args
    checkForArguments(argc);
    Setup(argv[1]);
    //Setup(dir_to_crawl);

    // Step 1: Get address stuff
    struct addrinfo *respPtr = makeAddressInfo(argv[2]);
    // Step 2: Open socket
    int sock_Fd = makeSocket(respPtr);
    // Step 3: Bind socket
    bindSocket(sock_Fd, respPtr);
    // Step 4: Listen on the socket
    socketListen(sock_Fd);
    // Step 5: Handle the connections
    while(1) {
        int accept_ID = socketAccept(sock_Fd);
        if (!fork()) { //checkout
            close(sock_Fd);
            confirmation(accept_ID);
            printf("Waiting for client query.\n");
            char resp[1000];
            int len = recv(accept_ID, resp, 999, 0);
            resp[len] = '\0';
            if (len == -1) {
                perror("Cannot receive message.\n");
                exit(1);
            }
            SearchResult iter = FindMovies(docIndex, resp);
            if (iter == NULL) {
                zeroMovies(accept_ID, resp, len);
            }else {
                deliverMovieNum(iter, accept_ID);
                len = recv(accept_ID, resp, len, 0);
                resp[len] = '\0';
                checkConfirmation(resp);
                SearchResult output = (SearchResult) malloc(sizeof(SEARCH_RESULT_LENGTH));
                while (SearchResultIterHasMore(iter)) {
                    deliverMovies(iter, output, accept_ID, resp);
                }
                printf("Movies sent to client.\n");
                free(output);
                DestroySearchResultIter(iter);
            }
            close(accept_ID);
            exit(0);
        }
        close(sock_Fd);
        Cleanup();
        return 0;
    }
}
