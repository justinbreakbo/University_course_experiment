
#include <iostream>
using namespace std;
#define MAXPROCESS 50                        /*最大进程数*/
#define MAXRESOURCE 100                        /*最大资源数*/
int AVAILABLE[MAXRESOURCE];                    /*可用资源数组*/
int MAX[MAXPROCESS][MAXRESOURCE];            /*最大需求矩阵*/
int ALLOCATION[MAXPROCESS][MAXRESOURCE];    /*分配矩阵*/
int NEED[MAXPROCESS][MAXRESOURCE];            /*需求矩阵*/
int REQUEST[MAXPROCESS][MAXRESOURCE];        /*进程需要资源数*/
bool FINISH[MAXPROCESS];                        /*系统是否有足够的资源分配*/
int p[MAXPROCESS];                             /*记录序列*/
int m,n;                                    /*m个进程,n个资源*/
void Init();
bool Safe();
void Bank();
void showdata(int,int);
int main()
{
	Init();
	Safe();
	Bank();
}
void Init()                /*初始化算法*/
{
	int i,j;
	cout<<"请输入进程的数目:";
	cin>>m;
	cout<<"请输入资源的种类:";
	cin>>n;
	cout<<"请输入每个进程最多所需的各资源数,按照"<<m<<"x"<<n<<"矩 阵输入"<<endl;
	for(i=0;i<m;i++)
		for(j=0;j<n;j++)
			cin>>MAX[i][j];
	cout<<"请输入每个进程已分配的各资源数,也按照"<<m<<"x"<<n<<"矩 阵输入"<<endl;
	for(i=0;i<m;i++)
	{
		for(j=0;j<n;j++)
		{
			cin>>ALLOCATION[i][j];
			NEED[i][j]=MAX[i][j]-ALLOCATION[i][j];
			if(NEED[i][j]<0)
			{
				cout<<"您输入的第"<<i+1<<"个进程所拥有的第"<<j+1<<"个资源数 错误,请重新输入:"<<endl;
				j--;
				continue;
			}
		}
	}
	cout<<"请输入各个资源现有的数目:"<<endl;
	for(i=0;i<n;i++)
	{
		cin>>AVAILABLE[i];
	}
}
void Bank()                /*银行家算法*/
{
	int i,cusneed,flag = 0;
	char again;
	while(1)
	{
		showdata(n,m);////////////////////////////////////////////////////////////////////
		cout<<endl;
input:
		cout<<"请输入要申请资源的进程号(注:第1个进程号为0,依次类推)"<<endl;
		cin>>cusneed;
		if (cusneed > m)
		{
			cout<<"没有该进程，请重新输入"<<endl;
			goto input;
		}
		cout<<"请输入进程所请求的各资源的数量"<<endl;
		for(i=0;i<n;i++)
		{
			cin>>REQUEST[cusneed][i];
		}
		for(i=0;i<n;i++)
		{
			if(REQUEST[cusneed][i]>NEED[cusneed][i])//如果用户选择的线程的第i个资源请求数＞该线程该资源所需的数量
			{
				cout<<"您输入的请求数超过进程的需求量!请重新输入!"<<endl;
				goto input;
			}
			if(REQUEST[cusneed][i]>AVAILABLE[i])//如果用户选择的线程的第i个资源请求数＞系统现有的第i个资源的数量
			{
				cout<<"您输入的请求数超过系统有的资源数!请重新输入!"<<endl;
				goto input;
			}
		}
		for(i=0;i<n;i++)//如果请求合理，那么下面
		{
			AVAILABLE[i]-=REQUEST[cusneed][i];//系统可用资源减去申请了的
			ALLOCATION[cusneed][i]+=REQUEST[cusneed][i];//线程被分配的资源加上已申请了的
			NEED[cusneed][i]-=REQUEST[cusneed][i];//线程还需要的资源减去已申请得到的
		}
		if(Safe())//AVAILABLE  ALLOCATION  NEED变动之后，是否会导致不安全
		{
			cout<<"同意分配请求!"<<endl;
		}
		else
		{
			cout<<"您的请求被拒绝!"<<endl;
			for(i=0;i<n;i++)
			{
				AVAILABLE[i]+=REQUEST[cusneed][i];
				ALLOCATION[cusneed][i]-=REQUEST[cusneed][i];
				NEED[cusneed][i]+=REQUEST[cusneed][i];
			}
		}
		for (i=0;i<n;i++)
		{
			if (NEED[cusneed][i] <= 0)
			{
				flag++;
			}
		}
		if (flag == n)//如果该进程各资源都已满足条件，则释放资源
		{
			for (i=0;i<n;i++)
			{
				AVAILABLE[i] += ALLOCATION[cusneed][i];
				ALLOCATION[cusneed][i] = 0;
				NEED[cusneed][i] = 0;
			}
			cout<<"线程"<<cusneed<<" 占有的资源被释放！"<<endl;
			flag = 0;
		}
		for(i=0;i<m;i++)//分配好了以后将进程的标识FINISH改成false
		{
			FINISH[i]=false;
		}
		cout<<"您还想再次请求分配吗?是请按y/Y,否请按其它键"<<endl;
		cin>>again;
		if(again=='y'||again=='Y')
		{
			continue;
		}
		break;
	}
}
bool Safe()                                    /*安全性算法*/
{
	int i,j,k,l=0;
	int Work[MAXRESOURCE];                    /*工作数组*/
	for(i=0;i<n;i++)
		Work[i]=AVAILABLE[i];
	for(i=0;i<m;i++)
	{
		FINISH[i]=false;//FINISH记录每个进程是否安全
	}
	for(i=0;i<m;i++)
	{   
		for(j=0;j<n;j++)//循环查找第i个进程需要的各个资源数 是否 超过系统现有的对应的资源数
		{
			if(NEED[i][j]>Work[j])//第i个进程需要的第j个资源数 ＞ 系统现有的第j个资源数
			{
				break;
			}
		}
		if(j==n)//如果第i个进程所需的各个资源数都没有超过系统现有的对应资源数
		{ 
			FINISH[i]=true;//给该进程的FINISH标记为true
			for(k=0;k<n;k++)
			{
				Work[k]+=ALLOCATION[i][k];//将Work赋值为 第i个进程各个已分配资源数＋系统现有的对应资源数(因为当改进程全部资源数都满足时线程结束并将资源返还给系统)
			}
			p[l++]=i;//记录进程号
		}
		else//如果超过继续循环下一个进程
		{
			continue; 
		}
		if(l==m)//当所有进程都能够被满足运行时
		{
			cout<<"系统是安全的"<<endl;
			cout<<"安全序列:"<<endl;
			for(i=0;i<l;i++)//改了146行的i值，显示资源分配给进程的顺序
			{
				cout<<p[i];
				if(i!=l-1)
				{
					cout<<"-->";
				}
			}
			cout<<""<<endl;			
			return true;
		}
	}//for循环
	cout<<"系统是不安全的"<<endl;
	return false;
}
 
void showdata(int n,int m)   //显示
{
	int i,j;
	cout<<endl;  
	cout<<"-------------------------------------------------------------"<<endl;  
	cout<<"系统可用的资源数为:    ";
	for   (j=0;j<n;j++)       
		cout<<"    "<<AVAILABLE[j];      
	cout<<endl;   
	cout<<"各进程还需要的资源量:"<<endl; 
	for   (i=0;i<m;i++)   
	{
		cout<<"    进程"<<i<<":";   
 
		for   (j=0;j<n;j++)
			cout<<"     "<<NEED[i][j];   
		cout<<endl;   
	}   
 
	cout<<endl;   
	cout<<"各进程已经得到的资源量:    "<<endl<<endl;   
 
	for   (i=0;i<m;i++)   
	{
		cout<<"    进程"<<i<<":";   
 
		for   (j=0;j<n;j++)
			cout<<"     "<<ALLOCATION[i][j];
		cout<<endl;   
	}  
	cout<<endl; 
}
