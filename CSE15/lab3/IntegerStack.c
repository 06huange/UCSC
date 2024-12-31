//------------------------------------------------------------
//	IntegerStack.c
// Implementation file for IntegerStack ADT
//---------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include"IntegerStack.h"

static const int InitialSize = 1;

typedef struct IntegerStackObj{
	int* item;
	int numItems;
	int physicalSize;
} IntegerStackObj;

/*
int arrayIndex(int listIndex){
	return listIndex-1;
}
*/

//doubles the size of array
void doubleItemArray(IntegerStack L){
	int i;
	int* newArray;
	int* oldArray = L->item;
	L->physicalSize *= 2;
	newArray = calloc(L->physicalSize, sizeof(int));
	for( i=0; i<(L->numItems); i++){
		newArray[i] = oldArray[i];
	}
	L->item = newArray;
	free(oldArray);
}

IntegerStack newIntegerStack(){
	IntegerStack L = malloc(sizeof(IntegerStackObj));
	L->item = calloc(InitialSize, sizeof(int));
	L->numItems = 0;
	L->physicalSize = InitialSize;
	return L;
}


//free memory from heap
void freeIntegerStack(IntegerStack* pL){
	if (pL!=NULL && *pL!=NULL){
		free ((*pL)->item);
		free(*pL);
		*pL=NULL;
	}
}

int isEmpty(IntegerStack L){
	if( L==NULL ){
      fprintf(stderr, "IntegerList Error: isEmpty() called on NULL IntegerList reference");
      exit(EXIT_FAILURE);
    }

    return (L->numItems == 0);
}

void push(IntegerStack L, int x){
   if( L==NULL ){
      fprintf(stderr, "IntegerList Error: add() called on NULL IntegerList reference");
      exit(EXIT_FAILURE);
   }

   // increase physical size of array if necessary
   if( (L->numItems)==(L->physicalSize) ){
      doubleItemArray(L);
   }

   
   L->item[(L->numItems)] = x;
   L->numItems++;
}

int pop(IntegerStack L){
	int i;
   if( L==NULL ){
      fprintf(stderr, "IntegerList Error: delete() called on NULL IntegerList reference");
      exit(EXIT_FAILURE);
   }
   i=L->item[L->numItems-1];
   L->numItems--;
   return i;
}

int peek(IntegerStack L){
	if( L==NULL ){
      fprintf(stderr, "IntegerList Error: delete() called on NULL IntegerList reference");
      exit(EXIT_FAILURE);
    }
	return L->item[L->numItems-1];
}
/*
void popAll(IntegerStack L){
	for (int i=0;i<L->numItems;i++){
		free(L->item[arrayIndex(i)]);
	}
}
*/
void popAll(IntegerStack L){
	if( L!=NULL){
		L->numItems=0;
	}
}


//other operatoins
void printIntegerStack(FILE* out, IntegerStack L){
   int i;
   if( L==NULL ){
      fprintf(stderr, "IntegerList Error: printIntegerList() called on NULL IntegerList reference");
      exit(EXIT_FAILURE);
   }

   for( i=L->numItems-1; i>=0; i--){
      fprintf(out, "%d ", L->item[(i)] );
   }
   fprintf(out, "\n");
}

int equals(IntegerStack L, IntegerStack R){
   int i, eq;
   if( L==NULL || R==NULL ){
      fprintf(stderr, "IntegerList Error: equals() called on NULL IntegerList reference");
      exit(EXIT_FAILURE);
   }

   eq = ( (L->numItems)==(R->numItems) );
   for( i=0; eq && i<(L->numItems); i++){
      eq = ( (L->item[(i)])==(R->item[(i)]) );
   }
   return eq;
}
