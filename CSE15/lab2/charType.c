/*
* Name:Kuo-Peng Huang
* UCSC ID:khuang53
* Class:CSE15
* Role:Extracts characters from each line of input file and places them into 4 different categories
* Assignment:Lab2
* Date:Oct 21,2019
*/



#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#define MAX_STRING_LENGTH 100

void extract_chars(char* s, char* a, char* d, char* p, char* w){
	int i=0, x=0, b=0, c=0, z=0;

	while(s[i]!='\0' && i<MAX_STRING_LENGTH){
		if( isspace(s[i])){
			w[x++]=s[i];
		}
		else if( isdigit(s[i])){
			d[b++]=s[i];
		}
		else if( isalpha(s[i])){
			a[c++]=s[i];
		}
		else if( ispunct(s[i])){
			p[z++]=s[i];
		}
		i++;
	}

	a[c]='\0';
	d[b]='\0';
	p[z]='\0';
	w[x]='\0';
}


//reads input file
int main(int argc, char* argv[]){
   FILE* in;        // handle for input file                  
   FILE* out;       // handle for output file                 
   char* line;      // string holding input line              
   char* alpha; // string holding all alphabets chars 
   char* punct; // punctuations
   char* digit; // numbers
   char* space; // white spaces
   int numline =1;


   // open input file for reading 
   if( (in=fopen(argv[1], "r"))==NULL ){
      printf("Unable to read from file %s\n", argv[1]);
      exit(EXIT_FAILURE);
   }

   // open output file for writing 
   if( (out=fopen(argv[2], "w"))==NULL ){
      printf("Unable to write to file %s\n", argv[2]);
      exit(EXIT_FAILURE);
   }

   // allocate strings line and alpha_num on the heap 
   line = calloc(MAX_STRING_LENGTH+1, sizeof(char) );
   alpha = calloc(MAX_STRING_LENGTH+1, sizeof(char) );
   punct = calloc(MAX_STRING_LENGTH+1, sizeof(char) );
   digit = calloc(MAX_STRING_LENGTH+1, sizeof(char) );
   space = calloc(MAX_STRING_LENGTH+1, sizeof(char) );
   assert( line!=NULL && alpha!=NULL && punct!=NULL && digit!=NULL && space!=NULL );

   // read each line in input file, extract alpha-numeric characters 
   while( fgets(line, MAX_STRING_LENGTH, in) != NULL ){
   	extract_chars(line, alpha, digit, punct, space);
   	fprintf(out, "line %d contains:\n", numline);

   	/*
   	int asize = sizeof(alpha)/sizeof(alpha[0]);
   	int dsize = sizeof(digit)/sizeof(digit[0]);
   	int psize = sizeof(punct)/sizeof(punct[0]);
   	int ssize = sizeof(space/sizeof(space[0]);
   	*/

   	int asize = strlen(alpha);
   	int dsize = strlen(digit);
   	int psize = strlen(punct);
   	int ssize = strlen(space);


   	//tests number of elements in alphabet array
   	if(asize>1){
   		fprintf(out, "%d alphabetic characters: %s\n", asize, alpha);
   	}
   	else{
   		fprintf(out, "%d alphabetic character: %s\n", asize, alpha);
   	}

   	//tests number of elements in number array
   	if(dsize>1){
   		fprintf(out, "%d numeric characters: %s\n", dsize, digit);
   	}
   	else{
   		fprintf(out, "%d numeric character: %s\n", dsize, digit);
   	}

   	//tests number of elements in punctuation array
   	if(psize>1){
   		fprintf(out, "%d punctuation characters: %s\n", psize, punct);
   	}
   	else{
   		fprintf(out, "%d punctuation character: %s\n", psize, punct);
   	}

   	//tests number of elements in white space array
   	if(ssize>1){
   		fprintf(out, "%d whitespace characters: %s\n", ssize, space);
   	}
   	else{
   		fprintf(out, "%d whitespace character: %s\n", ssize, space);
   	}

   	numline++;
   }

   // free heap memory 
   free(line);
   free(alpha);
   free(punct);
   free(digit);
   free(space);

   // close input and output files 
   fclose(in);
   fclose(out);

   return EXIT_SUCCESS;
}




//isspace, isdigit, isalpha, ispunct
//FILE* name = fopen(argv[1], "r");
//FILE* name = fopen(argv[2], "w");