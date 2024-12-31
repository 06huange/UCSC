//ArithmeticOperations.c
/*
# Name:Kuo-Peng Huang
# UCSC ID:khuang53
# Class:CSE15
# Role:Creates fptr_t type, pointer to a function, executes operations based on input file
# Assignment:Lab4
# Date:Nov 21,2019
*/

#include<stdio.h>
#include<stdlib.h>

typedef int (*fptr_t)(int, int);

int sum(int x, int y){
   return x+y;
}
 
int diff(int x, int y){
   return x-y;
}

int prod(int x, int y){
   return x*y;
}

int quot(int x , int y){
	return x/y;
}

int rem(int x, int y){
	return x%y;
}

int apply( fptr_t fp, int x, int y){
	return fp(x, y);
}

int compute(fptr_t fcn[5], int* A, int* idx, int n){
	fptr_t N;
	for(int i=0;i<n;i++){
		N=fcn[idx[i]];
		A[i+1] = apply(N,A[i],A[i+1]);
	}
	return A[n];
}


int main(int argc, char* argv[]){
	FILE* in;
	int ans;
	int n;
	fptr_t list[5] = {sum, diff, prod, quot, rem};

	//Opens in file for reading
	if( (in=fopen(argv[1], "r"))==NULL ){
      printf("Unable to read from file %s\n", argv[1]);
      exit(EXIT_FAILURE);
    }

    fscanf(in, "%d", &n);
    int* A = calloc(n+1,sizeof(int));
	int* idx = calloc(n,sizeof(int));
	for(int i=0;i<n;i++){
		fscanf(in, " %d", &idx[i]);
	}
	for(int i=0;i<n+1;i++){
		fscanf(in, " %d", &A[i]);
	}

   	ans = compute(list, A, idx, n);

   	printf("%d\n",ans);
   	free(A);
   	free(idx);
   	fclose(in);
   	return 0;

}