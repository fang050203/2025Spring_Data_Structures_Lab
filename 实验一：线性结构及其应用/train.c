#include <stdio.h>
#define N 100010     //定义一个比较大的空间

int q1[N];
int hh1=0,tt1=-1;    //定义轨道1队列
int cnt1=0;   //统计个数

int q2[N];
int hh2=0,tt2=-1;   //定义轨道2队列
int cnt2=0;    //统计个数


int stk[N];     //定义排序用的栈
int tt=0;        //定义栈顶

int main()
{
    while(1)
    {
        scanf("%d",&q1[++tt1]);
        cnt1++;
        char ch=getchar();
        if(ch==' ')continue;
        else if(ch=='\n')break;   

    }
    while(1)
    {
        scanf("%d",&q2[++tt2]);
        cnt2++;
        char ch=getchar();
        if(ch==' ')continue;
        else if(ch=='\n')break;  
    }

    while(hh1<=cnt1-1&&hh2<=cnt2-1)
    {
        if(q1[hh1]>=q2[hh2])stk[++tt]=q1[hh1++];    //归并排序算法
        else stk[++tt]=q2[hh2++];
    }


    while(hh1<=cnt1-1)stk[++tt]=q1[hh1++];  //处理剩余项
    while(hh2<=cnt2-1)stk[++tt]=q2[hh2++];  //处理剩余项

    while(tt)
    {
        printf("%d ",stk[tt--]);    //打印栈值
    }
    printf("\n");

    return 0;
}
