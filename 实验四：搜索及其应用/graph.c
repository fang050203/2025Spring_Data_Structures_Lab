
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

# define max_dis 100000

typedef char vextype[20];

typedef struct {
    int N, E;//N是顶点数，E是边数
    int** matrix;//储存邻接矩阵
    vextype* vertex;//存储节点的名字
} Graph;

Graph createGraph(int n);
int isConnected(Graph g);
void nodeDegree(Graph g, int* node_degree);
double clusteringCoefficient(Graph g);
int Diameter(Graph g);
int Radius(Graph g);
int dijkstra(Graph g, int start, int end, int* path);
void printPath(int d, int* diameter_path, Graph g);


/**
 * 创建一个节点数为n的图
 * @param n 节点个数
 * @return 返回这个图
 */
Graph createGraph(int n) {
    int i, j;
    Graph g;
    g.N = n;
    g.matrix = (int**)malloc(sizeof(int*) * g.N);
    for (i = 0; i < n; i++) {
        g.matrix[i] = (int*)malloc(sizeof(int) * g.N);
    }
    for (i = 0; i < g.N; i++) {
        for (j = 0; j < g.N; j++) {
            g.matrix[i][j] = max_dis;
        }
    }
    for (i = 0; i < g.N; i++) {
        g.matrix[i][i] = 0;
    }
    g.vertex = (vextype*)malloc(sizeof(vextype) * g.N);
    return g;
}


/**
 * 根据距离d和路径数组path输出路径，这样就不需要路径的节点数也能正确输出路径
 * @param d 路径长度
 * @param diameter_path 储存路径的数组
 * @param g 图
 */
void printPath(int d, int *diameter_path, Graph g)
{
    int k = 0;
    int path_length = 0;
    printf("Path: ");
    do {
        printf("%s->", g.vertex[diameter_path[k]]);
        path_length += g.matrix[diameter_path[k]][diameter_path[k + 1]];
        k++;
    } while (path_length < d);
    printf("%s\n", g.vertex[diameter_path[k]]);
}


/**
 * 判断图是否连通
 * @param g 图
 * @return 连通返回1，否则返回0
 */
int isConnected(Graph g) {
    //TODO
    int visited[g.N];
    for(int i=0;i<g.N;i++)
    {
        visited[i]=0;
    }
    dfs(0,g,visited);
    for(int i=0;i<g.N;i++)
    {
        if(!visited[i])
        {
            return 0;
        }
    }
    return 1;
}

//dfs判断图是否连通
void dfs(int x,Graph g,int *visited)
{
    for(int i=0;i<g.N;i++)
    {
        if(g.matrix[x][i]!=max_dis && i!=x && !visited[i])
        {
            visited[i]=1;
            dfs(i,g,visited);
        }
    }
}


/**
 * 计算每个点的度
 * @param g 图
 * @param node_degree 将每个点的度写到这个数组中
 */
void nodeDegree(Graph g, int *node_degree) {
    //TODO
    for(int i=0;i<g.N;i++)
    {
        int cnt=0;
        for(int j=0;j<g.N;j++)
        {
            if(g.matrix[i][j]!=max_dis && i!=j)cnt++;
        }
        node_degree[i]=cnt;
    }
}


/**
 * 计算图的聚类系数
 * @param g 图
 * @return 返回聚类系数
 */
/*double clusteringCoefficient(Graph g) {
    //TODO
    double sum=0;
    for(int i=0;i<g.N;i++)
    {
        int nei[g.N];
        double x=0;
        double a=0;
        double b=0;
        double n=0;
        for(int i=0;i<g.N;i++)
        {
            nei[i]=0;
        }
        for(int j=0;j<g.N;j++)
        {
            if(g.matrix[i][j]!=max_dis && i!=j)
            {
                nei[j]=1;
                n++;
            }
        }
        if(n==1)return 0;
        b=n*(n-1)/2;
        for(int )




        x=a/b;
        sum+=x;
    }
    return sum/g.N;
}*/



double clusteringCoefficient(Graph g) {
    double sum = 0;
    for (int i = 0; i < g.N; i++) {
        int nei[g.N];
        double a = 0, b = 0, n = 0;

        // 初始化邻接标记
        for (int j = 0; j < g.N; j++) {
            nei[j] = 0;
        }

        // 找到所有邻居
        for (int j = 0; j < g.N; j++) {
            if (g.matrix[i][j] != max_dis && i != j) {
                nei[j] = 1;
                n++;
            }
        }

        if (n < 2) continue;  // 少于两个邻居，聚类系数为0，不影响总和

        // 计算邻居之间实际的边数 a
        for (int j = 0; j < g.N; j++) {
            if (nei[j]) {
                for (int k = j + 1; k < g.N; k++) {
                    if (nei[k] && g.matrix[j][k] != max_dis) {
                        a++;
                    }
                }
            }
        }

        b = n * (n - 1) / 2.0;  // 理论最大边数
        sum += a / b;
    }

    return sum / g.N;  // 所有点聚类系数的平均值
}





/**
 * 使用dijkstra算法计算单源最短路径
 * @param g 图
 * @param start 起点
 * @param end 终点
 * @param path 从start到end的路径, [start,...,end]
 * @return 路径长度
 */
/*int dijkstra(Graph g, int start, int end, int *path)
{
    //TODO
    int minDist[g.N];
    int visited[g.N];
    for(int i=0;i<g.N;i++)
    {
        minDist[i]=max_dis;
        visited[i]=0;
    }
    minDist[start]=0;
    visited[start]=1;
    for(int i=0;i<g.N;i++)
    {
        int mind=max_dis;
        int cur=start;
        //第一步，找到距离原点最近且未被访问过的节点
        for(int j=0;j<g.N;j++)
        {
            if(minDist[j]<mind && !visited[j])
            {
                mind=minDist[j];
                cur=j;
            }
        }

        //第二步，标记该节点已经被访问
        visited[cur]=1;
        //第三步，更新到原点距离
        for(int j=0;j<g.N;j++)
        {
            if(!visited[j] && g.matrix[cur][j]!=max_dis && minDist[j] > minDist[cur]+g.matrix[cur][j])
            {
                minDist[j]=minDist[cur]+g.matrix[cur][j];
            }
        }
    }

}*/

