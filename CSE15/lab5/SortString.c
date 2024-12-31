//SortString.c
/*
# Name:Kuo-Peng Huang
# UCSC ID:khuang53
# Class:CSE15
# Role:Quicksorts strings
# Assignment:Lab5
# Date:Dec 5,2019
*/
#include<stdio.h>
#include<stdlib.h>
#include<stddef.h>
#include<string.h>
void printArray(FILE* out, char** A, int n){
   int i;
   for(i=0; i<n; i++){
      fprintf(out, "%s\n", A[i]);
   }
}
void swap(char** A, int i, int j){
	char* temp;
   	temp = A[i];
   	A[i] = A[j];
   	A[j] = temp;	
}
int Partition(char** A, int p, int r){
   int i, j;
   char* x = A[r];
   i = p-1;
   for(j=p; j<r; j++){
      if( strcmp(A[j],x) <= 0 ){
         i++;
         swap(A, i, j);
      }
   }
   swap(A, i+1, r);
   return(i+1);
}
void QuickSort(char** A, int p, int r){
	int q;
   	if( p<r ){
      q = Partition(A, p, r);
      QuickSort(A, p, q-1);
      QuickSort(A, q+1, r);
   }
}
int main(int argc, char* argv[]){
	FILE* in;
	FILE* out;
	int d;
   char temp[20];
	if( (in=fopen(argv[1], "r"))==NULL ){
      printf("Unable to read from file %s\n", argv[1]);
      exit(EXIT_FAILURE);
   }

   // open output file for writing 
   if( (out=fopen(argv[2], "w"))==NULL ){
      printf("Unable to write to file %s\n", argv[2]);
      exit(EXIT_FAILURE);
   }

   fscanf(in,"%d",&d);
   char** A = calloc(d,sizeof(char*));
   for(int i=0;i<d;i++){
   	
   	int count;
   	fscanf(in,"%s",temp);
      strcat(temp,"\0");
      //char z[20];
   	count = strlen(temp)+1;
   	A[i] = calloc(count,sizeof(char));
      strcpy(A[i],temp);
   }
   QuickSort(A, 0, d-1 );
   printArray(out, A, d);
   for(int i=0;i<d;i++){
   		free(A[i]);
   		A[i]=NULL;
   }
   free(A);
   A=NULL;
   fclose(in);
   fclose(out);
   return 1;
}