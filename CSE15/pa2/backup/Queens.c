//Queens
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>


void printBoard(int** B, int n){
    //printf("hi3");
	char x[500] = "";
	char l[500] = "(";
	char r[100] = ")";
	char temp[500] ="";
	char ans[500] = "";

	//int size = sizeof(B)/sizeof(B[0]);
	for(int i=1;i<=n;i++){
		sprintf(x, "%d, ", B[i][0]);
		strcat(temp,x);
	}
	strcat(ans,l);
	strcat(ans,temp);
	ans[strlen(ans)-2]='\0';
	strcat(ans,r);
	printf("%s\n", ans);

}

void placeQueen(int** B, int n, int i, int j){
	B[i][j] += 1;
	B[i][0] = j;
	int a,b;
	//int size = sizeof(B)/sizeof(B[0]);

	for(a = i+1; a <= n;a++){//puts -1 vertically
		B[a][j] -= 1;
	}

	for(a = i+1, b = j+1; a <= n && b <= n; a++, b++){//puts -1 diagonally to the right
		B[a][b] -= 1;
	}

	for(a = i+1, b = j-1; a <= n && b > 0; a++, b--){//puts -1 diagonally to the left
		B[a][b] -= 1;
	}
}

void removeQueen(int** B, int n, int i, int j){
	B[i][j] -= 1;
	B[i][0] = 0;
	int a,b;
	//int size = sizeof(B)/sizeof(B[0]);

	for(a = i+1; a <= n;a++){//puts -1 vertically
		B[a][j] += 1;
	}

	for(a = i+1, b = j+1; a <= n && b <= n; a++, b++){//puts -1 diagonally to the right
		B[a][b] += 1;
	}

	for(a = i+1, b = j-1; a <= n && b > 0; a++, b--){//puts -1 diagonally to the left
		B[a][b] += 1;
	}
}

int findSolutions(int** B, int n, int i, char* mode){
	int sum = 0;
    
    //printf("%d\n", n);
    //printf("%d\n", i);

	if (i > n){
		if(strcmp(mode,"verbose")==0){
			printBoard(B,n);
		}
		//printf("hi\n");
		return 1;
	}
	else{

		for(int a=1;a<=n;a++){
			if(B[i][a]==0){
				placeQueen(B, n, i, a);
				sum = sum + findSolutions(B, n, i+1, mode);
				//printf("%d\n",sum);
				removeQueen(B, n, i, a);
			}
		}
	}
	return sum;
}

void Usage(){
	printf("%s\n", "Usage: Queens [-v] number");
	printf("%s\n", "Option: -v   verbose output, print all solutions");
}

void main(int argc, char* argv[]){
	int n,i;
	int** B;
	char* v = "-v";
	char p[100];
	bool test = false;
	if(argc<2 || argc>3){ //print usage error if input is less than 1 or more than 2
		Usage();
		exit(EXIT_SUCCESS);
	}

	if(argc == 2){ //if argc is 1, check if it is a number
		sscanf(argv[1]," %d", &n); //What if n is 0
		if(n==0){
			Usage();
			exit(EXIT_SUCCESS);
		}
	}

	if(argc == 3){
		sscanf(argv[1]," %s", p);
		sscanf(argv[2]," %d", &n);
		if(strcmp(p,v)!=0){
			Usage();
			exit(EXIT_SUCCESS);
		}
		else{
			test = true;
			if(n==0){
				Usage();
				exit(EXIT_SUCCESS);
			}
		}
	}

	if(n<1){
		Usage();
		exit(EXIT_SUCCESS);
	}
	
	B=calloc(n+1,sizeof(int*));
	for(i=0;i<=n;i++){
	    B[i]=calloc(n+1,sizeof(int));
	}
    
	if(test == true){ //Prints solution in verbose mode
		if(n==1){
			printf("%d-Queens has %d solution\n",n,findSolutions(B,n,1,"verbose"));
		}
		else{
			printf("%d-Queens has %d solutions\n",n,findSolutions(B,n,1,"verbose"));
		}
	}
	else{ //Prints solution in normal mode

		if(n==1){
			printf("%d-Queens has %d solution\n",n,findSolutions(B,n,1,"normal"));
		}
		else{
			printf("%d-Queens has %d solutions\n",n,findSolutions(B,n,1,"normal"));
		}
	}

	for (int i=0;i<n;i++){
		int* ptr = B[i];
		free(ptr);
		ptr = NULL;
	}

}