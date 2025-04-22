#include <stdio.h>
#include <stdlib.h>

// 信封结构体
typedef struct {
    int width;
    int height;
} Envelope;

void my_swap(Envelope *a,Envelope *b)
{
    Envelope t=*a;
    *a=*b;
    *b=t;
}
int max(int a,int b)
{
    return a>b?a:b;
}
void my_sort_width(Envelope* envelopes,int l,int r)
{
    if(l >= r)	return;
	
	int i = l - 1, j = r + 1; 
    Envelope x = envelopes[(l + r) >> 1];
	while(i < j)
	{
		//do i ++; while((envelopes[i].width!=envelopes[j].width&&envelopes[i].width < x.width) || ((envelopes[i].width==x.width&&envelopes[i].height>x.height)&&(envelopes[j].width==x.width&&envelopes[j].height>x.height)));
		//do j --; while((envelopes[i].width!=envelopes[j].width&&envelopes[j].width > x.width) || ((envelopes[i].width==x.width&&envelopes[i].height>x.height)&&(envelopes[j].width==x.width&&envelopes[j].height<=x.height)));
        do i ++; while(envelopes[i].width < x.width);
		do j --; while(envelopes[j].width > x.width);
		if(i < j) my_swap(&envelopes[i],&envelopes[j]);
	}
	my_sort_width(envelopes,l , j);
	my_sort_width(envelopes, j+1, r);
}


void my_sort_height(Envelope* envelopes,int l,int r)
{
    if(l >= r)	return;
	
	int i = l - 1, j = r + 1, x = envelopes[(l + r) >> 1].height;
	while(i < j)
	{
		do i ++; while(envelopes[i].height > x);
		do j --; while(envelopes[j].height < x);
		if(i < j) my_swap(&envelopes[i],&envelopes[j]);
	}
	my_sort_height(envelopes, l , j);
	my_sort_height(envelopes, j+1, r);
}

int fang(Envelope *envelopes,int n)
{
    int dp[n];
    for (int i = 0; i < n; ++i) {
        dp[i] = 1;
        for (int j = 0; j < i; ++j) {
            if (envelopes[j].height < envelopes[i].height) {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
    }
    int mout=0;
    for(int i=0;i<n;i++)
    {
        if(dp[i]>mout)mout=dp[i];
    }
    return mout;
}
int maxEnvelopes(Envelope* envelopes, int n) {
    // TODO
    my_sort_width(envelopes,0,n-1);
    for(int i=0;i<n;i++)
    {
        for(int j=i;j<n-1;j++)
        {
            while(envelopes[j].width==envelopes[i].width)j++;
            j--;
            if(i<j)
            {
                my_sort_height(envelopes,i,j);
                break;
            }
            else
            {
                break;
            } 
        }
    }
    int x=fang(envelopes,n);
    return x;
}

int main() {
    int n;
    scanf("%d", &n);
    
    Envelope* envelopes = (Envelope*)malloc(n * sizeof(Envelope));
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &envelopes[i].width, &envelopes[i].height);
    }
    
    int result = maxEnvelopes(envelopes, n);
    printf("%d\n", result);
    
    free(envelopes);
    return 0;
}