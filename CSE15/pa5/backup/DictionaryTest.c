//DictionaryTest.c

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Dictionary.h"


int main(){
   int i;
   Dictionary A;
   char* str;
   char* v;
   char* k = calloc(100, sizeof(char));

   // create a Dictionary and some pairs into it
   A = newDictionary();
   insert(A, "1","a");
   insert(A, "2","b");
   insert(A, "3","c");
   insert(A, "4","d");
   insert(A, "5","e");
   insert(A, "6","f");
   insert(A, "7","g");
   insert(A, "8","h");
   insert(A, "9","i");
   insert(A, "10","j");
   insert(A, "11","k");
   insert(A, "12","l");
   // print out the Dictionary
   str = DictionaryToString(A);

   printf("%s\n", str);
   free(str);

   // test lookup()
   for(i=0; i<=15; i++){
      sprintf(k, "%d", i);
      v = lookup(A, k);
      printf("k=%s, value=%s\n", k, v);
   }
   printf("\n");

   // insert(A, "2","f");  // causes duplicate key error

   // delete some pairs
   delete(A, "1");
   delete(A, "3");
   delete(A, "7");
   delete(A, "10");

   // print out the Dictionary
   str = DictionaryToString(A);
   printf("%s\n", str);
   free(str);

   // delete(A, "7");  // causes key not found error

   // check size
   printf("size(A) = %d\n", size(A));

   // make A empty, check size, print it out
   makeEmpty(A);
   printf("size(A) = %d\n", size(A));
   str = DictionaryToString(A);
   printf("%s\n", str);
   free(str);

   // free everything
   free(k);
   freeDictionary(&A);

   return EXIT_SUCCESS;
}
