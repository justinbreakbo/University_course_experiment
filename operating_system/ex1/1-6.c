#include<sys/types.h>
#include<sys/shm.h>
#include<sys/ipc.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<wait.h>


#define SHMKEY 75
int shmid, i;
int *addr;

void client()
{
	int i;
	shmid = shmget(SHMKEY, 1024, 0777);
	addr = shmat(shmid, 0,0);
	for (i= 9;i>=0; i--)
	{
		while(*addr!=-1);
		printf("(client)sent\n");
		*addr = i;
	}
	exit(0);
}

void server()
{
	shmid = shmget(SHMKEY, 1024, 0777|IPC_CREAT);
	addr = shmat(shmid, 0, 0);
	do{
		*addr= -1;
		while(*addr==-1);
		printf("(server)received\n");
	}while(*addr);
	shmctl(shmid, IPC_RMID,0);
	exit(0);
}

void main()
{
	while((i=fork())==-1);
	if(!i)server();
	system("ips -m");
	while ((i=fork()) == -1);
	if (!i) client();
	wait(0);
	wait(0);
}
