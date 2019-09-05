#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "includes/QueryProtocol.h"

char *port_string = "1500";
unsigned short int port;
char *ip = "127.0.0.1";

#define BUFFER_SIZE 1000

int socketCreation(struct addrinfo *movie) {
    int sock_Id = socket(movie->ai_family, movie->ai_socktype, movie->ai_protocol);
    if (sock_Id < 0) {
        perror("Cannot create socket ID in RunQuery\n");
        exit(1);
    }
    int connection = connect(sock_Id, movie->ai_addr, movie->ai_addrlen);
    if (connection == -1) {
        perror("Cannot connect client to server\n");
        exit(1);
    }
    return sock_Id;
}

struct addrinfo *getAddrInfo(char *ip, char *port) {
    struct addrinfo res, *movie;
    memset(&res, 0, sizeof res);
    res.ai_family = AF_UNSPEC;
    res.ai_socktype = SOCK_STREAM;
    res.ai_flags = AI_PASSIVE;
    int address = getaddrinfo(ip, port, &res, &movie);
    if (address < 0) {
        perror("Cannot create address info struct\n");
        exit(1);
    }
    return movie;
}

void RunQuery(char *query, char *ip, char *port) {
  // Find the address
  struct addrinfo *movie = getAddrInfo(ip, port);
  // Create the socket
  int sock_Id = socketCreation(movie);
  char resp[1000];
  int len = read(sock_Id, resp, 999);
  resp[len] = '\0';
  if (len == -1 ||strlen(resp) != len) {
      perror("Error.");
      exit(1);
  }
  if (CheckAck(resp) == -1) {
      perror("Error in message.\n");
      exit(1);
  }
  // take in the acknowledgement from the serverrrrrrrr
  
  // Connect to the server
  int send_Id = send(sock_Id, query, strlen(query), 0);
  if (send_Id == -1) {
      perror("Cannot send message to server.\n");
      exit(1);
  }
  printf("Receiving response from server.\n");
  int num_responses;
  // 
  int received_Id = recv(sock_Id, &num_responses, sizeof(num_responses), 0);
  if (received_Id == -1) {
      perror("Error in receiving.");
      exit(1);
  }
  printf("The number of responses is %d\n", num_responses);
  int acknowledgement_ID = SendAck(sock_Id);
  if (acknowledgement_ID == -1) {
      perror("Cannot send acknowledgement.\n");
      exit(1);
  }
  // Do the query-protocol
  int i = num_responses;
  while (i > 0) {
      int nullTerm = recv(sock_Id, resp, 999, 0);
      resp[nullTerm] = '\0';
      printf("%s\n", resp);
      SendAck(sock_Id);
      i--;
  }
  // Close the connection
  close(sock_Id);
}
void destroyServer(char *ip, char *port) {
    struct addrinfo *movie = getAddrInfo(ip, port);
    int sock_Id = socketCreation(movie);
    int x = SendKill(sock_Id);
    if (x == -1) {
        perror("Cannot send kill from client to server\n");
        exit(1);
    }
    close(sock_Id);
    printf("client leaving server\n");
    exit(EXIT_SUCCESS);
}

void RunPrompt(char *ip, char *port) {
  char input[BUFFER_SIZE];

  while (1) {
    printf("Enter a term to search for, or q to quit: ");
    scanf("%s", input);

    printf("input was: %s\n", input);

    if (strlen(input) == 1) {
        if (input[0] == 'q') {
            printf("Thanks for playing! \n");
            return;
        }
        if ((input[0] == 'k' || input[0] == 'K')) {
	  destroyServer(ip, port);
        }
    }
    printf("\n\n");
    RunQuery(input, ip, port);
  }
}
int main(int argc, char **argv) {
  // Check/get arguments
  if (argc != 3) {
      perror("Please enter a new query.");
      exit(1);
  }
  // Get info from user and run query
  RunPrompt(argv[1], argv[2]);
  return 0;
}
