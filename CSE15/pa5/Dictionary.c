//-----------------------------------------------------------------------------
//   Name: Kuo-Peng Huang
//   UCSC ID: khuang53
//   Class: CSE15
//	 Assignment:pa5
//   Date: Dec 6,2019
//   Role: Create the Dictionary ADT in C using hashtable
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include"Dictionary.h"

// Setting a constant for the hashtable
const int tableSize=101;

// NodeObj
typedef struct NodeObj
{
   char* value;
   char* key;
   struct NodeObj* next;
}

NodeObj;

// Node
typedef NodeObj* Node;

// newNode()
// constructor of the Node type
Node newNode(char* k, char* v) 
{
   Node N = malloc(sizeof(NodeObj)); //It should be Obj to have the right spacing
   assert(N!=NULL);
   N->key = k;
   N->value = v;
   N->next = NULL;
   return(N);
}

// freeNode()
// destructor for the Node type
void freeNode(Node* pN)
{
   if( pN!=NULL && *pN!=NULL ){
      free(*pN);
      *pN = NULL;
   }
}

// Dictionary object
typedef struct DictionaryObj
{
   Node *table; //USING HASHTABLE
   int numItems;
}

DictionaryObj;

// newDictionary()
// constructor for the Dictionary type
Dictionary newDictionary()
{
   Dictionary D = malloc(sizeof(DictionaryObj)); //AGAIN Use Obj for right spacing
   assert(D != NULL);
   D->table = calloc(tableSize, sizeof(NodeObj)); // Same thing applies
   assert(D->table != NULL);
   D->numItems = 0;
   return D;
}

// free Method()
// destructor for the Dictionary type
void freeDictionary(Dictionary* pD)
{
   if( pD!=NULL && *pD!=NULL )
   {
      //if( !isEmpty(*pD) ) makeEmpty(*pD);
   	  makeEmpty(*pD);
      free((*pD)->table); //Free up the table along with the dictionary.
      free(*pD);
      *pD = NULL;
   }
}

// rotate_left()
// rotate the bits in an unsigned int
unsigned int rotate_left(unsigned int value, int shift) {
 int sizeInBits = 8*sizeof(unsigned int);
 shift = shift & (sizeInBits - 1);
 if ( shift == 0 )
 return value;
 return (value << shift) | (value >> (sizeInBits - shift));
}


// pre_hash()
// turn a string into an unsigned int
unsigned int pre_hash(char* input) {
 unsigned int result = 0xBAE86554;
 while (*input) {
 result ^= *input++;
 result = rotate_left(result, 5);
 }
 return result;
}

// hash()
// turns a string into an int in the range 0 to tableSize-1
int hash(char* key){
 return pre_hash(key)%tableSize;
}


int isEmpty(Dictionary D)
{
   if( D == NULL )
   {
      fprintf(stderr, 
              "Dictionary Error: calling isEmpty() on NULL Stack reference\n");
      exit(EXIT_FAILURE);
   }
   return(D->numItems == 0);
}


int size(Dictionary D)
{
   return D->numItems;
}


char* lookup(Dictionary D, char* x)
{
   if(D == NULL)
   {
      fprintf(stderr, "Dictionary Error: calling lookup() on NULL Dictionary\n");
      exit(EXIT_FAILURE);
   }

   Node N = D->table[hash(x)]; //Put the char into the hash spot

   while( N != NULL)
   {
      if(strcmp(N->key, x) == 0)
      {
         return N->value;
      }
      N = N->next;
   }
   return (NULL);
}

void insert(Dictionary D, char* k, char* v)
{
   Node N = newNode(k,v); //Create the new Node we will insert.
   int h = hash(k); //Set the Hash

      if( D == NULL)
      {
         fprintf(stderr, "Dictionary Error: calling insert() on NULL Dictionary reference\n");
         exit(EXIT_FAILURE);
      }

      if( lookup(D, k) != NULL )
      {
         fprintf(stderr, "Dictionary Error: cannot insert duplicate keys:\n");
         exit(EXIT_FAILURE);
      }
      else if(D->table[h] == NULL)
      {
         D->table[h] = N;
      }
      else
      {
         N->next = D->table[h];
         D->table[h] = N;
      }
      D->numItems++;
}

void delete(Dictionary D, char* k)
{
   int h = hash(k); //SETTING THE VARIABLES
   Node N = D->table[h];
   Node H = NULL;

   if( D == NULL )
   {
      fprintf(stderr, "Dictionary Error: calling delete() on NULL Dictionary reference\n");
      exit(EXIT_FAILURE);
   }

   if( lookup(D,k) == NULL)
   {
      fprintf(stderr, "Dictionary Error: cannot delete non-existent key\n");
      exit(EXIT_FAILURE);
   }

   if(lookup(D,k) != NULL)
   {
      if(N->key == k)
      {
         H = N;
         D->table[h] = N->next;
         freeNode(&H); //FREE BECAUSE DELETED
      }
      else
      {
         while(N->next->key != k)
         {
            N = N->next; //Basically looping through N = N.next
         }
         H = N->next;
         N->next = H->next;
         freeNode(&H); //SAME THING HERE
      }
      D->numItems--; //Deleting one makes it one less
   }
}

void makeEmpty(Dictionary D)
{
   if( D == NULL)
   {
      fprintf(stderr, "Dictionary Error: calling MakeEmpty() on NULL Dictionary\n");
   }

   for(int h = 0; h < tableSize; h++) //looping through
   {
         while (D->table[h] != NULL) //LOOP TO EMPTY ALL
         {
            Node N;
            N = D->table[h];
            D->table[h] = N->next;
            freeNode(&N); //MAKING EMPTY SO FREE IT
            N = NULL;
         }
   }
   D->numItems = 0;
}

int countChars(Dictionary D){
	int count = 0;
	for(int h=0;h<tableSize;h++){
		Node N;
		N = D->table[h];
		if(N!=NULL){
			count += strlen(N->key) + strlen(N->value) + 2;
			while(N->next!=NULL){
				N=N->next;
				count += strlen(N->key) + strlen(N->value) + 2;
			}
		}
	}

	//freeNode(&N);
	return count;
}

char* DictionaryToString(Dictionary D){
	char* str;
	int n;
	if( D == NULL )
	{
		fprintf(stderr, "Dictionary Error: calling DictionaryToString() on NULL Dictionary reference\n");
		exit(EXIT_FAILURE);
	}
	n=countChars(D);
	str = calloc(n+1, sizeof(char));
	for(int h = 0; h < tableSize; h++) //looping through
	{
		Node N;
		N = D->table[h];
		if(N!=NULL){
			strcat(str, N->key);
			strcat(str," ");
			strcat(str,N->value);
			strcat(str,"\n");

			while(N->next!=NULL){
				N=N->next;
				strcat(str, N->key);
				strcat(str," ");
				strcat(str,N->value);
				strcat(str,"\n");
			}
		}
	}
	str[n]='\0';
	return str;

}