// CS 5007, Northeastern University, Seattle
// Spring 2019
// Adrienne Slaughter
// edited by Ryan Martin 3/16/2019
//
// Inspired by UW CSE 333; used with permission.
//
// This is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published
//  by the Free Software Foundation, either version 3 of the License,
//  or (at your option) any later version.
// It is distributed in the hope that it will be useful, but
//  WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  General Public License for more details.

#include "LinkedList.h"
#include "LinkedList_priv.h"
#include "Assert007.h"

#include <stdio.h>
#include <stdlib.h>

LinkedList CreateLinkedList() {
  LinkedList list = (LinkedList)malloc(sizeof(LinkedListHead));
  if (list == NULL) {
    // out of memory
    return (LinkedList) NULL;
  }
  // Step 1.
  // Initialize the newly allocated record structure
  list -> num_elements = 0;
  list -> head = NULL;
  list -> tail = NULL;

  // Return newly allocated linked list
  return list;
}

int DestroyLinkedList(LinkedList list,
                      LLPayloadFreeFnPtr payload_free_function) {
  Assert007(list != NULL);
  Assert007(payload_free_function != NULL);

  // Step 2.
  // Free the payloads, as well as the nodes
  while (list->head != NULL) {
      payload_free_function(list->head->payload);
      LinkedListNodePtr temp = list-> head;
      list ->head = list->head->next;
      free(temp);
  }

  // free the list
  free(list);
  return 0;
}

unsigned int NumElementsInLinkedList(LinkedList list) {
  Assert007(list != NULL);
  // return number of elements in linked list
  return list->num_elements;
}

LinkedListNodePtr CreateLinkedListNode(void *data) {
    LinkedListNodePtr listnode =
      (LinkedListNodePtr)malloc(sizeof(LinkedListNode));
    if (listnode == NULL) {
        // Out of memory
        return NULL;
    }
    listnode->payload = data;
    listnode->next = NULL;
    listnode->prev = NULL;
    // return the linked list node
    return listnode;
}

int DestroyLinkedListNode(LinkedListNode *node) {
  Assert007(node != NULL);

  // destoys node, frees it and returns 0
  node->payload = NULL;
  node->next = NULL;
  node->prev = NULL;
  free(node);
  return 0;
}

int InsertLinkedList(LinkedList list, void *data) {
  Assert007(list != NULL);
  Assert007(data != NULL);
  LinkedListNodePtr new_node = CreateLinkedListNode(data);
  if (new_node == NULL) {
    return 1;
  }
  // if list is empty...
  if (list->num_elements == 0) {
    Assert007(list->head == NULL);
    Assert007(list->tail == NULL);
    list->head = new_node;
    list->tail = new_node;
    new_node->next = new_node->prev = NULL;
    list->num_elements = 1U;
    return 0;
  }
  // Step 3.
  // typical case; list has >=1 element
  list->head->prev = new_node;
  new_node->next = list->head;
  list->head = new_node;
  list->num_elements += 1;
  return 0;
}

int AppendLinkedList(LinkedList list, void *data) {
  Assert007(list != NULL);

  // Step 5: implement AppendLinkedList.  It's kind of like
  // InsertLinkedList, but add to the end instead of the beginning.

  // allocate new node

  LinkedListNodePtr node = (LinkedListNodePtr) malloc(sizeof(LinkedListNode));
  if (node == NULL) {
    return 1;
  }

  // initialize the payload
  node->payload = data;

  if (list->num_elements == 0) {
    Assert007(list->head == NULL);
    Assert007(list->tail == NULL);

    node->next = (struct ll_node *) (node->prev == NULL);
    list->head = list->tail = node;
    list->num_elements = 1U;
    return 0;
  }

  Assert007(list->head != NULL);
  Assert007(list->tail != NULL);
  node->next = NULL;
  node->prev = list->tail;
  list->tail->next = node;
  list->tail = node;
  list->num_elements += 1;

  return 0;
}

int PopLinkedList(LinkedList list, void **data) {
    Assert007(list != NULL);
    Assert007(data != NULL);

  // Step 4: implement PopLinkedList.  Make sure you test for
  // and empty list and fail.  If the list is non-empty, there
  // are two cases to consider: (a) a list with a single element in it
  // and (b) the general case of a list with >=2 elements in it.
  // Be sure to call free() to deallocate the memory that was
  // previously allocated by InsertLinkedList().


    // Cannot pop anything from a empty list
    if (list->num_elements == 0)
      return 0;

    // de-reference pointer
    *data = list->head->payload;

    LinkedListNodePtr temp = list->head;
    // if the linked list has one node
    if (list->num_elements == 1) {
        list->head = NULL;
        list->tail = NULL;
    } else {
      // if linked list has more than one node
        list->head = list->head->next;
        list->head ->prev = NULL;
    }
    list -> num_elements -= 1;

    free(temp);

    return 0;
}

int SliceLinkedList(LinkedList list, void **data) {
    Assert007(list != NULL);
    Assert007(data != NULL);

  // Step 6: implement SliceLinkedList.

    // Nothing to slice from a empty list
    if (list->num_elements == 0)
      return 1;

    // data is stored in linked list tail node

    *data = list->tail->payload;

    LinkedListNodePtr temp = list->tail;

    // linked list has only one node
    if (list->num_elements == 1) {
      list->head = NULL;
      list->tail = NULL;

      // linked list has at least two nodes
    } else {
      list->tail = list->tail->prev;
      list->tail->next = NULL;
    }

    list->num_elements -= 1;
    free(temp);

    return 0;
}

