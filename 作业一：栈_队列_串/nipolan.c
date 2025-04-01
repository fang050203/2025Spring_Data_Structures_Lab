#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 100010


int stk[N];
int tt=0;

void push(int x)
{
    if(tt==N-1)exit(1);
    else stk[++tt]=x;
}


int pop()
{
    int t;
    if(tt)
    {
        t=stk[tt--];
        return t;
    }
    else exit(1);
}

int en()
{
    if(tt)return 0;
    else return 1;
}

int top()
{
    if(tt)return stk[tt];
    else exit(1);
}

int main()
{   
    int a;
    scanf("%d",&a);
    getchar();
    char c[N];
    while(a--)
    {
        scanf("%s",c);
        //if(!strcmp(c,"\n"))break;
        if(!strcmp(c,"+"))
        {
            int a=pop();
            int b=pop();
            push(a+b);
        }
        else if(!strcmp(c,"-"))
        {
            int a=pop();
            int b=pop();
            push(b-a);
        }
        else if(!strcmp(c,"*"))
        {
            int a=pop();
            int b=pop();
            push(a*b);
        }
        else if(!strcmp(c,"/"))
        {
            int a=pop();
            int b=pop();
            push(b/a);
        }
        else
        {
            push(atoi(c));
        }
    }

    printf("%d",top());

    return 0;
}