#include <stdio.h>
#include <stdlib.h>
#define N 100010

int stk[N];
int tt=0;

void push(int x)
{
    stk[++tt]=x;
}

void pop()
{
    if(!stk_en())tt--;
}

int stk_en()
{
    if(tt)return 0;
    else return 1;
}

int main()
{
    char s[N];
    int cnt=0;
    char *p=s;
    char c;
    while(1)
    {
        scanf("%c",&c);
        if(c!='\n')
        {
            *(p++)=c;
            cnt++;
        }
        else
        {
            p=s;
            break;
        }
    }

    if(cnt%2)s[cnt/2]='1';

    while(cnt--)
    {
        c=*(p++);
        if(c>='1'&&c<='9')
        {
            continue;
        }
        else if(c>='A'&&c<='Z')
        {
            c+='a'-'A';
            if(stk_en())
            {
                push(c);
            }
            else if(c==stk[tt])
            {
                pop();
                continue;
            }
            else{
                push(c);
            }
        }
        else
        {
            if(stk_en())
            {
                push(c);
            }
            else if(c==stk[tt])
            {
                pop();
                continue;
            }
            else{
                push(c);
            }
        }
    }












    if(stk_en())printf("true");
    else printf("false");


    return 0;
}