#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>


int flag=0;
typedef struct{
    int x;
    int y;
}pair;

typedef struct{
    int x;
    int y;
    int g;
    int h;
    int f;
}Node;



int dir[4][2]={0,1,1,0,0,-1,-1,0};
/* 使用DFS算法找到钥匙'$'，输出每次移动的方向以及最后的路径长度 */
int bfs(char **maze, int width, int height, int startX, int startY,int path,int visited[][height])
{
    int len[width][height];
    for(int i=0;i<width;i++)
    {
        for(int j=0;i<height;i++)
        {
            len[i][j]=0x7ffffff0;
        }
    }
    pair que[width*height];
    int hh=0,tt=-1;
    que[++tt].x=startX;
    que[tt].y=startY;
    len[startX][startY]=0;
    visited[startX][startY]=1;
    while(hh<=tt)
    {
        int x=que[hh].x;
        int y=que[hh++].y;        
        for(int i=0;i<4;i++)
        {
            int nex=x+dir[i][0];
            int ney=y+dir[i][1];
            if(nex <0 || ney <0 || nex ==width || ney == height || maze[nex][ney]=='1')continue;
            if(!visited[nex][ney])
            {
                que[++tt].x=nex;
                que[tt].y=ney;
                visited[nex][ney]=1;
                len[nex][ney]=len[x][y]+1;
                if(maze[nex][ney]=='$')return len[nex][ney];
            }
        }
    }
    return -1;
}




void findKey(char **maze, int width, int height, int startX, int startY,int visited[][height]) {
    // TODO
    if(maze[startX][startY]=='$')
    {
        flag=1;
        return;
    }

    for(int i=0;i<4;i++)
    {
        int nex=startX+dir[i][0];
        int ney=startY+dir[i][1];
        if(nex <0 || ney <0 || nex ==width || ney == height || maze[nex][ney]=='1')continue;

        if(!visited[nex][ney])
        {
            if(i==0)
            {
                printf("->R");
            }
            else if(i==1)
            {
                printf("->D");
            }
            else if(i==2)
            {
                printf("->L");
            }
            else
            {
                printf("->U");
            }   
            visited[nex][ney]=1;
            findKey(maze,width,height,nex,ney,visited);
            if(flag)return;
            if(i==0)
            {
                printf("->L");
            }
            else if(i==1)
            {
                printf("->U");
            }
            else if(i==2)
            {
                printf("->R");
            }
            else
            {
                printf("->D");
            }
        }   
    }
}


void take_bfs(char** maze,int width,int height,int startX,int startY,int visited[][height])
{     //调用bfs函数用
    printf("\n");
    //int visited[width][height];
    for(int i=0;i<width;i++)
    {
        for(int j=0;j<height;j++)
        {
            visited[i][j]=0;
        }
    }
    int x=bfs(maze,width,height,startX,startY,0,visited);
    printf("%d\n",x);
}







/* 返回两点之间的曼哈顿距离 */
int manhattan(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}



// 比较函数：用于优先队列的节点排序
int compareNodes(Node a, Node b) {
    if (a.f != b.f) return a.f < b.f;
    if (a.x != b.x) return a.x > b.x;
    return a.y > b.y;
}

