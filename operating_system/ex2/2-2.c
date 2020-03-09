#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXPROCESS 20
#define MAXRESOURCE 30

const int n = 3, m = 3;
int available[m] = {3, 3 ,3};
int max[n][m] = {3,2,1,2,1,3,1,2,3};
int allocation[n][m] = {1,2,1,1,0,0,1,1,1};
int need[n][m] = {2,0,0,1,1,3,0,1,2};

int request[MAXPROCESS][MAXRESOURCE];  

int p[MAXPROCESS];  
int finish[MAXPROCESS];

// 银行家算法
// void bank()
// {

// 	int i,cusneed,flag = 0;
// 	char again;
// 	while(1)
// 	{
// 		show(n,m);////////////////////////////////////////////////////////////////////
		

//         while(1)
//         {
//             printf("请输入要申请资源的进程号(注:第1个进程号为0,依次类推)");
//             scanf("%d", cusneed);
//             if (cusneed > m)
//             {
//                 printf("没有该进程，请重新输入");
//                 continue;
//             }
//             else
//             {
//                 break;
//             }
//         }

//         printf("请输入进程所请求的各资源的数量：\n");
// 		for(i=0;i<m;i++)
// 		{
// 			scanf("%d",request[cusneed][i]);
// 		}
// 		for(i=0;i<m;i++)
// 		{
// 			if(request[cusneed][i]>need[cusneed][i])//如果用户选择的线程的第i个资源请求数＞该线程该资源所需的数量
// 			{
                
// 				printf("您输入的请求数超过进程的需求量!请重新输入! \n ");
				
// 			}
// 			if(request[cusneed][i]>available[i])//如果用户选择的线程的第i个资源请求数＞系统现有的第i个资源的数量
// 			{
// 				printf("您输入的请求数超过系统有的资源数!请重新输入!");
				
// 			}
// 		}
// 		for(i=0;i<m;i++)//如果请求合理，那么下面
// 		{
// 			available[i]-=request[cusneed][i];//系统可用资源减去申请了的
// 			allocation[cusneed][i]+=request[cusneed][i];//线程被分配的资源加上已申请了的
// 			need[cusneed][i]-=request[cusneed][i];//线程还需要的资源减去已申请得到的
// 		}
// 		if(Safe())//AVAILABLE  ALLOCATION  NEED变动之后，是否会导致不安全
// 		{
// 			printf("同意分配请求!");
// 		}
// 		else
// 		{
// 			printf("您的请求被拒绝!");
// 			for(i=0;i<m;i++)
// 			{
// 				available[i]+=request[cusneed][i];
// 				allocation[cusneed][i]-=request[cusneed][i];
// 				need[cusneed][i]+=request[cusneed][i];
// 			}
// 		}
// 		for (i=0;i<m;i++)
// 		{
// 			if (need[cusneed][i] <= 0)
// 			{
// 				flag++;
// 			}
// 		}
// 		if (flag == m)//如果该进程各资源都已满足条件，则释放资源
// 		{
// 			for (i=0;i<m;i++)
// 			{
// 				available[i] += allocation[cusneed][i];
// 				allocation[cusneed][i] = 0;
// 				need[cusneed][i] = 0;
// 			}
// 			printf("线程 %d 占有的资源被释放！", cusneed);
// 			flag = 0;
// 		}
// 		for(i=0;i<m;i++)//分配好了以后将进程的标识FINISH改成false
// 		{
// 			finish[i]=0;
// 		}
// 		printf("您还想再次请求分配吗?是请按y/Y,否请按其它键");
// 		scanf("%c",again);
// 		if(again=='y'||again=='Y')
// 		{
// 			continue;
// 		}
// 		break;
// 	}
// }


// int safe()
// {
//     int i,j,k,l = 0;
//     int work[MAXRESOURCE];

//     for (i = 0; i < m; i ++ )
//         work[i] = available[i];
//     for (i = 0; i < n; i ++ )
//         finish[i] = 0;
//     for (i = 0; i < n; i++)
//     {
//         for (int j = 0; j < m; j++)
//         {
//             if (need[i][j] > work[j])
//             {
//                 break;
//             }
//         }
//         if (j == m)
//         {
//             finish[i] = 1;
//             for (k = 0; k<m; k++)
//             {
//                 work[k] += allocation[i][k];
//             }
//             p[l++] = i;
//         }
//         else
//         {
//             continue;
//         }
//         if (l== m)
//         {
//             printf("系统是安全的");
//             printf("安全系列：");
//             for(i = 0; i<l; i++)
//             {
//                 printf(p[i]);
//                 if (i!= l-1)
//                 {
//                     printf("-->");
//                 }
//             }
//             printf("  ");
//             return 1;
//         }
//     }
//     printf("系统是不安全的");
//     return 0;
// }

void show(int n, int m)
{
    printf("available向量：");
    for(int j = 0; j< m; j++)
    {
        printf("%d", available[j]);
    } 

    printf("max矩阵：");
    for(int i=0; i<n; i++)
    {
        for(int j = 0; j< m; j++)
        {
            printf("%d\t", max[i][j]);
        }
        printf("\n"); 
    }
    
    printf("allacation矩阵：");
    for(int i=0; i<n; i++)
    {
        for(int j = 0; j< m; j++)
        {
            printf("%d\t", allocation[i][j]);
        }
        printf("\n"); 
    }    

    printf("need矩阵：");
    for(int i=0; i<n; i++)
    {
        for(int j = 0; j< m; j++)
        {
            printf("%d\t", need[i][j]);
        }
        printf("\n"); 
    }    
}

// void init()
// {
//     int i,j;
//     srand((unsigned)time(NULL));
//     for (j = 0;j<m; j++)
//         available[j] = rand() % (max - min) + min;

//     for (i = 0;i<n; i++)
//     {
//         for (j = 0;j<m; j++)
//         {

//         }
//     }

// }

int main()
{

    

    
	// init();
    show(n,m);
	// safe();
	// bank();


    return 0;

}
