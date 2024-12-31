//IntegerQueueTest
/*
*Name:Kuo-Peng Huang
*UCSC ID:khuang53
*Class:CSE15
*Assignment:pa4
*Role:tests integerQueueTest
*Date: Dec 3,2019
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"IntegerQueue.h"

int main(){
	IntegerQueue A = newIntegerQueue();
	IntegerQueue B = newIntegerQueue();
	//printf("Initial size of dictionary is: %d\n", length(A));
	enqueue(A, 1);
	enqueue(A, 2);
	enqueue(A, 3);
	printf("Size of interger Queue is: %d\n", length(A));

	printf("Deleted item is: %d\n", dequeue(A));
	printf("Item at top of the queue is: %d\n", peek(A));
	printf("Size of interger Queue is: %d\n", length(A));

	printf("is empty? %d\n",isEmpty(A));
	dequeueAll(A);
	printf("is empty? %d\n",isEmpty(A));
	printf("%d\n",length(A));

	enqueue(A, 5);
	enqueue(A, 3);
	enqueue(A, 9);
	enqueue(A, 7);
	enqueue(A, 8);
	dequeue(A);
	enqueue(B, 3);
	enqueue(B, 9);
	enqueue(B, 7);
	enqueue(B, 8);
	printf("are they equal? %d\n", equals(A,B));
	printf("Item at top of the queue is: %d\n", peek(A));
	printf("Size of interger Queue is: %d\n", length(A));

	printf("creating string...\n");
	char* str = IntegerQueueToString(A);
	printf("int string created\n");
	printf("IntegeQueue as string: %s\n", str);

	freeIntegerQueue(&A);


	/*
	insert(A,"1","a");
	insert(A,"2","b");
	insert(A,"3","c");
	insert(A,"4","d");
	insert(A,"5","e");
	printf("%s\n",lookup(A,"2"));
	printf("Size of dictionary after insert is: %d\n",size(A));
	delete(A,"2");
	printf("successfully deleted");
	printf("%s\n",lookup(A,"2"));
	char* str = DictionaryToString(A);
	printf("%s\n",str);
	makeEmpty(D);
	printf("%d\n",size(A));

	freeDictionary(&A);
	*/

	return(EXIT_SUCCESS);
}
