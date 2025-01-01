/*
BigInterger.c
Name: Eagle Huang
CruzID: khuang53
Assignment: PA2
*/

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include"BigInteger.h"
#include"List.h"
#define BASE 1000000000
#define POWER 9
// Exported type -------------------------------------------------------------
// BigInteger reference type
typedef struct BigIntegerObj{
	List L;
	int sign;
}BigIntegerObj;
// Constructors-Destructors ---------------------------------------------------
// newBigInteger()
// Returns a reference to a new BigInteger object in the zero state.
BigInteger newBigInteger(){
	BigInteger N = malloc(sizeof(BigIntegerObj));
	N->L = newList();
	N->sign = 0;
	return(N);
}
// freeBigInteger()
// Frees heap memory associated with *pN, sets *pN to NULL.
void freeBigInteger(BigInteger* pN){
	if (pN != NULL && *pN != NULL){
		freeList(&(*pN)->L);
		free(*pN);
		*pN = NULL;
	}
}
// Access functions -----------------------------------------------------------
// sign()
// Returns -1 if N is negative, 1 if N is positive, and 0 if N is in the zero
// state.
int sign(BigInteger N){
	if(N == NULL){
		printf("BigInteger Error: NULL\n");
	}
	return N->sign;
}
// compare()
// Returns -1 if A<B, 1 if A>B, and 0 if A=B.
int compare(BigInteger A, BigInteger B){
	//If A and B are same length
	if(A == NULL || B == NULL){
		printf("BigInteger Error: NULL\n");
		exit(EXIT_FAILURE);
	}
	if(length(A->L) == length(B->L)){
		moveFront(A->L);
		moveFront(B->L);
		while(index(A->L) != -1){
			if(get(A->L) == get(B->L)){
				moveNext(A->L);
				moveNext(B->L);
			}
			else{
				if(get(A->L) > get(B->L)){
					if (A->sign < 0){
						return -1;
					}
					else if(A->sign > 0){
						return 1;
					}
				}
				else{
					if(B->sign < 0){
						return 1;
					}
					else if(B->sign > 0){
						return -1;
					}
				}
			}
		}
	}
	//Compare based on length
	else{
		if(length(A->L) > length(B->L)){
			if (A->sign < 0){
				return -1;
			}
			else if(A->sign > 0){
				return 1;
			}
		}
		else{
			if (B->sign < 0){
				return 1;
			}
			else if(B->sign > 0){
				return -1;
			}
		}
	}
	return 0;
}
// equals()
// Return true (1) if A and B are equal, false (0) otherwise.
int equals(BigInteger A, BigInteger B){
	if(A == NULL || B == NULL){
		printf("BigInteger Error: NULL\n");
		exit(EXIT_FAILURE);
	}
	if(sign(A) != sign(B)){
		return 0;
	}
	if(length(A->L) == length(B->L)){
		if(length(A->L) == 0){
			return 1;
		}
		moveFront(A->L);
		moveFront(B->L);
		while(index(A->L) != -1){
			if(get(A->L) != get(B->L)){
				return 0;
			}
			moveNext(A->L);
			moveNext(B->L);
		}
		return 1;
	}
	return 0;
}
// Manipulation procedures ----------------------------------------------------
// makeZero()
// Re-sets N to the zero state.
void makeZero(BigInteger N){
	if(N == NULL){
		printf("BigInteger Error: NULL\n");
		exit(EXIT_FAILURE);
	}
	N->sign = 0;
	clear(N->L);
}
// negate()
// Reverses the sign of N: positive <--> negative. Does nothing if N is in the
// zero state.
void negate(BigInteger N){
	if(N == NULL){
		printf("BigInteger Error: NULL\n");
		exit(EXIT_FAILURE);
	}
	if(sign(N) != 0){
		if(N->sign == 1){
			N->sign = -1;
		}
		else{
			N->sign = 1;
		}
	}
}

