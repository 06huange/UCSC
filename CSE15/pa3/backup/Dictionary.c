//Dictionary.c

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

typedef DictionaryObj* Dictionary;

Dictionary newDictionary(){
	Dictionary D = malloc(sizeof(DictionaryObj));
	D->head = NULL;
	D->numPairs = 0;
	return D;
}

void freeDictionary(Dictionary* pD){
	if (pD!=NULL && *pD!=NULL){
		makeEmpty(*pD);
		free(*pD);
		*pD = NULL;
	}
}
//private functions
Node findKey(Dictionary D,char* k){
	while(D->head!=NULL){
		if(D->head->key==k){
			return D->head;
		}

		D->head = D->head->next;
	}
	return NULL;
}

int countChars(Dictionary D){
	int count = 0;
	while(D->head!=NULL){
		count += strlen(D->head->key) + strlen(D->head->value) + 2;
		D->head = D->head->next;
	}
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
	if (D==NULL){
		fprintf(stderr,"Dictionary Error: calling size() on NULL Dictionary reference\n");
		exit(EXIT_FAILURE);
	}
	while(D->head!=NULL){
		if(D->head->key==k){
			return D->head->value;
		}

		D->head = D->head->next;
	}
	return NULL;
}

void insert(Dictionary D, char* k, char* v){
	Node nu = newNode(k,v);
	Node temp;
	if(lookup(D,k)==NULL){
		if(D->head==NULL){
			D->head = nu;
		}
		else{
			temp = D->head;
			D->head = nu;
			nu->next = temp;
		}
		D->numPairs++;
	}
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
		Node nu = D->head;
		while(nu!=NULL && nu->next!=NULL){
			if(nu->next==findKey(D,k)){
				Node del = nu->next;
				nu->next = del->next;
				freeNode(&del);
			}
			nu=nu->next;
		}
	}
	D->numPairs--;
	
}

void makeEmpty(Dictionary D){
	while(D->head!=NULL && D->head->next!=NULL){
		Node temp = D->head;
		D->head = D->head->next;
		freeNode(&temp);
	}
}


//Other Operations
char* DictionaryToString(Dictionary D){
	char* str;
	int n;
	if (D==NULL){
		fprintf(stderr,"Dictionary Error: calling DictionaryToString() on NULL Dictionary reference\n");
		exit(EXIT_FAILURE);
	}

	n = countChars(D);
	str = calloc(n+1, sizeof(char));
	while(D->head!=NULL){
		strcat(str,D->head->key);
		strcat(str," ");
		strcat(str,D->head->value);
		strcat(str,"\n");
		D->head = D->head->next;
	}
	//strcat(str,'\0');
	return str;
}