#include <stdio.h>
#include <stdlib.h>


void my_swap(int *a,int *b)
{
    int t=*a;
    *a=*b;
    *b=t;
}
void my_sort(int *nums,int *fang,int l,int r)
{
    if(l>=r)return;
    int i = l - 1, j = r + 1, x = (l + r) >> 1;
	while(i < j)
	{
		do i ++; while(fang[i] < fang[x]);
		do j --; while(fang[j] > fang[x]);
		if(i < j) 
        {
            my_swap(&nums[i],&nums[j]);
            my_swap(&fang[i],&fang[j]);
        }
	}
	my_sort(nums,fang,l,j);
	my_sort(nums,fang,j+1,r);
}
int my_map(int *mapping,int x)
{
    int size=1;
    int sum=0;
    if(x>0)
    {
        while(x)
        {
            int t=x%10;
            x/=10;
            sum+=mapping[t]*size;
            size*=10;
        }
    }
    else
    {
        return mapping[0];
    }
    return sum;
    
}
/******************* 排序 *******************/
void sortJumbled(int *mapping, int *nums, int numsSize) {
    int *res_nums = (int *)malloc(numsSize * sizeof(int));
    // TODO
    int fang[numsSize];
    for(int i=0;i<numsSize;i++)
    {
        fang[i]=my_map(mapping,nums[i]);
    }
    my_sort(nums,fang,0,numsSize-1);
    for(int i=0;i<numsSize;i++)
    {
        res_nums[i]=nums[i];
    }
    for(int i = 0; i < numsSize; i++)
        printf("%d ", res_nums[i]);
    printf("\n");
}
/*****************************************************/


/******************* 读取数据 *******************/
void readInput(int **mapping, int **nums, int *numsSize) {
    scanf("%d", numsSize);

    *mapping = (int *)malloc(10 * sizeof(int));
    for (int i = 0; i < 10; i++) {
        scanf("%d", &((*mapping)[i]));
    }

    *nums = (int *)malloc((*numsSize) * sizeof(int));
    for (int i = 0; i < *numsSize; i++) {
        scanf("%d", &((*nums)[i]));
    }
}
/*****************************************************/

int main() {
    int *mapping, *nums, numsSize;
    readInput(&mapping, &nums, &numsSize);
    sortJumbled(mapping, nums, numsSize);

    return 0;
}