// BigInteger Arithmetic operations -----------------------------------------------
// stringToBigInteger()
// Returns a reference to a new BigInteger object representing the decimal integer
// represented in base 10 by the string s.
// Pre: s is a non-empty string containing only base ten digits {0,1,2,3,4,5,6,7,8,9}
// and an optional sign {+, -} prefix.
BigInteger stringToBigInteger(char* s){

	BigInteger B = newBigInteger();
	//precondition: non-empty, contains only base ten digits
	// assign SIGN
	int len = strlen(s);
	int strt = 1;
	int num = 0;
	if(len != 0){
		//check first char for + or -
		if(isdigit(s[0]) > 0){
			B->sign = 1;
			if(s[0] != '0'){
				long temp = s[0] - '0';
				append(B->L, temp);
				num = 1;
			}
			//len--;
		}
		else if(s[0] == '-' || s[0] == '+'){
			if(s[0] == '-'){
				B->sign = -1;
			}
			else{
				B->sign = 1;
			}
			//len--;
		}
		else{
			printf("BigInteger Error: Not Digit\n"); //change error message
			exit(EXIT_FAILURE);
		}

		//check whole string for digits
		for(int i=1; i<len; i++){
			if(isdigit(s[i]) == 0){
				if(s[i] == '\n'){
					len--;
					break;
				}
				printf("BigInteger Error: Not Digit\n"); //change error message
				exit(EXIT_FAILURE);
			}
			if(num == 0){
				if(s[i] == '0'){
					strt++;
				}
				else{
					num = 1;
				}
			}
		}
		for(int i=strt; i<len; i++){
			long temp = s[i] - '0';
			append(B->L, temp);
		}
	}
	else{
		printf("BigIntegerError: Empty String\n");
		exit(EXIT_FAILURE);
	}
	return B;
}
// copy()
// Returns a reference to a new BigInteger object in the same state as N.
BigInteger copy(BigInteger N){
	if(N == NULL){
		printf("BigInteger Error: NULL\n");
		exit(EXIT_FAILURE);
	}
	BigInteger copy = newBigInteger();
	moveFront(N->L);
	while(index(N->L) != -1){
		append(copy->L, get(N->L));
		moveNext(N->L);
	}
	copy->sign = N->sign;
	return copy;
}

