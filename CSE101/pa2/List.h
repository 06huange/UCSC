/*
List.h
Name: Eagle Huang
CruzID: khuang53
Assignment: PA1
*/

#include<stdlib.h>
#include<stdio.h>
#define TYPE long

typedef struct ListObj* List;
// Constructors-Destructors ---------------------------------------------------
List newList(void); 
void freeList(List* pL); 
// Access functions -----------------------------------------------------------
int length(List L); 
int index(List L); 
TYPE front(List L); 
TYPE back(List L); 
TYPE get(List L);
//TYPE equals(List A, List B);
// Manipulation procedures ----------------------------------------------------
void clear(List L);
void moveFront(List L);
void moveBack(List L); 
void movePrev(List L); 
void moveNext(List L); 
void prepend(List L, TYPE data); 
void append(List L, TYPE data); 
void insertBefore(List L, TYPE data); 
void insertAfter(List L, TYPE data); 
void deleteFront(List L); 
void deleteBack(List L); 
void delete(List L);
void set(List L, TYPE data);
// Other operations -----------------------------------------------------------
void printList(FILE* out, List L); 
List copyList(List L);