int dijkstra(Graph g, int start, int end, int *path)
{
    int minDist[g.N];
    int visited[g.N];
    int prev[g.N]; // 新增：记录每个点的前驱节点

    for(int i = 0; i < g.N; i++) {
        minDist[i] = max_dis;
        visited[i] = 0;
        prev[i] = -1; // 初始没有前驱
    }

    minDist[start] = 0;

    for(int i = 0; i < g.N; i++) {
        int mind = max_dis;
        int cur = -1;

        // 找到距离起点最近的未访问节点
        for(int j = 0; j < g.N; j++) {
            if(minDist[j] < mind && !visited[j]) {
                mind = minDist[j];
                cur = j;
            }
        }

        if(cur == -1) break; // 所有能到达的点处理完

        visited[cur] = 1;

        // 更新所有邻接点的最短路径
        for(int j = 0; j < g.N; j++) {
            if(!visited[j] && g.matrix[cur][j] != max_dis && 
               minDist[j] > minDist[cur] + g.matrix[cur][j]) {
                minDist[j] = minDist[cur] + g.matrix[cur][j];
                prev[j] = cur; // 记录前驱
            }
        }
    }

    // 若无法到达终点
    if (minDist[end] == max_dis) return -1;

    // 回溯 path
    int stack[g.N]; // 临时栈
    int len = 0;
    for (int at = end; at != -1; at = prev[at]) {
        stack[len++] = at;
    }

    // 倒序写入 path
    for (int i = 0; i < len; i++) {
        path[i] = stack[len - i - 1];
    }

    return minDist[end];
}



/**
 * 计算图的直径。提示：Floyd算法
 * @param g 图
 * @return 直径的长度
 */
//int Diameter(Graph g) {
    //TODO
//}


/**
 * 计算图的半径
 * @param g 图
 * @return 半径长度
 */
//int Radius(Graph g) {
    //TODO
//}

            


int Diameter(Graph g) {
    int dist[g.N][g.N];

    // 初始化距离矩阵
    for (int i = 0; i < g.N; i++) {
        for (int j = 0; j < g.N; j++) {
            dist[i][j] = g.matrix[i][j];
            if (i == j) dist[i][j] = 0;
        }
    }

    // Floyd算法计算所有顶点对最短路径
    for (int k = 0; k < g.N; k++) {
        for (int i = 0; i < g.N; i++) {
            for (int j = 0; j < g.N; j++) {
                if (dist[i][k] != max_dis && dist[k][j] != max_dis &&
                    dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    int diameter = 0;
    // 找最长的最短路径
    for (int i = 0; i < g.N; i++) {
        for (int j = 0; j < g.N; j++) {
            if (dist[i][j] != max_dis && dist[i][j] > diameter) {
                diameter = dist[i][j];
            }
        }
    }

    return diameter;
}

int Radius(Graph g) {
    int dist[g.N][g.N];

    // 初始化距离矩阵
    for (int i = 0; i < g.N; i++) {
        for (int j = 0; j < g.N; j++) {
            dist[i][j] = g.matrix[i][j];
            if (i == j) dist[i][j] = 0;
        }
    }

    // Floyd算法计算所有顶点对最短路径
    for (int k = 0; k < g.N; k++) {
        for (int i = 0; i < g.N; i++) {
            for (int j = 0; j < g.N; j++) {
                if (dist[i][k] != max_dis && dist[k][j] != max_dis &&
                    dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    int radius = max_dis;
    // 对每个顶点i，找最大最短路径（离心率）
    for (int i = 0; i < g.N; i++) {
        int ecc = 0; // 离心率
        for (int j = 0; j < g.N; j++) {
            if (dist[i][j] != max_dis && dist[i][j] > ecc) {
                ecc = dist[i][j];
            }
        }
        if (ecc < radius) {
            radius = ecc;
        }
    }

    return radius;
}



int main() {
    int node_num;
    int edge_num;

    scanf("%d %d", &node_num, &edge_num);

    Graph g = createGraph(node_num);
    for(int i = 0; i < node_num; i++) {
        sprintf(g.vertex[i], "%d", i);
    }

    for (int i = 0; i < edge_num; i++) {
        int start_idx, end_idx, weight;
        scanf("%d %d %d", &start_idx, &end_idx, &weight);
        g.matrix[start_idx][end_idx] = weight;
        g.matrix[end_idx][start_idx] = weight;
    }
    printf("connected: %d\n", isConnected(g));

    int *degree = (int *)malloc(sizeof(int) * g.N);
    nodeDegree(g, degree);
    printf("degree distribution:\n");
    for(int i=0; i<g.N; i++)
    {
        printf("node%s:%d,", g.vertex[i], degree[i]);
    }
    printf("\n");
    double c = clusteringCoefficient(g);
    printf("clustering coefficient:%f\n", c);

    if (isConnected(g))
    {
        int* short_path = (int*)malloc(sizeof(int) * g.N);
        int dis = dijkstra(g, 1, 3, short_path);
        printf("the minimum fare between 1 and 3: %d\n", dis);
        printPath(dis, short_path, g);
        free(short_path);
        int d = Diameter(g);
        printf("diameter:%d\n", d);

        int r = Radius(g);
        printf("radius:%d\n", r);
    }

    return 0;
}