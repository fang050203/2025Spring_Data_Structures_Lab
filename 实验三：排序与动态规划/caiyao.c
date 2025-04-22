#include <stdio.h>

int max(int a,int b)
{
    return a>b ?a:b;
}

int main()
{
    int m,n;
    scanf("%d %d",&m,&n);
    //while(getchar()!='\n');
    int x=n;
    int weight[x];
    int value[x];
    int dp[x][m+1];
    int a=0,b=0;
    while(n--)
    {
        scanf("%d %d",&weight[a++],&value[b++]);
        //while(getchar()!='\n');
    }
    for(int i=0;i<x;i++)
    {
        dp[i][0]=0;
    }
    for(int i=0;i<=m;i++)
    {
        if(i<weight[0])dp[0][i]=0;
        else dp[0][i]=dp[0][i-weight[0]]+value[0];
    }
    for(int i=1;i<x;i++)
    {
        for(int j=1;j<=m;j++)
        {
            if (j < weight[i]) dp[i][j] = dp[i - 1][j];
            else dp[i][j] = max(dp[i - 1][j], dp[i][j - weight[i]] + value[i]);
        }
    }
    printf("%d",dp[x-1][m]);

    return 0;
}
