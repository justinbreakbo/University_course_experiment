 
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/mman.h>
#define N 10

int main(void){
	int i,sum,fd;
	int *result_ptr = mmap(0,4,PROT_READ|PROT_WRITE,MAP_SHARED|MAP_ANONYMOUS,0,0);
	int pid=fork();
	if(pid==0){
		for(sum=0,i=1;i<N;i++) sum+=i;
		    *result_ptr = sum;
	}else{
		wait(0);
		printf("result = %d\n", *result_ptr);
	}
}
