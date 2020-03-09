#include<stdlib.h>
#include<stdio.h>
#include<time.h>

void CopyL(int Sour[],int Dist[] ,int x); //数组Sour复制到数组Dist，复制到x个数
void SetDI(int DiscL1[], int DiscL2[], int DiscL3[], int num);  //随机生成磁道数  
void Print(int Pri[],int x);  //打印输出数组Pri
void DelInq(int Sour[],int x,int y);  //数组Sour把x位置的数删除，并把y前面的数向前移动，y后的数保持不变(即会出现2个y) 
void FCFS(int Han,int DiscL[], int num);  //先来先服务算法(FCFS)
void SSTF(int Han,int DiscL[], int num);  //最短寻道时间优先算法(SSTF)
int SCAN(int Han,int DiscL[],int x,int y);  //扫描算法(SCAN)
void PaiXu();  //寻道长度由低到高排序
void Pri();
int NAll=0;
int Best[5][2]; //用作寻道长度由低到高排序时存放的数组 
int Limit=0; //输入寻找的范围磁道数i
int Jage;
float Aver=0;

int main()
{

    int num;
    int i;
    int DiscLine1[20];  
    int DiscLine2[20];  
    int DiscLine3[20];  

    int Hand;  //磁道数
    int Con=1;

    srand(time(NULL));
    num = rand() % (20-10) + 10;  


    Jage=0;
    printf(" 请输入初始的磁道数(0~1000):");
    scanf("%d",&Hand);
    printf(" 请输入磁道的范围(0~1000):");
    scanf("%d",&Limit);
    if(Limit<=0||Limit>1000){
        printf("超出范围!\n");
    } 
    else{

        SetDI(DiscLine1, DiscLine2, DiscLine3, num);  //随机生成磁道数
        FCFS(Hand,DiscLine1,num); //先来先服务算法(FCFS)
        SSTF(Hand,DiscLine2,num); //最短寻道时间优先算法(SSTF)
        SCAN(Hand,DiscLine3,0,num-1);  //扫描算法(SCAN)
    }

}

//数组Sour复制到数组Dist，复制到x个数
void CopyL(int Sour[],int Dist[] ,int x)
{
    int i;
    for(i=0;i<=x;i++)
    {
        Dist[i]=Sour[i];
    }
}
//打印输出数组Pri
void Print(int Pri[],int x)
{
    int i;
    for(i=0;i<=x;i++)
    {
        printf("%5d",Pri[i]);
    }
}
//随机生成磁道数
void SetDI(int DiscL1[], int DiscL2[], int DiscL3[], int num)
{
    int i;
    for(i=0;i<=num-1;i++)
    {
        DiscL1[i]=rand()%Limit;//随机生成10个磁道号
        DiscL2[i]=DiscL1[i];
        DiscL3[i]=DiscL1[i];
    }
    printf("+++随机生成的磁道号序列:");
    Print(DiscL1,num-1);  //输出随机生成的磁道号
    printf(" \n\n");
}
//数组Sour把x位置的数删除，并把y前面的数向前移动，y后的数保持不变(即会出现2个y) 
void DelInq(int Sour[],int x,int y)
{
    int i;
    for(i=x;i<y;i++)
    { 
        Sour[i]=Sour[i+1];
        x++;
    }
}
//先来先服务算法(FCFS)
void FCFS(int Han,int DiscL[], int num)
{
    int RLine[20];  //将随机生成的磁道数数组Discl[]复制给数组RLine[]
    int i,k,All,Temp;  //Temp是计算移动的磁道距离的临时变量
    All=0;  //统计全部的磁道数变量
    k=num-1;  //限定10个的磁道数
    CopyL(DiscL,RLine,num-1);  //复制磁道号到临时数组RLine
    printf("---按照FCFS算法,磁道的访问顺序为:");
    All=Han-RLine[0];
    for(i=0;i<=num -1;i++)
    {
        Temp=RLine[0]-RLine[1];
        if(Temp<0) 
            Temp=(-Temp);//移动磁道数为负数时,算出相反数作为移动磁道数
        printf("%5d",RLine[0]);
        All=Temp+All;//求全部磁道数的总和 
        DelInq(RLine,0,k);//每个磁道数向前移动一位
        k--;
    }
    Best[Jage][1]=All;
    Best[Jage][0]=1; 
    Jage++;//排序的序号加1
    Aver=((float) All)/num;//求平均寻道次数 
    printf("\n");
    printf("---执行FCFS算法的移动磁道数:<%5d> \n",All);printf("\n");
    // printf(" + 平均寻道长度:*%0.2f* \n",Aver);printf("\n");
}

