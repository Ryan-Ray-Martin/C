#include <stdio.h>
#include <stdlib.h>


typedef struct customerNode CustomerNode; 

struct customerNode{
	char* customerName; 
	CustomerNode *nextNode; 
	CustomerNode *prevNode; 
};



struct queueOfCustomers{
   CustomerNode *front; 
   CustomerNode *rear; 
   int size; 
};

typedef struct queueOfCustomers QueueOfCustomers; 

// ===============================
// Queue Operation Prototypes
// ===============================


char* dequeue(QueueOfCustomers*); 

void enqueue(char* newCustomer, QueueOfCustomers*);

char* front(QueueOfCustomers*); 

char* back(QueueOfCustomers*); 

QueueOfCustomers* create();

void destroy(QueueOfCustomers*); 

// ===============================
// Queue Operation Implementation
// ===============================


char* dequeue(QueueOfCustomers* queue){

	if (queue->size == 0){
		printf("Queue is empty; can't dequeue anything\n"); 
		return ""; 
	}

	char *out = queue->front->customerName; 

	CustomerNode *first = queue->front; 

	// If it's the last element, there's nothing for front to point to.
	if (queue->size > 1){
		queue->front = queue->front->nextNode; 
		queue->front->prevNode = NULL; 
	}
	else{
		// There's one element left in the queue.
		queue->front = NULL; 
	}

	free(first); 

	queue->size--; 

	return out; 
}

void enqueue(char* newCustomer, QueueOfCustomers* queue){

	printf("Enqueuing %s\n", newCustomer); 
	// Create a new node
	CustomerNode *newNode = (CustomerNode*)malloc(sizeof(CustomerNode)); 
	newNode->customerName = newCustomer; 
	
	// set the next node to null
	newNode->nextNode = NULL; 
	// set the prev node to queue->rear
	newNode->prevNode = queue->rear; 

	if (queue->size == 0){
		// If it's the first in the queue, 
		// be sure to point the front ptr at it. 
		queue->front = newNode; 
	}
	else{
		// If it's not the first element,
		// set queue->rear->nextNode to new node
		queue->rear->nextNode = newNode;
	}

	// point rear at new node
	queue->rear = newNode; 

	queue->size++; 
}


char* front(QueueOfCustomers* queue){
  if (queue->size > 0){
    return queue->front->customerName;
  }
  

}
 

char* back(QueueOfCustomers* queue){
  if (queue->size > 0){
    return queue->rear->customerName;
  }
}
 

QueueOfCustomers* create(){
	// Allocate space on the heap
	QueueOfCustomers* newQueue = 
		(QueueOfCustomers*)malloc(sizeof(QueueOfCustomers)); 

	newQueue->front = NULL; 
	newQueue->rear = NULL; 
	newQueue->size = 0; 

	return newQueue; 

}

void destroy(QueueOfCustomers* queue){
	printf("Destroying the queue...\n"); 

	// Remove all nodes
	while (queue->size > 0){
		dequeue(queue); 
	}

	// Free the queue
	free(queue);
}

void printQueue(QueueOfCustomers *queue){
	CustomerNode* head = queue->front; 

	if (queue->size == 0){
		printf("The queue has no elements. \n"); 
		return; 
	}

	printf("The queue has %d elements. \n", queue->size);

	printf("FRONT: %s\n", head->customerName); 

	while(head != NULL){
		printf("%p\tPrevNode: %15p|%20s|\tNextNode: %15p\n", head, head->prevNode, head->customerName, head->nextNode); 
		head = head->nextNode;
	}

	printf("REAR: %s\n", queue->rear->customerName); 

 }



void printNode(CustomerNode *node){
	printf("Node: %p\t%15s\n", node, node->customerName); 
}


//===================

int main(){

	QueueOfCustomers *queue = create(); 

	printQueue(queue);

	printf("\n\n");

	enqueue("Ben Bitdiddle", queue); 
	enqueue("Joe Smith", queue); 
	enqueue("Alyssa Abernathy", queue); 
	enqueue("Charlie Carpenter", queue); 

	printQueue(queue);

	printf("The next customer is: %s \n", front(queue)); 

	printf("The last customer is: %s \n", back(queue)); 

	printf("Now helping customer: %s \n", dequeue(queue)); 

	printQueue(queue);

	destroy(queue); 


}
