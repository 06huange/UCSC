//Simulation.c
/*
*Name:Kuo-Peng Huang
*UCSC ID:khuang53
*Class:CSE15
*Assignment:pa4
*Role:processes jobs using integerQueue linked list
*Date: Dec 3,2019
*/
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"Job.h"
#include"IntegerQueue.h"

Job getJob(FILE* in){
	int a, d;
	fscanf(in, "%d %d\n", &a, &d);
	return newJob(a, d);
}

void printTrace(FILE* trace,IntegerQueue* Q,Job* backup, int time, int n){
	fprintf(trace, "time=%d\n", time);
	for(int i=0;i<=n;i++){
		fprintf(trace, "%d: ",i);
        if(isEmpty(Q[i])!=1){
            int p = length(Q[i]);
            for(int y = 0;y<p;y++){
                int temp = dequeue(Q[i]);
                printJob(trace, backup[temp]);
                enqueue(Q[i],temp);
            }
            fprintf(trace, "\n");
        }
        else{
            fprintf(trace, "\n");
        }
	}
    fprintf(trace, "\n");
}


int main(int argc, char* argv[]){
	FILE* in;
	FILE* report;
	FILE* trace;
	int m;
	int time = 0;
    char rpt[50];
    char trc[50];

    char* arg;
    arg = argv[1];

    strcpy(rpt, arg);
    strcpy(trc, arg);
	report = fopen(strcat(rpt,".rpt"),"w");
	trace = fopen(strcat(trc,".trc"),"w");


	if( (in=fopen(arg, "r"))==NULL ){
      printf("Unable to read from file %s\n", argv[1]);
      exit(EXIT_FAILURE);
    }

    fscanf(in,"%d\n",&m);
    Job* backup = calloc(m,sizeof(Job));
    for(int i=0;i<m;i++){
    	backup[i] = getJob(in);
    }

    //integer queue
    IntegerQueue* Q = calloc(m,sizeof(IntegerQueue));
    //place job indices in storage queue
    for(int i=0;i<m;i++){
        Q[i]= newIntegerQueue();
        enqueue(Q[0],i);
    }
    //HEADER FOR TRACE FILE
    fprintf(trace, "Trace file: %s.trc\n",arg);
    fprintf(trace, "%d Jobs:\n",m);
    for(int i=0;i<m;i++){
    	printJob(trace, backup[i]);
    }
    fprintf(trace,"\n");
    fprintf(trace,"\n");



    //HEADER FOR REPORT FILE
    fprintf(report, "Report file: %s.rpt\n",arg);
    fprintf(report, "%d Jobs:\n",m);

    for(int i=0;i<m;i++){

    	printJob(report, backup[i]);
    }

    fprintf(report,"\n");

    fprintf(report,"\n");

    fprintf(report,"***********************************************************\n");

    //printf("Running simulation...\n");//************
    //printf("\n");//************
    //************************
	//RUN SIMULATION M-1 TIMES
	//************************
    //printf("yo\n");
    for(int n=1;n<m;n++){
        //printf("yo\n");
    	fprintf(trace, "*****************************\n");
    	if(n==1){
    		fprintf(trace, "%d processor:\n",n);
    	}
    	else{
    		fprintf(trace, "%d processors:\n",n);
    	}
    	fprintf(trace, "*****************************\n");
        //printf("yo");
        //printf("yo\n");
        printTrace(trace, Q, backup,time, n);
        //printf("yo\n");
        //printf("yo");
    	double averageWait = 0.00;
    	int totalWait = 0;
    	int maxWait = 0;
    	int min = 100;
    	int i = 0;
    	int pT = 0;
        //printf("yo\n");
        //printf("length of storage queue %d\n",length(Q[0]));
    	//************************
		//PROCESS ALL JOBS
		//************************
    	for(time=0;;time++){ //process all jobs in storage queue
    		if(length(Q[0])==m && i==m){
    			break;
    		}
            //printf("Processing finished jobs...\n");
    		//************************
	    	//PROCESS FINISHING JOBS
	    	//************************
    		for(int j=1;j<=n;j++){ //loop through all processors
				if(isEmpty(Q[j])!=1){ //check to see if processors are empty
                    //printf("DF:LSLDKFJ:ALKJLFSDF\n");
					if(getFinish(backup[peek(Q[j])])==time){//if finish time equals time, dequeue and add to storage
						int temp;
						temp = peek(Q[j]);
                        //printf("THIS JOB IS FINISHED------->%d\n",temp);
						dequeue(Q[j]);
						if(length(Q[j])!=0){
							computeFinishTime(backup[peek(Q[j])],time);
							int tempWait = getWaitTime(backup[peek(Q[j])]);
							totalWait += tempWait;
							if(tempWait>=maxWait){
								maxWait=tempWait;
							}
						}
						enqueue(Q[0],temp);
                        pT=1;
					}
				}
			}

            //printf("Adding jobs...\n");
			//************************
	    	//ADDING JOBS TO PROCESSOR
	    	//************************
            if(i<m){
        		while(getArrival(backup[i])==time){ //check for arrival time of the top of the storage
    	    		//find processor with least items
                    //printf("finding shortest line...\n");
    	    		for(int k =1;k<=n;k++){
    	    			if(length(Q[k])<=min){ //if processor is not empty
    	    				min = length(Q[k]); //determine the processor with minimum length
    	    			}
    	    		}
    	    		//add job to lowest index processor
                    //printf("finding closest line...\n");
                    int index = 1;
    	    		for(int k =1;k<=n;k++){
    	    			if(length(Q[k])<=min){ //if length of processor is minimum
    	    				min = length(Q[k]);	
                            index=k;
                            break;
    	    			}
    	    		}
                    //printf("adding job into the processor...\n");
    	    		enqueue(Q[index],i); //add job in storage to processor
    				if(length(Q[index])==1){
    					computeFinishTime(backup[peek(Q[index])],time);
    					int tempWait = getWaitTime(backup[peek(Q[index])]);
    					totalWait += tempWait;
    					if(tempWait>=maxWait){
    						maxWait=tempWait;
    					}

    				}
    				dequeue(Q[0]); //delete first job in storage
    				//print to trace file
                    pT = 1;
                    i++;
                    if(i>m-1){
                        break;
                    }
    	    		min = 100;
        		}
            }

    		if(pT==1){
    			printTrace(trace, Q, backup,time, n);
    		}
	    	pT=0;

    	}
    	//print to report
    	averageWait = (double)totalWait/m;
    	if(n==1){
    		fprintf(report,"%d processor: totalWait=%d, maxWait=%d, averageWait=%.2f\n",n,totalWait,maxWait,averageWait);
    	}
    	else{
    		fprintf(report,"%d processors: totalWait=%d, maxWait=%d, averageWait=%.2f\n",n,totalWait,maxWait,averageWait);
    	}

    	for(int z = 0;z<m;z++){
    		resetFinishTime(backup[z]);
    	}

    	i=0;
    	averageWait = 0.00;
    	totalWait = 0;
    	maxWait = 0;
        time=0;
        dequeueAll(Q[0]);
        //place job indices in storage queue
        for(int i=0;i<m;i++){
            enqueue(Q[0],i);
        }
    }
    for(int i=0;i<m;i++){
        freeIntegerQueue(&Q[i]);
        freeJob(&backup[i]);
    }
    free(Q);
    free(backup);
    Q=NULL;
    backup=NULL;

    fclose(in);
    fclose(trace);
    fclose(report);

    exit(EXIT_SUCCESS);
}