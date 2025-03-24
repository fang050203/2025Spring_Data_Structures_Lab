#include <stdio.h>
const int N=100010;     //定义一个比较大的空间

int q1[N];
int hh1=0,tt1=-1;    //定义轨道1队列

int q2[N];
int hh2=0,tt2=-1;   //定义轨道2队列

int stk[N];     //定义排序用的栈
int tt=1;        //定义栈顶

int main()
{
    while(1)
    {
        char temp=getchar();
        if(temp==' ')continue;
        else if(temp=='\n')break;
        else q1[++tt1]=temp-'1'+1;
    }
    
    return 0;
}