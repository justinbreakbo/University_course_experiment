#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>

int main()
{
	int process1, process2, i;
	while((process1 = fork()) == -1);
	if(process1 == 0)
	{
		lockf(1, 1, 0);
		for(i=0; i<10; i++)
		{
			printf("childB % d \n", i);
			lockf(1, 0, 0);
		}
	}
	else
	{
		while((process2 = fork()) == -1);
		if(process2 == 0)
		{
			lockf(1,1,0);
			for(i = 0;i < 10; i++)
			{
				printf("childG %d \n", i);
				lockf(1, 1, 0);
			}
		}
		else
		{
			lockf(1,1,0);
			for(i=0;i<10;i++)
			{
				printf("parent %d \n", i);
				lockf(1,0,0);
			}
		}
	}
}