// Helper Function ---------------------------------------------------------
void normalize(BigInteger A){
	moveBack(A->L);
	long carry = 0;
	long borrow = 0;
	while(index(A->L) != -1){
		//check for borrow
		if(borrow > 0){
			set(A->L, get(A->L) - borrow);
			borrow = 0;
		}
		//check for carry
		if(carry > 0){
			set(A->L, get(A->L) + carry); //carry = 1
			carry = 0;
		}
		if(get(A->L) == 0){
			if(index(A->L) == 0 && length(A->L) > 1){
				delete(A->L);
			}
		}
		else{
			if(get(A->L) > 0){
				if(get(A->L) >= BASE){
					long temp = get(A->L) % BASE;
					carry = get(A->L) / BASE;
					set(A->L, temp);
					if(index(A->L) == 0){
						prepend(A->L, carry);
						carry = 0;
					}
				}
				else{
					carry = 0;
				}
			}
			if(get(A->L) < 0){
				set(A->L, get(A->L) + BASE);
				borrow = (get(A->L)/10) + 1;
			}
		}
		movePrev(A->L);
	}
}
// add()
// Places the sum of A and B in the existing BigInteger S, overwriting its
// current state: S = A + B
void add(BigInteger S, BigInteger A, BigInteger B){
	if(A == NULL || B == NULL){
		printf("BigInteger Error: NULL\n");
		exit(EXIT_FAILURE);
	}
	BigInteger tempA = copy(A);
	BigInteger tempB = copy(B);
	moveBack(tempA->L);
	moveBack(tempB->L);
	makeZero(S);
	//one positive one negative
	if(tempA->sign != tempB->sign){
		negate(tempA);
		int key = compare(tempA,tempB);
		negate(tempA);
		if(key == -1){
			while(index(tempA->L) != -1 && index(tempB->L) != -1){
				long temp = get(tempB->L) - get(tempA->L);
				prepend(S->L, temp);
				movePrev(tempA->L);
				movePrev(tempB->L);
			}
			S->sign = 1; //might need fixing
		}
		else if(key == 1){
			while(index(tempA->L) != -1 && index(tempB->L) != -1){
				long temp = get(tempA->L) - get(tempB->L);
				prepend(S->L, temp);
				movePrev(tempA->L);
				movePrev(tempB->L);
			}
			S->sign = -1;
		}
		else if(key == 0){
			append(S->L, 0);
			S->sign = 0;
		}
		//if different length
		if(index(tempA->L) == -1 && index(tempB->L) != -1){
			while(index(tempB->L) != -1){
				prepend(S->L, get(tempB->L));
				movePrev(tempB->L);
			}
		}
		else if(index(tempB->L) == -1 && index(tempA->L) != -1){
			while(index(tempA->L) != -1){
				prepend(S->L, get(tempA->L));
				movePrev(tempA->L);
			}
		}
		//assign sign for D
		if(key < 0){
			S->sign = 1;
		}
		if(key > 0){
			S->sign = -1;
		}
	}
	//both positive or negative
	else{
		while(index(tempA->L) != -1 && index(tempB->L) != -1){
			long temp = get(tempA->L) + get(tempB->L);
			prepend(S->L, temp);
			movePrev(tempA->L);
			movePrev(tempB->L);
		}
		//assign sign
		if(tempB->sign == -1){
			S->sign = -1;
		}
		else if(tempB->sign == 1){
			S->sign = 1;
		}
		//if different length
		if(index(tempA->L) == -1 && index(tempB->L) != -1){
			while(index(tempB->L) != -1){
				prepend(S->L, get(tempB->L));
				movePrev(tempB->L);
			}
		}
		else if(index(tempB->L) == -1 && index(tempA->L) != -1){
			while(index(tempA->L) != -1){
				prepend(S->L, get(tempA->L));
				movePrev(tempA->L);
			}
		}
	}
	normalize(S);
	freeBigInteger(&tempA);
	freeBigInteger(&tempB);
}
// sum()
// Returns a reference to a new BigInteger object representing A + B.
BigInteger sum(BigInteger A, BigInteger B){
	if(A == NULL || B == NULL){
		printf("BigInteger Error: NULL\n");
		exit(EXIT_FAILURE);
	}
	BigInteger S = newBigInteger();
	add(S,A,B);
	return S;
}
// subtract()
// Places the difference of A and B in the existing BigInteger D, overwriting
// its current state: D = A - B
void subtract(BigInteger D, BigInteger A, BigInteger B){
	if(A == NULL || B == NULL){
		printf("BigInteger Error: NULL\n");
		exit(EXIT_FAILURE);
	}
	BigInteger tempA = copy(A);
	BigInteger tempB = copy(B);
	makeZero(D);
	int key = compare(tempA,tempB);
	moveBack(tempA->L);
	moveBack(tempB->L);
	//both positive or both negative
	if(tempA->sign == tempB->sign){
		if(key == -1){
			while(index(tempA->L) != -1 && index(tempB->L) != -1){
				long temp = get(tempB->L) - get(tempA->L);
				prepend(D->L, temp);
				movePrev(tempA->L);
				movePrev(tempB->L);
			}
			//assign sign
			D->sign = -1;
		}
		else if(key == 1){
			while(index(tempA->L) != -1 && index(tempB->L) != -1){
				long temp = get(tempA->L) - get(tempB->L);
				prepend(D->L, temp);
				movePrev(tempA->L);
				movePrev(tempB->L);
			}
			//assign sign
			D->sign = 1;
		}
		else if(key == 0){
			prepend(D->L, 0);
			D->sign = 0;
		}
		//if different length
		if(index(tempA->L) == -1 && index(tempB->L) != -1){
			while(index(tempB->L) != -1){
				prepend(D->L, get(tempB->L));
				movePrev(tempB->L);
			}
		}
		else if(index(tempB->L) == -1 && index(tempA->L) != -1){
			while(index(tempA->L) != -1){
				prepend(D->L, get(tempA->L));
				movePrev(tempA->L);
			}
		}
	}
	//one positive one negative
	else{
		while(index(tempA->L) != -1 && index(tempB->L) != -1){
			long temp = get(tempA->L) + get(tempB->L);
			prepend(D->L, temp);
			movePrev(tempA->L);
			movePrev(tempB->L);
		}
		//assign sign
		if(tempB->sign == -1){
			D->sign = 1;
		}
		if(tempA->sign == -1){
			D->sign = -1;
		}
		//if different length
		if(index(tempA->L) == -1 && index(tempB->L) != -1){
			while(index(tempB->L) != -1){
				prepend(D->L, get(tempB->L));
				movePrev(tempB->L);
			}
		}
		else if(index(tempB->L) == -1 && index(tempA->L) != -1){
			while(index(tempA->L) != -1){
				prepend(D->L, get(tempA->L));
				movePrev(tempA->L);
			}
		}
	}
	normalize(D);
	freeBigInteger(&tempA);
	freeBigInteger(&tempB);
}
// diff()
// Returns a reference to a new BigInteger object representing A - B.
BigInteger diff(BigInteger A, BigInteger B){
	if(A == NULL || B == NULL){
		printf("BigInteger Error: NULL\n");
		exit(EXIT_FAILURE);
	}
	BigInteger D = newBigInteger();
	subtract(D,A,B);
	return D;
}
// multiply()
// Places the product of A and B in the existing BigInteger P, overwriting
// its current state: P = A*B
void multiply(BigInteger P, BigInteger A, BigInteger B){
	if(A == NULL || B == NULL){
		printf("BigInteger Error: NULL\n");
		exit(EXIT_FAILURE);
	}
	BigInteger tempA = copy(A);
	BigInteger tempB = copy(B);
	makeZero(P);
	int n;
	if(tempA->sign == 0 || tempB->sign == 0){
		append(P->L, 0);
		P->sign = 1;
	}
	else{
		moveBack(tempA->L);
		moveBack(tempB->L);
		BigInteger tempInt = newBigInteger();
		for(int i=0; i<length(tempB->L); i++){
			for(n=0; n<length(tempA->L); n++){
				long temp = get(tempA->L) * get(tempB->L);
				prepend(tempInt->L, temp);
	
				movePrev(tempA->L);
			}
			for(int k=0; k<i; k++){
				append(tempInt->L, 0);
			}
			//normalize(tempInt);
			add(P,P,tempInt);
			makeZero(tempInt);
			movePrev(tempB->L);
			moveBack(tempA->L);
		}
		//normalize(P);
		//assign sign
		if((tempA->sign < 0) ^ (tempB->sign < 0)){
			P->sign = -1;
		}
		else if(tempA->sign == tempB->sign){
			P->sign = 1;
		}
		freeBigInteger(&tempInt);
	}
	freeBigInteger(&tempA);
	freeBigInteger(&tempB);
}
// prod()
// Returns a reference to a new BigInteger object representing A*B
BigInteger prod(BigInteger A, BigInteger B){
	if(A == NULL || B == NULL){
		printf("BigInteger Error: NULL\n");
		exit(EXIT_FAILURE);
	}
	BigInteger P = newBigInteger();
	multiply(P,A,B);
	return P;
}
// Other operations -----------------------------------------------------------
// printBigInteger()
// Prints a base 10 string representation of N to filestream out.
void printBigInteger(FILE* out, BigInteger N){
	if(N == NULL){
		printf("BigInteger: NULL\n");
		exit(EXIT_FAILURE);
	}
	moveFront(N->L);
	if(sign(N) == -1){
		fprintf(out,"-");
	}
	while(index(N->L) != -1){
		fprintf(out,"%ld", get(N->L));
		moveNext(N->L);
	}
	fprintf(out,"\n");
}
