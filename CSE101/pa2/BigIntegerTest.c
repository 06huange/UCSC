/*
Lex.c
Name: Eagle Huang
CruzID: khuang53
Assignment: PA1
*/

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"List.h"
#include"BigInteger.h"

int main(){
	char* strA = "15342";
	char* strB = "2458";

	BigInteger A = stringToBigInteger(strA);
	BigInteger B = stringToBigInteger(strB);

	//printList(stdout, A->L);
	//printList(stdout, B->L);
	printf("Sign of A is: %d\n", sign(A));
	printf("Sign of B is: %d\n", sign(B));

	negate(A);
	negate(B);
	printf("Opposite sign of A is: %d\n", sign(A));
	printf("Opposite sign of B is: %d\n", sign(B));

	printf("Compare value: %d\n", compare(A,B));

	printf("Equals value: %d\n", equals(A,B));

	printBigInteger(stdout, A);
	printBigInteger(stdout, B);

	BigInteger C = copy(A);
	BigInteger D = copy(B);
	printBigInteger(stdout, C);

	makeZero(A);
	makeZero(B);

	printBigInteger(stdout, A);
	printBigInteger(stdout, B);
	printBigInteger(stdout, C);
	printBigInteger(stdout, D);

	BigInteger E = newBigInteger();
	subtract(E,C,D);
	printBigInteger(stdout, E);
	normalize(E);
	printBigInteger(stdout, E);

	printf("negate\n\n");
	//negate(C);
	negate(D);
	printBigInteger(stdout, C);
	printBigInteger(stdout, D);
	subtract(E,C,D);
	printBigInteger(stdout, E);
	normalize(E);
	printBigInteger(stdout, E);

	printf("Addition operation\n");
	printBigInteger(stdout, C);
	printBigInteger(stdout, D);
	add(E,C,D);
	printBigInteger(stdout, E);
	normalize(E);
	printBigInteger(stdout, E);
	negate(C);
	printf("Addition operation\n");
	add(E,C,D);
	printBigInteger(stdout, E);
	normalize(E);
	printBigInteger(stdout, E);

	BigInteger summ = sum(C,D);
	printf("Summation of C and D is: ");
	printBigInteger(stdout, summ);
	printf("\n");
	BigInteger differ = diff(C,D);
	printf("Different of C and D is: ");
	printBigInteger(stdout, differ);

	char* strC = "135";
	char* strD = "-7";

	BigInteger x = stringToBigInteger(strC);
	BigInteger y = stringToBigInteger(strD);

	printf("Additional addition test\n");
	add(C,C,C);
	printBigInteger(stdout, C);

	//test multiply and prod
	printf("Multiply operation\n");
	printBigInteger(stdout, x);
	printBigInteger(stdout, y);
	makeZero(E);
	multiply(E,x,y);
	printBigInteger(stdout, E);

	BigInteger produ = prod(x,y);
	printBigInteger(stdout, produ);
	return 1;
}