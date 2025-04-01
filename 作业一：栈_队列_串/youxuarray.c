#include <stdio.h>
#define N 100010


int temp[N];
int main()
{
    int n;
    char c;
    int *p=temp;
    int a;
    scanf("%d",&n);
    while(getchar()!='\n');
    while(1)
    {
        scanf("%d",p++);
        c=getchar();
        if(c==' ')continue;
        else if(c=='\n')break;
    }
    scanf("%d",&a);
    int i=0;
    int j=0;
    while(i<=n-1&&j==0)
    {
        if(temp[i]<=a)printf("%d ",temp[i++]);
        else 
        {
            printf("%d ",a);
            j++;
        }
    }
    while(i<=n-1)
    {
        if(i<n-1)printf("%d ",temp[i++]);
        else printf("%d",temp[i++]);
    }
    if(!j)printf("%d",a);
    return 0;
}