#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include"List.h"
#include"BigInteger.h"

#define MAXCHAR 100000

int main(int argc, char* argv[]){
	FILE* in;
	FILE* out;
	char temp[50];
	char temp2[50];
	//check number of arguments
	if(argc != 3){
		printf("Usage: %s <input file> <output file>\n", argv[0]);
        exit(EXIT_FAILURE);
	}
	//open input file for reading
	if((in=fopen(argv[1], "r")) == NULL){
		printf("Unable to read from file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	//open output file for writing
	if( (out=fopen(argv[2], "w"))==NULL ){
      printf("Unable to write to file %s\n", argv[2]);
      exit(EXIT_FAILURE);
    }

    //fscanf(in, "%d", &numDigitA);
    fgets(temp, MAXCHAR, in);
    int valA = atoi(temp);
    char intA[valA];
    fgets(intA, MAXCHAR, in);
    //fscanf(in, "%s", &intA);
    
    fgets(temp2, MAXCHAR, in);
    int valB = atoi(temp2);
    char intB[valB];
    fgets(intB, MAXCHAR, in);
    //fscanf(in, "%d", &intB);

    /*
	char* intA = "5";
	char* intB = "7";
	*/

    BigInteger A = stringToBigInteger(intA);
    BigInteger B = stringToBigInteger(intB);

    //Output 1 : A
    printBigInteger(out, A);
    fprintf(out,"\n");
    //Output 2 : B
    printBigInteger(out, B);
    fprintf(out,"\n");
    //Output 3 : A + B
    printBigInteger(out, sum(A,B));
    fprintf(out,"\n");
    //Output 4 : A - B
    printBigInteger(out, diff(A,B));
    fprintf(out,"\n");
    //Output 5 : A - A
    printBigInteger(out, diff(A,A));
    fprintf(out,"\n");
    //Output 6 : 3A - 2B
    BigInteger tempA = sum(A,A);
    add(tempA, tempA, A);
    BigInteger tempB = sum(B,B);
    printBigInteger(out, diff(tempA,tempB));
    fprintf(out,"\n");
    //Output 7 : A x B
    printBigInteger(out, prod(A,B));
    fprintf(out,"\n");
    //Output 8 : A x A
    printBigInteger(out, prod(A,A));
    fprintf(out,"\n");
    //Output 9 : B x B
    printBigInteger(out, prod(B,B));
    fprintf(out,"\n");
    //Output 10 : 9A^4 + 16B^5
    BigInteger multiA = prod(A,A);
    BigInteger multiB = prod(B,B);
    //A^4
    for(int i=0; i<2; i++){
    	multiply(multiA, multiA, A);
    }
    //B^5
    for(int i=0; i<3; i++){
    	multiply(multiB, multiB, B);
    }

    BigInteger nine = stringToBigInteger("9");
    BigInteger sixteen = stringToBigInteger("16");

    multiply(multiA, multiA, nine);
    multiply(multiB, multiB, sixteen);

    printBigInteger(out, sum(multiA,multiB));

    fclose(in);
    fclose(out);
    freeBigInteger(&A);
    freeBigInteger(&B);
    A = NULL;
    B = NULL;
    return 0;
    exit(EXIT_SUCCESS);
}