//冒泡排序
int* Bubble(int pArr[],int nFirst,int nEnd)
{
    int nTemp=0;
    for(int i=nFirst;i<nEnd;++i)
    {
        for(int j=i;j<nEnd;++j)
        {
            if(pArr[i]>pArr[j])
            {
                nTemp=pArr[i];
                pArr[i]=pArr[j];
                pArr[j]=nTemp;
            }
        }
    }
    return pArr;
}

//最短寻道时间优先算法(SSTF)
void SSTF(int Han,int DiscL[],int num)
{
    int temp;
    int k=1,n=num;
    int l,r;
    int i,j,all=0;

    //将磁道号按递增排序
    DiscL=Bubble(DiscL,0,num);

    printf("---按照SSTF算法,磁道的访问顺序为：");

  
    if(DiscL[n-1]<=Han)//当前磁头位置大于最外围欲访问磁道
    {
      for(i=n-1;i>=0;i--)
      {
          printf("%5d",DiscL[i]);
      }
      all=Han-DiscL[0];
    }
    else
      if(DiscL[0]>=Han)//当前磁头位置小于最里欲访问磁道
      {
          for(i=0;i<n;i++)
          {
              printf("%5d",DiscL[i]);
          }
          all=DiscL[n-1]-Han;
      }
    else
    {
        while(DiscL[k]<Han)//确定当前磁道在已排的序列中的位置
        {
          k++;
        }
         l=k-1;
         r=k;

        while((l>=0)&&(r<n))
        {
         if((Han-DiscL[l])<=(DiscL[r]-Han))//选择离磁头近的磁道
         {
             printf("%5d",DiscL[l]);
             all+=Han-DiscL[l];
             Han=DiscL[l];
             l=l-1;
         }
        else
        {
            printf("5%d",DiscL[r]);
            all+=DiscL[r]-Han;
            Han=DiscL[r];
            r=r+1;
        }
      }
      if(l=-1)//磁头位置里侧的磁道已访问完
      {
         for(j=r;j<n;j++)//访问磁头位置外侧的磁道
         {
            printf("%5d",DiscL[j]);
         }
             all+=DiscL[n-1]-DiscL[0];
      }
    if(r==n)//磁头位置外侧的磁道已访问完
    {
    for(j=k-1;j>-1;j--) //访问磁头位置里侧的磁道
      {
          printf("%5d",DiscL[j]);
      }
          all+=DiscL[n-1]-DiscL[0];
     }
 }
      printf("\n---执行SSTF算法的移动磁道数:<%5d> \n",all);
      //float num_a = float(num);
      //printf(" + 平均寻道长度:*%0.2f* \n",all/num_a);

}

//扫描算法(SCAN)
int SCAN(int Han,int DiscL[],int x,int y)
{
    int temp;
    int k=1,n=y+1;
    int l,r;
    int i,j,all=0;
    DiscL=Bubble(DiscL,x,y);

     if(DiscL[n-1]<=Han) //磁头位置大于最外围欲访问磁道
       {           
           printf("\n---按照SCAN算法，磁道的访问顺序为：");
           for(i=n-1;i>=0;i--)
             printf("%5d",DiscL[i]);
           all=Han-DiscL[0];
       }
       else
           if(DiscL[0]>=Han) //磁头位置小于最里欲访问磁道
           {           
              printf("\n---按照SCAN算法，磁道的访问顺序为：");
              for(i=0;i<n;i++)
                 printf("%5d",DiscL[i]);
              all=DiscL[n-1]-Han;
           }
           else                   //磁头位置在最里侧磁道与最外侧磁道之间
           {   int d;
               while(DiscL[k]<Han)
               {             //确定当前磁道在已排的序列中的位置
                   k++;
               }
               l=k-1;
               r=k;  
               printf("\n请输入当前磁头移动的方向 (0 表示向内 ，1表示向外) : ");
               scanf("%d",&d);  //确定磁头访问的方向
             
               printf("\n---按照SCAN算法，磁道的访问顺序为：");
               if(d==0||d==1)
               {
                      if(d==0)    //磁头向内
                      {
                        for(j=l;j>=0;j--)
                        {
                             printf("%5d",DiscL[j]);
                        }
                        for(j=r;j<n;j++)
                        {
                            printf("%5d",DiscL[j]);
                        }
                         all=Han-2*DiscL[0]+DiscL[n-1];
                      }
                        if(d==1)               //磁头向外
                        { 
                            for(j=r;j<n;j++)
                            {
                                printf("%5d",DiscL[j]);
                            }
                            for(j=l;j>=0;j--)
                            {
                                printf("%5d",DiscL[j]);
                            }
                             all=2*DiscL[n-1]-Han-DiscL[0];
                        }
               }
            else
                printf("请输入0或1！");
            }

      printf("\n---执行SCAN算法的移动磁道数:<%5d> \n",all);
      //float num_a = float(num);
      //printf(" + 平均寻道长度:*%0.2f* \n",all/num_a);
      return 0;
}

