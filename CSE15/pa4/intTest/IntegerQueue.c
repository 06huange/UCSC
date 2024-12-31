//IntegerQueueADT
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include"IntegerQueue.h"

typedef struct NodeObj* Node;

typedef struct NodeObj{
	int item;
	struct NodeObj* next;
}NodeObj;

typedef struct IntegerQueueObj* IntegerQueue;

typedef struct IntegerQueueObj{     
	int numItems;      // number of items in this IntegerQueue
	Node front;         // index of front element
	Node back;          // index of back element
}IntegerQueueObj;

//Constructor
Node newNode(int x){
	Node N = malloc(sizeof(NodeObj));
	N->item = x;
	N->next = NULL;
	return N;
}

IntegerQueue newIntegerQueue(){
	IntegerQueue Q = malloc(sizeof(IntegerQueueObj));
	//Q->numItems = 0;
   	Q->front = NULL;
   	Q->back = NULL;
   	return Q;
}

//Destructor
void freeNode(Node* pN){
	if(pN!=NULL && *pN!=NULL){
		free(*pN);
		*pN=NULL;
	}
}

void freeIntegerQueue(IntegerQueue* pQ){
	if (*pQ != NULL && pQ!= NULL){
		if(!isEmpty(*pQ)) dequeueAll(*pQ);
		free(*pQ);
		*pQ=NULL;
	}
}

//ADT operations
int isEmpty(IntegerQueue Q){
	if (Q==NULL){
		fprintf(stderr, "IntegerQueue Error: isEmpty() called on NULL "\
			"IntegerQueue reference");
		exit(EXIT_FAILURE);
	}

	return (Q->numItems==0);
}

int length(IntegerQueue Q){
	if (Q==NULL){
		fprintf(stderr, "IntegerQueue Error: length() called on NULL "\
			"IntegerQueue reference");
		exit(EXIT_FAILURE);
	}

	return (Q->numItems);
}

void enqueue(IntegerQueue Q, int x){
	Node N = newNode(x);
	if (Q->front==NULL){
		Q->front=Q->back=N;
	}
	else{
		Q->back->next=N;
		Q->back=N;
	}
	Q->numItems++;
}

int dequeue(IntegerQueue Q){
	int x;
	Node N;
	if (Q==NULL){
		fprintf(stderr, "IntegerQueue Error: dequeue() called on NULL "\
			"IntegerQueue reference");
		exit(EXIT_FAILURE);
	}

	x=Q->front->item;
	N=Q->front;

	if(Q->front==Q->back){
		Q->front = Q->back = NULL;
	}
	else{
		Q->front=Q->front->next;
	}
	Q->numItems--;
	free(N);
	return x;
}

int peek(IntegerQueue Q){
	if (Q==NULL){
		fprintf(stderr, "IntegerQueue Error: peek() called on NULL "\
			"IntegerQueue reference");
		exit(EXIT_FAILURE);
	}
	if( isEmpty(Q) ){
      fprintf(stderr, "IntegerQueue Error: cannot peek empty queue\n");
      exit(EXIT_FAILURE);
   	}

   	return Q->front->item;
}

void dequeueAll(IntegerQueue Q){
	if (Q==NULL){
		fprintf(stderr, "IntegerQueue Error: dequeueAll() called on NULL "\
			"IntegerQueue reference");
		exit(EXIT_FAILURE);
	}

	while(Q->front!=NULL){
		Node temp = Q->front;
		Q->front = temp->next;
		freeNode(&temp);
		temp = NULL;
	}
	Q->numItems = 0;
}

//Other Operations
int countChars(IntegerQueue Q){
	Node N = Q->front;
	int count = 0;
	while(N!=NULL){
		if(N->item<10){
			count += 2;
		}
		if(N->item>=10&&N->item<100){
			count += 3;
		}
		if(N->item>=100){
			count += 4;
		}
		N=N->next;
	}
	freeNode(&N);
	return count;
}

char* IntegerQueueToString(IntegerQueue Q){
	if (Q==NULL){
		fprintf(stderr, "IntegerQueue Error: IntegerQueueToString() called on NULL "\
			"IntegerQueue reference");
		exit(EXIT_FAILURE);
	}
	Node N = Q->front;
	int n = countChars(Q);
	char temp[5] = "";
	char* str = calloc(n+1,sizeof(char));
	while(N!=NULL){
		sprintf(temp,"%d",N->item);
		strcat(str,temp);
		strcat(str," ");
		N=N->next;
	}
	str[n] = '\0';
	free(N);
	return str;
}

int equals(IntegerQueue Q, IntegerQueue R){
	if(Q==NULL || R==NULL){
		fprintf(stderr, "IntegerQueue Error: equals() called on NULL IntegerQueue reference");
		exit(EXIT_FAILURE);
	}
	Node N = Q->front;
	Node P = R->front;
	if((Q->numItems)!=(R->numItems)){
		return 0;
	}
	while(N!=NULL){
		if(N->item != P->item){
			return 0;
		}
		N = N->next;
		P = P->next;
	}
   	return 1;

}