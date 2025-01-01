/*
List.c
Name: Eagle Huang
CruzID: khuang53
Assignment: PA1
*/

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"List.h"

typedef struct NodeObj{
	TYPE data;
	struct NodeObj* next;
	struct NodeObj* prev;
} NodeObj;

typedef NodeObj* Node;

typedef struct ListObj{
	Node front;
	Node back;
	Node cursor;
	int length;
	int index;
} ListObj;

//typedef struct ListObj* List;
// Constructors-Destructors ---------------------------------------------------
Node newNode(TYPE data){
	Node node = malloc(sizeof(NodeObj));
	node->data = data;
	node->next = NULL;
	node->prev = NULL;
	return(node);
}

void freeNode(Node* pN){
	if (pN != NULL && *pN != NULL){
		free(*pN);
		*pN = NULL;
	}
}

List newList(void){
	List L = malloc(sizeof(ListObj));
	L->front = NULL;
	L->back = NULL;
	L->cursor = NULL;
	L->length = 0;
	L->index = -1;
	return(L);
} // Creates and returns a new empty List.

void freeList(List* pL){
	if (pL != NULL && *pL != NULL){
		clear(*pL);
		free(*pL);
		*pL = NULL;
	}
}
// Frees all heap memory associated with *pL, and sets
 // *pL to NULL.
// Access functions -----------------------------------------------------------
int length(List L){
	if (L == NULL){
		printf("List Error: NULL\n");
		exit(EXIT_FAILURE);
	}
	return(L->length);
} // Returns the number of elements in L.
int index(List L){
	if (L == NULL){
		printf("List Error: NULL\n");
		exit(EXIT_FAILURE);
	}
	return(L->index);
} // Returns index of cursor element if defined, -1 otherwise.
TYPE front(List L){ // Returns front element of L. Pre: length()>0
	if (L == NULL){
		printf("List Error: NULL\n");
		exit(EXIT_FAILURE);
	}
	return(L->front->data);
}
TYPE back(List L){ // Returns back element of L. Pre: length()>0
	if (L == NULL){
		printf("List Error: NULL\n");
		exit(EXIT_FAILURE);
	}
	return(L->back->data);
}
TYPE get(List L){ // Returns cursor element of L. Pre: length()>0, index()>=0
	if (L == NULL){
		printf("List Error: NULL\n");
		exit(EXIT_FAILURE);
	}
	return(L->cursor->data);
}
/*
int equals(List A, List B){
	if(A->length == B->length){
		if(A->length == 0 && B->length == 0){
			return 1;
		}
		Node aP = A->front;
		Node bP = B->front;
		while(aP->next != NULL){
			if(aP->data != bP->data){
				return 0;
			}
			aP = aP->next;
			bP = bP->next;
		}
		return 1;
	}
	return 0;
} // Returns true (1) iff Lists A and B are in same
 // state, and returns false (0) otherwise.
 */

// Manipulation procedures ----------------------------------------------------
void clear(List L){
	if(L == NULL){
		printf("List Error: NULL\n");
		exit(EXIT_FAILURE);
	}
	while(L->back != NULL){
		deleteBack(L);
	}
} // Resets L to its original empty state.
void moveFront(List L){
	if(L == NULL){
		printf("List Error: NULL\n");
		exit(EXIT_FAILURE);
	}
	if( L != NULL){
		if (L->length > 0){
			L->cursor = L->front;
			L->index = 0;
		}
	}
} // If L is non-empty, sets cursor under the front element,
 // otherwise does nothing.
void moveBack(List L){
	if(L == NULL){
		printf("List Error: NULL\n");
		exit(EXIT_FAILURE);
	}
	if(L != NULL){
		if (L->length > 0){
			L->cursor = L->back;
			L->index = L->length-1;
		}
	}
} // If L is non-empty, sets cursor under the back element,
 // otherwise does nothing.
void movePrev(List L){
	if(L == NULL){
		printf("List Error: NULL\n");
		exit(EXIT_FAILURE);
	}
	if(L->cursor != NULL){
		if(L->index == 0){
			L->cursor = NULL;
			L->index = -1;
		}
		else{
			L->cursor = L->cursor->prev;
			L->index--;
		}
	}
} // If cursor is defined and not at front, move cursor one
 // step toward the front of L; if cursor is defined and at
 // front, cursor becomes undefined; if cursor is undefined
 // do nothing
void moveNext(List L){
	if(L == NULL){
		printf("List Error: NULL\n");
		exit(EXIT_FAILURE);
	}
	if(L->cursor != NULL){
		if(L->index == L->length -1){
			L->cursor = NULL;
			L->index = -1;
		}
		else{
			L->cursor = L->cursor->next;
			L->index++;
		}
	}
} // If cursor is defined and not at back, move cursor one
 // step toward the back of L; if cursor is defined and at
 // back, cursor becomes undefined; if cursor is undefined
 // do nothing
