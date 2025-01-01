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

#define MAX_STRING_SIZE 100
int main(int argc, char* argv[]){
	FILE* in;
	FILE* out;
	char line[MAX_STRING_SIZE];
	//int numLines = 0;
	int n = 0;

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

    while(fgets(line, MAX_STRING_SIZE, in) != NULL) n++;
    rewind(in);
    char* input[n];
    for (int i=0; i<n; i++){
    	fgets(line,MAX_STRING_SIZE,in);
    	input[i] = (char*) malloc(sizeof(line));
    	strcpy(input[i],line);
    }

    List sort = newList();
    //create sorted list

    append(sort,0);
    for (int i = 1; i < n; i++){
        moveFront(sort);

        while (index(sort) != -1){
            if (strcmp(input[get(sort)], input[i]) > 0){
                insertBefore(sort, i);
                break;
            }
            else{
                moveNext(sort);
            }
        }
        if (index(sort) == -1){
            append(sort,i);
        }
    }



    moveFront(sort);
    while(index(sort) != -1)
    {
        fprintf(out, input[get(sort)]);
        moveNext(sort);
    }
    //free heap memory
    
    //close input and output files
    for(int i = 0; i< n; i++){
        free(input[i]);
    }
    freeList(&sort);
    /* close files */
    fclose(in);
    fclose(out);
    return (0);

    return EXIT_SUCCESS;



}
