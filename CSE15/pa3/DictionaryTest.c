#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Dictionary.h"

int main(){
	Dictionary A = newDictionary();
	printf("Initial size of dictionary is: %d\n",size(A));

	insert(A,"1","a");
	insert(A,"2","b");
	insert(A,"3","c");
	insert(A,"4","d");
	printf("%s\n",lookup(A,"2"));
	printf("Size of dictionary after insert is: %d\n",size(A));
	delete(A,"2");
	printf("successfully deleted");
	printf("%s\n",lookup(A,"2"));

	return(EXIT_SUCCESS);
}