void prepend(List L, TYPE data){
	if(L == NULL){
		printf("List Error: NULL\n");
		exit(EXIT_FAILURE);
	}
	if(L->length > 0){
		Node newElement = newNode(data);
		newElement->next = L->front;
		L->front->prev = newElement;
		L->front = newElement;
	}
	else{
		Node newElement = newNode(data);
		L->front = L->back = newElement;
	}
	if(L->index != -1){
		L->index++;
	}
	L->length++;
} // Insert new element into L. If L is non-empty,
 // insertion takes place before front element.
void append(List L, TYPE data){
	if(L == NULL){
		printf("List Error: NULL\n");
		exit(EXIT_FAILURE);
	}
	if(L->length > 0){
		Node newElement = newNode(data);
		newElement->prev = L->back;
		L->back->next = newElement;
		L->back = newElement;
	}
	else{
		Node newElement = newNode(data);
		L->front = L->back = newElement;
	}
	L->length++;
} // Insert new element into L. If L is non-empty,
 // insertion takes place after back element.

void insertBefore(List L, TYPE data){
	if(L == NULL){
		printf("List Error: NULL\n");
		exit(EXIT_FAILURE);
	}
	if(L->index != -1){
		Node newElement = newNode(data);
		newElement->next = L->cursor;
		if(L->cursor != L->front){
			L->cursor->prev->next = newElement;
			newElement->prev = L->cursor->prev;
		}
		else{
			L->front = newElement;
		}
		L->cursor->prev = newElement;
		
		L->index++;
		L->length++;
	}

} // Insert new element before cursor.
 // Pre: length()>0, index()>=0
void insertAfter(List L, TYPE data){
	if(L == NULL){
		printf("List Error: NULL\n");
		exit(EXIT_FAILURE);
	}
	if(L->index != -1){
		Node newElement = newNode(data);
		newElement->prev = L->cursor;
		if(L->cursor != L->back){
			L->cursor->next->prev = newElement;
			newElement->next = L->cursor->next;
		}
		else{
			L->back = newElement;
		}
		L->cursor->next = newElement;
		L->length++;
	}

} // Insert new element after cursor.
 // Pre: length()>0, index()>=0

void deleteFront(List L){
	if(L == NULL){
		printf("List Error: NULL\n");
		exit(EXIT_FAILURE);
	}
	if(L->length > 0){
		if(L->cursor == L->front){
			L->cursor = NULL;
			L->index = -1;
		}
		if(L->index > 0){
			L->index--;
		}
		Node temp = L->front;
		L->front = L->front->next;
		freeNode(&temp);
		temp = NULL;
		L->length--;
	}
} // Delete the front element. Pre: length()>0

void deleteBack(List L)
{
    if(L == NULL){
        printf("List Error: NULL\n");
        exit(1);
    }
    if (L->length > 0){
        if (L->cursor == L->back){
            L->cursor = NULL;
            L->index = -1;
        }
        if (L->length > 1){
            Node temp = L->back;
            L->back = L->back->prev;
            freeNode(&temp);
        }
        else{
            Node temp = L->back;
            freeNode(&temp);
            L->back = NULL;
        }
        L->length--;
    }
}

void delete(List L)
{
    if(L == NULL){
        printf("List Error: NULL\n");
        exit(1);
    }
    if (L != NULL){
        if (L->cursor == L->front){
            deleteFront(L);
        }
        else if (L->cursor == L->back){
            deleteBack(L);
        }
        else{	
        	Node temp = L->cursor;
        	temp->prev->next = temp->next;
        	temp->next->prev = temp->prev;
            L->cursor = NULL;
            L->index = -1;
            L->length--;
            freeNode(&temp);
        }
    }
} // Delete cursor element, making cursor undefined.
 // Pre: length()>0, index()>=0

void set(List L, TYPE x){
	if(L == NULL){
        printf("List Error: NULL\n");
        exit(1);
    }
    if(L->length > 0 && L->index >= 0){
    	int key = L->index;
    	insertAfter(L, x);
    	delete(L);
    	moveFront(L);
    	for(int i=0; i<key; i++){
    		moveNext(L);
    	}
    }
}
// Other operations -----------------------------------------------------------
void printList(FILE* out, List L){
	if(L == NULL){
		printf("List Error: NULL\n");
		exit(EXIT_FAILURE);
	}
	Node print;
	print = L->front;
	while(print != NULL){
		fprintf(out,"%ld ", print->data);
		print = print->next;
	}
	fprintf(out,"\n");
} // Prints to the file pointed to by out, a
 // string representation of L consisting
 // of a space separated sequence of integers,
// with front on left.
List copyList(List L){
	if(L == NULL){
		printf("List Error: NULL\n");
		exit(EXIT_FAILURE);
	}
	List copy = newList();
	Node temp = L->front;
	while(temp != NULL){
		append(copy,temp->data);
		temp = temp->next;
	}
	return copy;
} // Returns a new List representing the same integer
 // sequence as L. The cursor in the new list is undefined,
// regardless of the state of the cursor in L. The state
// of L is unchanged.

