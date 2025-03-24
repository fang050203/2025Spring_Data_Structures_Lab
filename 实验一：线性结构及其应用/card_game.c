#include <stdio.h>

int main()
{
    int count=0;   //纸牌张数
    scanf("%d",&count);
    int size[count+1];   //定义记录牌的朝向的数组
    for(int i=1;i<=count;i++)
    {
        size[i]=1;  //全部初始化为正面
    }
    for(int i=2;i<=count;i++)
    {
        for(int j=i;j<=count;j++)     //两层for循环，遍历数组
        {
            if(!(j%i))
            {
                if(size[j])size[j]=0;   //翻转
                else size[j]=1;
            }
        }
    }

    int sum=0;   //统计总个数
    for(int i=1;i<=count;i++)
    {
        if(size[i])
        {
            printf("%d ",i);    //统计并输出正面的牌及个数
            sum++;
        }
    }
    printf("\n");
    printf("%d",sum);  //打印结果


}