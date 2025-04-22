#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char big[26]={0};
char small[26]={0};
void swap(char *a,char *b)
{
    char t=*a;
    *a=*b;
    *b=t;
}
void fang_sort(char *s,int l,int r)
{
    if(l >= r)	return;
	
	int i = l - 1, j = r + 1, x = s[l + r >> 1];
	while(i < j)
	{
		do i ++; while(s[i] < x);
		do j --; while(s[j] > x);
		if(i < j) swap(&s[i],&s[j]);
	}
	fang_sort(s, l , j);
	fang_sort(s, j+1, r);
}

int find_cnt(char c)
{
    if(c<='Z')return big[c-'A'];
    else return small[c-'a'];
}
void my_sort(char *s,int l,int r)
{
    if(l >= r)	return;
	
	int i = l - 1, j = r + 1, x = s[(l + r) >> 1];
	while(i < j)
	{
		do i ++; while(find_cnt(s[i]) > find_cnt(x));
		do j --; while(find_cnt(s[j]) < find_cnt(x));
		if(i < j) swap(&s[i],&s[j]);
	}
	my_sort(s, l , j);
	my_sort(s, j+1, r);
    /*if (l >= r) return;

    int mid = (l + r) >> 1;
    my_sort(tmp,s, l, mid);
    my_sort(tmp,s, mid + 1, r);

    int k = 0, i = l, j = mid + 1;
    while (i <= mid && j <= r)
        //if ((find_cnt(s[i]) < find_cnt(s[j]))||(find_cnt(s[i])==find_cnt(s[j])&&s[i]<s[j])) tmp[k ++ ] = s[i ++ ];
        if (find_cnt(s[i]) > find_cnt(s[j])) tmp[k ++ ] = s[i ++ ];
        else tmp[k ++ ] = s[j ++ ];

    while (i <= mid) tmp[k ++ ] = s[i ++ ];
    while (j <= r) tmp[k ++ ] = s[j ++ ];

    for (i = l, j = 0; i <= r; i ++, j ++ ) s[i] = tmp[j];*/
}
void my_sort_a(char *s,int l,int r)
{
    if(l >= r)	return;
	int i = l - 1, j = r + 1, x = s[(l + r) >> 1];
	while(i < j)
	{
		do i ++; while(s[i]<x);
		do j --; while(s[j]>x);
		if(i < j) swap(&s[i],&s[j]);
	}
	my_sort_a(s, l , j);
	my_sort_a(s, j+1, r);
}
char* frequencySort(char* s) {
    // TODO
    char *p=s;
    int size=0;
    while(*p!='\0')
    {
        if(*p<='Z')
        {
            big[*(p++)-'A']++;
            size++;
        }
        else 
        {
            small[*(p++)-'a']++;
            size++;
        }
    }
    //char tmp[size];
    //fang_sort(s,0,size-1);
    my_sort(s,0,size-1);
    for(int i=0;i<size;i++)
    {
        for(int j=i;j<size-1;j++)
        {
            while(find_cnt(s[j])==find_cnt(s[i]))j++;
            j--;
            if(i<j)
            {
                my_sort_a(s,i,j);
                break;
            }
            else
            {
                break;
            } 
        }
    }
    return s;
}

int main() {
    char s[1000];
    scanf("%s", s);
    
    char* result = frequencySort(s);
    printf("%s\n", result);
    
    return 0;
}