#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/mman.h>

int main(void){
	int i,fd;
	char * buf;
	fd = open("test-data",O_RDONLY);
	buf = mmap(0,12,PROT_READ,MAP_PRIVATE,fd,0);
	for(i=0;i<12;i++)
		printf("%c\n",buf[i]);
}
