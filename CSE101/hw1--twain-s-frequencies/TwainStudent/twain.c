/*
twain.c
Takes input and returns sorted output
*/
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include"List.h"



int main(int argc, char *argv[]){
    FILE* in;
    FILE* out;
    FILE* twain = fopen("./twain-cleaned.txt","r");
    //FILE* twain = fopen("./test2.txt","r");
    char str[60];
	//int count = 1;

    //check number of argument
    if(argc != 3){
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    if((in=fopen(argv[1],"r")) == NULL){
        printf("Unable to read from file %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    if((out=fopen(argv[2],"w")) == NULL){
        printf("Unable to write to file %s\n", argv[2]);
        exit(EXIT_FAILURE);
    }
    
    //build array of linked lists
    List a = newList();
    List b = newList();
    List c = newList();
    List d = newList();
    List e = newList();
    List f = newList();
    List g = newList();
    List h = newList();
    List i = newList();
    List j = newList();
    List k = newList();
    List l = newList();
    List m = newList();
    List n = newList();
    List o = newList();
    List p = newList();
    List q = newList();
    List r = newList();
    List s = newList();
    List t = newList();
    List u = newList();
    List v = newList();
    List w = newList();
    List x = newList();
    List y = newList();
    List z = newList();
    List alphaList[26] = {a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z};

   
    //read words from twain-cleaned into linked list
    while(fgets(str,sizeof(str),twain) !=NULL){
    //printf("%s ",str);
        if(isalpha(str[0])!=0){ //check first character
            //printf("%c\n",str[0]);
            strtok(str,"\n");
            int index = toupper(str[0]);
            //printf("finding ");
            Node temp = find(str,alphaList[index-65]);
            //printf("updating list ");
            if(temp == NULL){
                insert(str,alphaList[index-65]);
            }
            else{
                update(temp);
            }
        }
        //printf("line -- %d\n", count);
        //count++;
    }
//printf("sort\n");    
    for(int i=0; i<26; i++){
        sort(alphaList[i]);
    }

    //print(out, L);
    
    //process querys from input file
    char queryChar;
    int queryRank;
    /*test
   for (int i=0; i<26; i++){
    printf(get(alphaList[i]));
    }
    */
    
    
    //printf("processing query\n");
    while(fscanf(in,"%c %d\n",&queryChar,&queryRank)!=EOF){
        //query
        int index = toupper(queryChar);
        query(queryRank,alphaList[index-65],out);
    }
    

    //print(out, alphaList[7]);
	fclose(out);
    fclose(in);
    fclose(twain);
	return EXIT_SUCCESS;
}

