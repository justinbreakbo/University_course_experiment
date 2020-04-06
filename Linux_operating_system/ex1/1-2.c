#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

void main(){
  int p1,p2;
  while((p1 = fork()) == -1);
  if(p1 == 0){
    execl("/bin/ls","ls","-1","-color",NULL);
    exit(1);
  }else{
    while((p2 = fork()) == -1);
    if(p2 == 0){
      execl("/bin/ls","ls","-1","-color",NULL);
      exit(1);
    }else{
      wait(NULL);
      printf("父进程\n");
      system("ps");
      exit(0);
    }
  }
}
