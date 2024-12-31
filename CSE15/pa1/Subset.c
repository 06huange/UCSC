/*
*Name:Kuo-Peng Huang
*UCSC ID:khuang53
*Class:CSE15
*Assignment:pa1
*Role:Prints all possible subset combinations of a set
*Date: Oct 12,2019
*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>

#define MAX_SIZE 100

void printSet(int B[], int n){

	bool check = true;
	char fbracket[MAX_SIZE] = "{";
	char lbracket[MAX_SIZE] = "}";
	char subset[MAX_SIZE] = "";
	char comma[MAX_SIZE] = ", ";
	char ebracket[MAX_SIZE] = "{}";
	char temp[MAX_SIZE] = "";
	int len;
	for(int i=1;i<=n;i++){
		if(B[i] == 1){
			//subset = subset + ", " + i;
			//char *num;
			//itoa(i,num,10);
			sprintf(temp,"%d",i);
			strcat(subset,temp);
			strcat(subset,comma);
		}
	}

	for(int p=1;p<=n;p++){
		if(B[p] == 1){
			check = false;
		}
	}
	if (check == true){
		printf("%s",ebracket);
		return;
	}
	else{
	    char fSet[MAX_SIZE]="";
		//subset = temp;
		strcat(fSet,fbracket);
		strcat(fSet,subset);
		len = strlen(fSet);
		fSet[len-2]='\0';
		strcat(fSet,lbracket);
		printf("%s",fSet);
		printf("%s","\n");
	}

	
}

void printSubsets(int B[], int n,int k,int i){
	if(k==0){
		printSet(B,n);
		return;
	}
	else if(k>=n-i+1){
		return;
	}
	else{
		B[i] =1;
		printSubsets(B, n, k-1, i + 1);

		B[i] =0;
		printSubsets(B, n, k, i + 1);
	}
}

int main(int argc, char* argv[]){
	int n;
	int k, check1, check2;
	
	char ch;
	//int i=1;
    //printf("hi2\n");
	//scanf("%d %d", &n, &k);
	if(argc == 3){
	    //printf("hi3\n");
    	check1 = sscanf(argv[1],"%d%c",&n, &ch);
    	//printf("%d %d\n", n, check1);
    	check2 = sscanf(argv[2],"%d%c",&k, &ch);
    	//printf("%d %d\n", k, check2);
		if(check1 == 1 && check2 ==1){
			//test if k is greater than n
			if(k>n){
			    //printf("hi4\n");
				printf("Usage: Subset n k (n and k are ints satisfying 0<=k<=n<=100)");
			}

			//test if range
			else if(k<0||n>MAX_SIZE){
			    //printf("hi5\n");
				printf("Usage: Subset n k (n and k are ints satisfying 0<=k<=n<=100)");
			}

			else{
				//printf("hi\n");
				int B[n];
				printSubsets(B,n+1,k,1);
			}
		} else {
		    printf("Usage: Subset n k (n and k are ints satisfying 0<=k<=n<=100)");
		}
	} else {
	    printf("Usage: Subset n k (n and k are ints satisfying 0<=k<=n<=100)");
	}

	return EXIT_SUCCESS;
}
