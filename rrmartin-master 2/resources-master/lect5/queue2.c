#include <stdio.h>
#include <stdlib.h>

#define SIZE 5

// Defining a circular queue based on an array. 

struct queueOfCustomers{
   char* customers[SIZE]; 
   int front;
   int rear;  ]
   int size; 
};

typedef struct queueOfCustomers QueueOfCustomers; 


// ===============================
// Queue Operation Prototypes
// ===============================


char* dequeue(QueueOfBooks*); 

void enqueue(char* newBook, QueueOfBooks*);

char* front(QueueOfBooks*); 

char* back(QueueOfBooks*); 

QueueOfBooks* create();

void destroy(QueueOfBooks*); 

// ===============================
// Queue Operation Implementation
// ===============================

char* dequeue(QueueOfBooks* queue){
	queue->bookInFront--; 
	return (queue->booknames[queue->bookInFront]); 
}

void enqueue(char* newBook, QueueOfBooks* queue){
	
	if (queue->bookInRear == queue->bookInFront && queue->bookInFront < SIZE){
		// Queue is full!!!
		printf("Can't add another book-- the queue is full!"); 
	}
	else{
		queue->bookInRear--; 
		if (queue->bookInRear < 0){
			queue->bookInRear = SIZE -1; 
		}
		queue->booknames[queue->bookInRear] = newBook; 
	}


	if (rear < SIZE){
   array[rear] = newElement;
   rear++;  
}
if (rear >= SIZE){
   rear = 0; 


}

int size(QueueOfBooks* queue){
	return(queue->bookInFront - queue->bookInRear ); 
}

char* front(QueueOfBooks* queue){

}

char* back(QueueOfBooks* queue){

}

QueueOfBooks* create(){
	// Allocate space on the heap
	QueueOfBooks* newQueue = 
		(QueueOfBooks*)malloc(sizeof(QueueOfBooks)); 

	// Initialize anything
	newQueue->bookInFront = 0; 
	newQueue->bookInRear = 0;

	// For purposes of demo, I'm doing this here. It's not always necessary: 
	int i=0; 
	for (i=0; i<SIZE; i++){
		newQueue->booknames[i] = ""; 
	}

	// Return pointer to new queue
	return newQueue; 
}

void destroy(QueueOfBooks* queue){

}


void printQueue(QueueOfBooks* books){
	printf("Printing the queue of books: \n"); 
	int i; 
	for (i=SIZE; i>=0; i--){
		if (i == books->bookInFront ){
			printf("------>");
		}
		if (i < SIZE){
			printf("\t[%d: %25s ]", i, books->booknames[i]);
		}
		if (i == books->bookInRear){
			printf("<------");
		}
		printf("\n"); 
	}
}

int main(){
	QueueOfBooks *queue = create(); 

	printQueue(queue);

	printf("\n\n");

	enqueue("Harry Potter", queue); 
	enqueue("War and Peace", queue); 
	enqueue("Hunger Games", queue); 
	enqueue("There's a Right Way", queue); 

	printQueue(queue);

	printf("\nThe next book we're reading: %s\n", dequeue(queue)); 

	printf("\n\n");
	printQueue(queue);

	printf("\nThe next book we're reading: %s\n", dequeue(queue)); 

	printf("\n\n");
	printQueue(queue);

	enqueue("Diary of a Wimpy Kid", queue); 

	printQueue(queue);

	enqueue("The Goldfinch", queue);

	printf("\n\n The size of the queue: %d\n\n", size(queue));


	destroy(queue);

}