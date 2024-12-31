//Dictionary.c
/*
*Name:Kuo-Peng Huang
*UCSC ID:khuang53
*Class:CSE15
*Assignment:pa3
*Role:Implements Dictionar ADT
*Date: Nov 17,2019
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include"Dictionary.h"

typedef struct NodeObj{
	char* key;
	char* value;
	struct NodeObj* next;
}NodeObj;

typedef NodeObj* Node;

Node newNode(char* k, char* v){
	Node N = malloc(sizeof(NodeObj));
	assert(N!=NULL);
	N->key = k;
	N->value = v;
	N->next = NULL;
	return(N);
}

void freeNode(Node* pN){
	if(pN!=NULL && *pN!=NULL){
		free(*pN);
		*pN=NULL;
	}
}

typedef struct DictionaryObj{
	Node head;
	int numPairs;
} DictionaryObj;

Dictionary newDictionary(void){
	Dictionary D = malloc(sizeof(DictionaryObj));
	assert(D!=NULL);
	D->head = NULL;
	D->numPairs = 0;
	return D;
}

int isEmpty(Dictionary D){
	if (D==NULL){
		fprintf(stderr,"Dictionary Error: calling findKey() on NULL Dictionary reference\n");
		exit(EXIT_FAILURE);
	}
	return(D->numPairs == 0);
}

void freeDictionary(Dictionary* pD){
	if (pD!=NULL && *pD!=NULL){
		if(!isEmpty(*pD)) makeEmpty(*pD);
		free(*pD);
		*pD = NULL;
	}
}
//private functions
Node findKey(Dictionary D,char* k){
	//printf("first node of the list is: %s\n",D->head->key);
	Node N = D->head;
	//printf("first node of the list is: %s\n",N->key);
	if (D==NULL){
		fprintf(stderr,"Dictionary Error: calling findKey() on NULL Dictionary reference\n");
		exit(EXIT_FAILURE);
	}
	for( ; N!=NULL;N=N->next){
		if(strcmp(N->key,k)==0){
			return N;
		}
	}
	return NULL;
}

int countChars(Dictionary D){
	Node N = D->head;
	int count = 0;
	while(N!=NULL){
		count += strlen(N->key) + strlen(N->value) + 2;
		N = N->next;
	}
	freeNode(&N);
	return count;
}

//ADT Operations
int size(Dictionary D){
	if (D==NULL){
		fprintf(stderr,"Dictionary Error: calling size() on NULL Dictionary reference\n");
		exit(EXIT_FAILURE);
	}

	return D->numPairs;
}

char* lookup(Dictionary D, char* k){
	Node nu;
	if (D==NULL){
		fprintf(stderr,"Dictionary Error: calling lookup() on NULL Dictionary reference\n");
		exit(EXIT_FAILURE);
	}
	nu = findKey(D, k);
	return(nu==NULL ? NULL : nu->value);
}

void insert(Dictionary D, char* k, char* v){
	Node N = newNode(k,v);
	N->next = NULL;
	if (D==NULL){
		fprintf(stderr,"Dictionary Error: calling insert() on NULL Dictionary reference\n");
		exit(EXIT_FAILURE);
	}
	if(lookup(D,k)!=NULL){
		fprintf(stderr,"Dictionary Error: cannot insert duplicate keys:\n");
		exit(EXIT_FAILURE);
	}
	else if(D->head==NULL){
		D->head = N;
	}
	else{
		Node temp = D->head;
		while(temp->next!=NULL){
			temp=temp->next;
		}
		temp->next = N;
	}
	(D->numPairs++);
}

void delete(Dictionary D,char* k){

	if (D==NULL){
		fprintf(stderr,"Dictionary Error: calling delete() on NULL Dictionary reference\n");
		exit(EXIT_FAILURE);
	}
	if (lookup(D,k)==NULL){
		fprintf(stderr,"Dictionary Error: cannot delete non-existent key\n");
		exit(EXIT_FAILURE);
	}
	if(D->head == findKey(D,k)){
		Node temp = D->head;
		D->head = temp->next;
		freeNode(&temp);
	}
	else{
		Node N = D->head;
		while(N!=NULL && N->next!=NULL){
			if(N->next==findKey(D,k)){
				Node a = N;
				Node b = N->next;
				a->next = b->next;
				N = a;
				freeNode(&b);
				//freeNode(&a);
			}
			N=N->next;
		}
		freeNode(&N);
	}
	(D->numPairs)--;
}

void makeEmpty(Dictionary D){
	if (D==NULL){
		fprintf(stderr,"Dictionary Error: calling makeEpmty() on NULL Dictionary reference\n");
		exit(EXIT_FAILURE);
	}
	while(D->head!=NULL){
		Node temp = D->head;
		D->head = temp->next;
		freeNode(&temp);
		temp = NULL;
	}
	D->numPairs = 0;
}


//Other Operations
char* DictionaryToString(Dictionary D){
	char* str;
	int n;
	Node N = D->head;
	if (D==NULL){
		fprintf(stderr,"Dictionary Error: calling DictionaryToString() on NULL Dictionary reference\n");
		exit(EXIT_FAILURE);
	}

	n = countChars(D);
	str = calloc(n+1, sizeof(char));
	while(N!=NULL){
		strcat(str,N->key);
		strcat(str," ");
		strcat(str,N->value);
		strcat(str,"\n");
		N = N->next;
	}
	str[n] = '\0';
	return str;
}