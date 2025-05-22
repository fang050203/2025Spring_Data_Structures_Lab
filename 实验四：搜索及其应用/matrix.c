#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int dir[4][2]={0,1,1,0,-1,0,0,-1};

bool find(int** matrix,int x,int y,int matrixRowSize, int matrixColSize,int target)
{
    if(matrix[x][y]==target)return true;
    else if(matrix[x][y]>target)
    {
        y--;
        if(y<0)return false;
        else return find(matrix,x,y,matrixRowSize,matrixColSize,target);
    }
    else
    {
        x++;
        if(x==matrixRowSize)return false;
        else return find(matrix,x,y,matrixRowSize,matrixColSize,target);
    }
}
bool searchMatrix(int** matrix, int matrixRowSize, int matrixColSize, int target) {
    // TODO
    int x=0;
    int y=matrixColSize-1;
    return find(matrix,x,y,matrixRowSize,matrixColSize,target);
}

int main() {
    int m, n;
    scanf("%d %d", &m, &n);
    
    // 动态分配二维数组
    int** matrix = (int**)malloc(m * sizeof(int*));
    for (int i = 0; i < m; i++) {
        matrix[i] = (int*)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }
    
    int K;
    scanf("%d", &K);
    for (int i = 0; i < K; i++) {
        int target;
        scanf("%d", &target);
        
        bool found = searchMatrix(matrix, m, n, target);
        printf("%s\n", found ? "true" : "false");
    }
    
    // 释放内存
    for (int i = 0; i < m; i++) {
        free(matrix[i]);
    }
    free(matrix);
    
    return 0;
}