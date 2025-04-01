#include <stdio.h>
#define N 85

int main()
{
    char A[N];
    char B[N];
    int cnta=0;
    int cntb=0;
    char c;
    while(1)
    {
        scanf("%c",&c);
        if(c=='\n')break;
        A[cnta++]=c;
    }
    while(1)
    {
        scanf("%c",&c);
        if(c=='\n')break;
        B[cntb++]=c;
    }
    int next[cntb];
    next[0]=0;
    int j=0;
    for(int i=1;i<cntb;i++)
    {
        while(j>0&&B[i]!=B[j])
        {
            j=next[j-1];
        }
        if(B[i]==B[j])
        {
            j++;
        }
        next[i]=j;
    }


    int k=0;
    for(int i=0;i<cnta;i++)
    {
        while(k>0&&A[i]!=B[k])
        {
            k=next[k-1];
        }

        if(A[i]==B[k])
        {
            k++;
        }

        if(k==cntb)
        {
            printf("Yes");
            return 0;
        }
    }
    printf("No");
    return 0;
}