void SortLinkedList(LinkedList list, unsigned int ascending,
    LLPayloadComparatorFnPtr compare) {
    Assert007(list != NULL);
    if (list->num_elements <2) {
        return;
    }

    int swapped;
    do {
      LinkedListNodePtr curnode = list->head;
      swapped = 0;
      while (curnode->next != NULL) {
        // compare this node with the next; swap if needed
        int compare_result = compare(curnode->payload, curnode->next->payload);
        if (ascending) {
          compare_result *= -1;
        }
        if (compare_result < 0) {
          // swap
          void* tmp;
          tmp = curnode->payload;
          curnode->payload = curnode->next->payload;
          curnode->next->payload = tmp;
          swapped = 1;
        }
        curnode = curnode->next;
      }
    } while (swapped);
}

void PrintLinkedList(LinkedList list) {
    printf("List has %lu elements. \n", list->num_elements);
}


LLIter CreateLLIter(LinkedList list) {
  Assert007(list != NULL);
  Assert007(list->num_elements > 0);

  LLIter iter = (LLIter)malloc(sizeof(struct ll_iter));
  Assert007(iter != NULL);
  iter->list = list;
  iter->cur_node = list->head;
  return iter;
}

int LLIterHasNext(LLIter iter) {
  Assert007(iter != NULL);
  return (iter->cur_node->next != NULL);
}

int LLIterNext(LLIter iter) {
  Assert007(iter != NULL);

  // Step 7: if there is another node beyond the iterator, advance to it,
  // and return 0. If there isn't another node, return 1.

  if (LLIterHasNext(iter)) {
    iter->cur_node = iter->cur_node->next;
    return 0;
  }
  return 1;
}

int LLIterGetPayload(LLIter iter, void** data) {
  Assert007(iter != NULL);
  *data = iter->cur_node->payload;
  return 0;
}


int LLIterHasPrev(LLIter iter) {
  Assert007(iter != NULL);

  // returns if there is a previous node or not
  return (iter->cur_node->prev != NULL);
}

int LLIterPrev(LLIter iter) {
  Assert007(iter != NULL);
  // Step 8:  if there is another node beyond the iterator, go to it,
  // and return 0. If not return 1.
  if (LLIterHasPrev(iter)) {
    iter->cur_node = iter->cur_node->prev;
    return 0;
  }
  return 1;
}

int DestroyLLIter(LLIter iter) {
  Assert007(iter != NULL);
  iter->cur_node = NULL;
  iter->list = NULL;
  free(iter);
  return 0;
}

int LLIterInsertBefore(LLIter iter, void* payload) {
  Assert007(iter != NULL);
  if ((iter->list->num_elements <= 1) ||
      (iter->cur_node == iter->list->head)) {
    // insert item
    return InsertLinkedList(iter->list, payload);
  }

  LinkedListNodePtr new_node = CreateLinkedListNode(payload);
  if (new_node == NULL) return 1;
  new_node->next = iter->cur_node;
  new_node->prev = iter->cur_node->prev;
  iter->cur_node->prev->next = new_node;
  iter->cur_node->prev = new_node;

  iter->list->num_elements++;
  return 0;
}

int LLIterDelete(LLIter iter, LLPayloadFreeFnPtr payload_free_function) {
  Assert007(iter != NULL);

  // Step 9: implement LLIterDelete.  This is the most
  // complex function you'll build.  There are several cases
  // to consider:
  //
  // - degenerate case: the list becomes empty after deleting.
  // - degenerate case: iter points at head
  // - degenerate case: iter points at tail
  // - fully general case: iter points in the middle of a list,
  //                       and you have to "splice".
  //
  // Be sure to call the payload_free_function to free the payload
  // the iterator is pointing to, and also free any LinkedList
  // data structure element as appropriate.

  // free the current payload
  payload_free_function(iter->cur_node->payload);

  // pointer to the current node
  LinkedListNodePtr temp = iter->cur_node;


  // if the list only has one element
  if (iter->list->num_elements == 1) {
      iter->cur_node = NULL;
      iter->list->num_elements -= 1;
      iter->list->head = NULL;
      iter->list->tail = NULL;

      free(temp);
      return 1;
  }

  iter->list->num_elements -= 1;

  if (iter->cur_node->prev == NULL) {
    // @ head of linked list
      iter->cur_node = iter->cur_node->next;
      iter->list->head = iter->cur_node;
      iter->cur_node->prev = NULL;
  } else if (iter->cur_node->next == NULL) {
    // @ tail of linked list
      iter->cur_node = iter->cur_node->prev;
      iter->list->tail = iter->cur_node;
      iter->cur_node->next = NULL;
  } else {
    // @ middle of the linked list
      iter->cur_node->prev->next = iter->cur_node->next;
      iter->cur_node->next->prev = iter->cur_node->prev;
      iter->cur_node = iter->cur_node->next;
  }
  free(temp);

  return 0;
}
