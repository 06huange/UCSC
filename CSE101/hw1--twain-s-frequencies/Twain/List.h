/*
List.h
Header File for List.c
*/

#include<stdlib.h>
#include<stdio.h>


typedef struct ListObj* List;

typedef struct NodeObj* Node;
//Constructor
List newList(void);

//Functions
char* get(List L);

void insert(char* val, List L);

Node find(char* val, List L);

void update(Node N);

void sort(List L);

void swap(Node A, Node B);

void query(int k, List L, FILE* out);

void print(FILE* out, List L); 
