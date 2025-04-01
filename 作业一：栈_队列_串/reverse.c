#include <stdio.h>
#define N 100010


void reverse(char *c,int i,int j)
{
    int mid=i+(j-i)/2+1;
    for(;i<mid;i++,j--)
    {
        char x=c[i];
        c[i]=c[j];
        c[j]=x;
    }
}
int main()
{
    char c[N];
    int cnt=0;
    char t;
    int i;
    while(1)
    {
        scanf("%c",&t);
        if(t=='\n')
        {
            c[cnt]='\0';
            break;
        }
        c[cnt++]=t;
    }
    //while(getchar()!='\n');
    int k;
    scanf("%d",&k);
    for(i=0;i+2*k<=cnt-1;i+=2*k)
    {
        reverse(c,i,i+k-1);
    }
    if(i+k>cnt-1)reverse(c,i,cnt-1);
    else reverse(c,i,i+k-1);
    puts(c);

    return 0;
}