/*
List.c
LinkedList for sorting Twain's famous words
*/
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"List.h"

typedef struct NodeObj{
	char data[50];
	int freq;
	struct NodeObj* next;
} NodeObj;

typedef struct ListObj{
	Node head;
    int length;
} ListObj;

Node newNode(char* data){
	Node node = malloc(sizeof(NodeObj));
	//node->data = (char*)malloc(sizeof(data));
    strcpy(node->data,data);
    	node->freq = 1;
        node->next = NULL;
	return(node);
}

List newList(void){
	List L = malloc(sizeof(ListObj));
	L->head = NULL;
    L->length = 0;
	return(L);
} // Creates and returns a new empty List.

//Functions
char* get(List L){
    if(L->head == NULL){
    return NULL;
    }
    return L->head->data;
}

void insert(char* val, List L){
    Node n = newNode(val);
    n->next = L->head;
    L->head = n;
    L->length++;
    return;
}

Node find(char* val, List L){
    Node curr = L->head;
    //printf("%s %s\n",val,curr->data);
    while (curr!=NULL){
        if(strcmp(curr->data,val)==0) return curr;
        curr= curr->next;
    }
    return NULL;
}

void update(Node N){
    N->freq++;
    return;
}

//bubble sort
void sort(List L){
    if(L->head == NULL || L->head->next == NULL);
    else{
        Node base;
        for(int i=0; i<L->length-1;i++){
            for(base = L->head; base->next != NULL;base = base->next){
                if(base->freq < base->next->freq){
                    swap(base, base->next);
                }
                else{
                    if(base->freq == base->next->freq){
                        if(strcmp(base->data,base->next->data)>0){
                            swap(base, base->next);
                        }
                    }
                }
            }
            
        }
    }
}

void swap(Node A, Node B){
    char* tempStr = malloc(sizeof(A->data));
    int tempFreq;
    strcpy(tempStr, A->data);
    tempFreq = A->freq;
    strcpy(A->data,B->data);
    A->freq = B->freq;
    strcpy(B->data,tempStr);
    B->freq = tempFreq;
    free(tempStr);
}

void query(int k, List L, FILE* out){
    if(k > L->length-1){
        fprintf(out, "-\n");
    }
    else{
        Node curr = L->head;
        for(int i=0; i<k; i++){
            curr = curr->next;
        }
        fprintf(out, "%s %d\n",curr->data,curr->freq);
    }
}

void print(FILE* out, List L){
    printf("PRINTING");
	Node print;
	print = L->head;
	while(print != NULL){
		fprintf(out, "%s %d \n", print->data, print->freq);
		print = print->next;
	}
    return;
}