void findDoor(char **maze, int width, int height, int startX, int startY, int endX, int endY, int visited[][height]) {
    // 初始化closed列表
    int **closed = (int **)malloc(width * sizeof(int *));
    for (int i = 0; i < width; i++) {
        closed[i] = (int *)calloc(height, sizeof(int));
    }
    // 父节点记录
    pair **parent = (pair **)malloc(width * sizeof(pair *));
    for (int i = 0; i < width; i++) {
        parent[i] = (pair *)malloc(height * sizeof(pair));
        for (int j = 0; j < height; j++) {
            parent[i][j].x = -1;
            parent[i][j].y = -1;
        }
    }
    // 优先队列动态数组
    Node *openList = (Node *)malloc(width * height * sizeof(Node));
    int openSize = 0;
    // 初始化起始节点
    Node start;
    start.x = startX;
    start.y = startY;
    start.g = 0;
    start.h = manhattan(startX, startY, endX, endY);
    start.f = start.g + start.h;
    openList[openSize++] = start;
    // 扩展顺序记录
    pair expanded[width * height];
    int expandedCount = 0;
    // 路径记录
    pair path[width * height];
    int pathLength = 0;
    int found = 0;
    while (openSize > 0) {
        // 找到优先级最高的节点（f最小，x大优先，y大次优）
        int bestIdx = 0;
        for (int i = 1; i < openSize; i++) {
            if (compareNodes(openList[i], openList[bestIdx])) {
                bestIdx = i;
            }
        }
        Node current = openList[bestIdx];
        // 从open列表中移除该节点
        for (int i = bestIdx; i < openSize-1; i++) {
            openList[i] = openList[i+1];
        }
        openSize--;
        // 记录扩展顺序
        expanded[expandedCount++] = (pair){current.x, current.y};
        // 找到出口，回溯路径
        if (current.x == endX && current.y == endY) {
            pair p = {current.x, current.y};
            while (p.x != startX || p.y != startY) {
                path[pathLength++] = p;
                p = parent[p.x][p.y];
            }
            path[pathLength++] = p; // 添加钥匙节点
            // 反转路径
            for (int i = 0; i < pathLength/2; i++) {
                pair tmp = path[i];
                path[i] = path[pathLength-1-i];
                path[pathLength-1-i] = tmp;
            }
            found = 1;
            break;
        }
        closed[current.x][current.y] = 1;
        // 扩展四个方向
        for (int d = 0; d < 4; d++) {
            int nx = current.x + dir[d][0];
            int ny = current.y + dir[d][1];
            if (nx < 0 || ny < 0 || nx >= width || ny >= height || maze[nx][ny] == '1') 
                continue;
            if (closed[nx][ny]) continue;
            // 计算新g值
            int tentative_g = current.g + 1;
            int inOpen = 0;
            int idx = -1;
            // 检查是否在open列表中
            for (int i = 0; i < openSize; i++) {
                if (openList[i].x == nx && openList[i].y == ny) {
                    inOpen = 1;
                    idx = i;
                    break;
                }
            }
            // 更新或添加节点
            if (inOpen) {
                if (tentative_g < openList[idx].g) {
                    openList[idx].g = tentative_g;
                    openList[idx].f = openList[idx].g + openList[idx].h;
                    parent[nx][ny] = (pair){current.x, current.y};
                }
            } else {
                Node newNode;
                newNode.x = nx;
                newNode.y = ny;
                newNode.g = tentative_g;
                newNode.h = manhattan(nx, ny, endX, endY);
                newNode.f = newNode.g + newNode.h;
                parent[nx][ny] = (pair){current.x, current.y};
                openList[openSize++] = newNode;
            }
        }
    }
    // 输出扩展顺序
    if (expandedCount > 0) {
        printf("->(%d,%d", expanded[0].x, expanded[0].y);
        for (int i = 1; i < expandedCount; i++) {
            printf(")->(%d,%d", expanded[i].x, expanded[i].y);
        }
        printf(")\n");
    } else {
        printf("\n");
    }
    // 输出路径
    if (found) {
        printf("->(%d,%d", path[0].x, path[0].y);
        for (int i = 1; i < pathLength; i++) {
            printf(")->(%d,%d", path[i].x, path[i].y);
        }
        printf(")\n");
    } else {
        printf("\n");
    }
    // 释放内存
    for (int i = 0; i < width; i++) {
        free(closed[i]);
        free(parent[i]);
    }
    free(closed);
    free(parent);
    free(openList);
}





int main() {
    int width, height;
    scanf("%d %d\n", &width, &height);
    char **maze = (char **)malloc(width * sizeof(char *));
    for(int i = 0; i < width; i++) {
        maze[i] = (char *)malloc(height * sizeof(char));
        scanf("%s", maze[i]);
    }
    
    int startX = 0, startY = 0;
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            if (maze[i][j] == '*') {
                startX = i;
                startY = j;
            }
        }
    }

    //避免重复访问
    int visited[width][height];
    for(int i=0;i<width;i++)
    {
        for(int j=0;j<height;j++)
        {
            visited[i][j]=0;
        }
    }

    visited[startX][startY]=1;
    findKey(maze, width, height, startX, startY,visited);
    take_bfs(maze, width, height, startX, startY,visited);


    int endX = 0, endY = 0;
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            if (maze[i][j] == '$') {
                startX = i;
                startY = j;
            }
            if (maze[i][j] == '#') {
                endX = i;
                endY = j;
            }
        }
    }

    for(int i=0;i<width;i++)
    {
        for(int j=0;j<height;j++)
        {
            visited[i][j]=0;
        }
    }

    findDoor(maze, width, height, startX, startY, endX, endY,visited);
    
    for(int i = 0; i < width; i++) {
        free(maze[i]);
    }
    free(maze);
    return 0;
}