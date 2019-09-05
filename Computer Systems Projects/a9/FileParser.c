/*
 *  Created by Adrienne Slaughter
 *  edited by Ryan Martin
 *  CS 5007 Spring 2019
 *  Northeastern University, Seattle
 *
 *  This is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  It is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  See <http://www.gnu.org/licenses/>.
 */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <pthread.h>

#include "MovieIndex.h"
#include "FileParser.h"
#include "Movie.h"
#include "DocIdMap.h"
#include "MovieSet.h"
//  Only for NullFree; TODO(adrienne): NullFree should live somewhere else.

pthread_mutex_t lock;
pthread_mutex_t iter_lock;
HTIter globalIter;
Index globalIndex;
int checker = 0;

#define BUFFER_SIZE 1000
#define P_THREAD_SIZE 5
//=======================
// To minimize the number of files we have, I'm
// putting the private function prototypes for
// the fileparser here.

void IndexTheFile(char *file, uint64_t docId, Index index);

void* IndexTheFile_MT(void*);


/**
 * \fn Parses the files that are in a provided DocIdMap.
 * Builds an OffsetIndex
 */
int ParseTheFiles(DocIdMap docs, Index index) {
  HTIter iter = CreateHashtableIterator(docs);
  HTKeyValue kv;

  HTIteratorGet(iter, &kv);
  IndexTheFile(kv.value, kv.key, index);

  while (HTIteratorHasMore(iter) != 0) {
    HTIteratorGet(iter, &kv);
    IndexTheFile(kv.value, kv.key, index);
    HTIteratorNext(iter);
  }

  HTIteratorGet(iter, &kv);
  IndexTheFile(kv.value, kv.key, index);

  DestroyHashtableIterator(iter);

  return 0;
}

// Builds an OffsetIndex
void IndexTheFile(char *file, uint64_t doc_id, Index index) {
  FILE *cfPtr;

  if ((cfPtr = fopen(file, "r")) == NULL) {
    printf("File could not be opened\n");
    return;
  } else {
    char buffer[BUFFER_SIZE];
    int row = 0;

    while (fgets(buffer, BUFFER_SIZE, cfPtr) != NULL) {
      Movie *movie = CreateMovieFromRow(buffer);
      if (movie == NULL) {
        continue;
      }
      int result = AddMovieTitleToIndex(index, movie, doc_id, row);
      if (result < 0) {
        fprintf(stderr, "Didn't add MovieToIndex.\n");
      }
      row++;
      DestroyMovie(movie);  // Done with this now
    }
    fclose(cfPtr);
  }
}

// Takes a linkedlist of movies, and builds a hashtable based on the given field
// Builds a TypeIndex
Index BuildMovieIndex(LinkedList movies, enum IndexField field_to_index) {
  Index movie_index = CreateIndex();
  movie_index->movies = movies;

  LLIter iter = CreateLLIter(movies);
  Movie* cur_movie;
  LLIterGetPayload(iter, (void**)&cur_movie);

  AddMovieToIndex(movie_index, cur_movie, field_to_index);

  while (LLIterHasNext(iter)) {
    LLIterNext(iter);
    LLIterGetPayload(iter, (void**)&cur_movie);
    AddMovieToIndex(movie_index, cur_movie, field_to_index);
  }

  DestroyLLIter(iter);

  return movie_index;
}


// Takes a linkedlist of movies, and builds a hashtable based on the given field
// Adds a movie to a TypeIndex
Index AddToMovieIndex(Index movie_index,
                      LinkedList movies,
                      enum IndexField field_to_index) {
  LLIter iter = CreateLLIter(movies);
  Movie* cur_movie;
  LLIterGetPayload(iter, (void**)&cur_movie);

  AddMovieToIndex(movie_index, cur_movie, field_to_index);
  InsertLinkedList(movie_index->movies, cur_movie);

  while (LLIterHasNext(iter)) {
    LLIterNext(iter);
    LLIterGetPayload(iter, (void**)&cur_movie);
    AddMovieToIndex(movie_index, cur_movie, field_to_index);
    InsertLinkedList(movie_index->movies, cur_movie);
  }

  DestroyLLIter(iter);

  //  NullFree because the payloads now live in the HT
  DestroyLinkedList(movies, NullFree);

  return movie_index;
}

// Returns a LinkedList of Movie structs from the specified file
LinkedList ReadFile(const char* filename) {
  FILE *cfPtr;

  LinkedList movie_list = CreateLinkedList();

  if ((cfPtr = fopen(filename, "r")) == NULL) {
    printf("File could not be opened\n");
    DestroyLinkedList(movie_list, NULL);
    return NULL;
  } else {
    char row[BUFFER_SIZE];

    int i = 0;

    while (!feof(cfPtr)) {
      fgets(row, BUFFER_SIZE, cfPtr);
      i++;
      // Got the line; create a movie from it
      MoviePtr movie = CreateMovieFromRow(row);
      if (movie != NULL) {
        InsertLinkedList(movie_list, movie);
      }
    }
    fclose(cfPtr);
  }
  return movie_list;
}

void* IndexTheFile_MT(void* index) {
  
    HTKeyValue kv;
    FILE *cfPtr;
    // lock critical section of while loop
    pthread_mutex_lock(&lock);

    while (HTIteratorGet(globalIter, &kv) == 0 && checker == 0) {
      if (HTIteratorHasMore(globalIter) != 0) {
	HTIteratorNext(globalIter);
      }else {
	checker = 1;
      }
      pthread_mutex_unlock(&lock);
      	if ((cfPtr = fopen(kv.value, "r")) == NULL) {
	   printf("File could not be opened\n");
	   return NULL;
	} else {
	  char buffer[BUFFER_SIZE];
	  int row = 0;
	  while (fgets(buffer, BUFFER_SIZE, cfPtr) != NULL) {
	    Movie *movie = CreateMovieFromRow(buffer);
	    if (movie == NULL) {
	      continue;
	    }
	    // lock critical section of AddMovieTitleToIndex
	    pthread_mutex_lock(&iter_lock);
	    int result = AddMovieTitleToIndex(index, movie, kv.key, row);
	    pthread_mutex_unlock(&iter_lock);
	    if (result < 0) {
	      fprintf(stderr, "Didn't add MovieToIndex.\n");
	    }
	    row++;
	    DestroyMovie(movie);  // Done with this now
	  }
	  fclose(cfPtr);
        }
        pthread_mutex_unlock(&lock);
    
    }
    return NULL;
}

int ParseTheFiles_MT (DocIdMap docs, Index index){
    int i;
    pthread_t tid[P_THREAD_SIZE];
    globalIter = CreateHashtableIterator(docs);
    // creates five threads for indexing the files
    for (i=0 ;i < P_THREAD_SIZE; i++) {
      pthread_create(&tid[i], NULL, IndexTheFile_MT,(void*)index);
    }
    // joins the threads after the indexing
    for (i=0; i<P_THREAD_SIZE; i++) {
      pthread_join(tid[i], NULL);
    }
    DestroyHashtableIterator(globalIter);
    return 0;
   
}
