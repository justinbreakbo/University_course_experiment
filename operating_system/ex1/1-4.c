#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<signal.h>
#include<unistd.h>

void waiting(), stop();
int waitMark;

int main(){
    int process1,process2,stdout;
    while((process1 = fork()) == -1);
    if(process1 > 0){
        while((process2 = fork()) == -1);
        if(process2 > 0){
            waitMark = 1;
	    signal(SIGINT,stop);   
	    waiting();
	    kill(process1,16);       
	    kill(process2,17);      
	    wait(0);
	    wait(0);
	    printf("parent is killed\n");
	    exit(0);
	}else{
	    waitMark = 1;
	    signal(17,stop);       
        signal(SIGINT,SIG_IGN); 
	    waiting();
	    lockf(stdout,1,0);
	    printf("child procsss2 is killed by parent\n");
	    lockf(stdout,0,0);
	    exit(0);
	}
    }else{
	    waitMark = 1;
	    signal(16,stop);       
        signal(SIGINT,SIG_IGN); 
	    waiting();
	    lockf(stdout,1,0);
	    printf("child process1 is killed by parent\n");
	    lockf(stdout,0,0);
	    exit(0);
    }
}

void waiting(){
    while(waitMark != 0);
}
void stop(){
    waitMark = 0;
}
