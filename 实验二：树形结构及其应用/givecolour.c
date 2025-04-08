#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
 };


struct TreeNode* q[100010];
int top=0;

void midtravel(struct TreeNode* root)
{
    if(!root)return;
    midtravel(root->left);
    q[++top]=root;
    midtravel(root->right);
} 

/******************* 染色 *******************/
void getNumber(struct TreeNode* root, int** ops, int opsSize){
    // TODO
    int cnt=0;
    if(!root)
    {
        printf("%d",cnt);
        return;
    }
    midtravel(root);
    int check[top+1];
    for(int i=1;i<=top;i++)
    {
        check[i]=0;
    }
    for(int i=0;i<opsSize;i++)
    {
        if(ops[i][0])
        {
            int x=1,y=top;
            while(q[x++]->val<ops[i][1]);
            x--;
            while(q[y--]->val>ops[i][2]);
            y++;
            for(int i=x;i<=y;i++)
            {
                check[i]=1;
            }
        }
        else
        {
            int x=1,y=top;
            while(q[x++]->val<ops[i][1]);
            x--;
            while(q[y--]->val>ops[i][2]);
            y++;
            for(int i=x;i<=y;i++)
            {
                check[i]=0;
            }
        }
    }

    for(int i=1;i<=top;i++)
    {
        if(check[i])cnt++;
    }
    printf("%d",cnt);
}
/*****************************************************/

/******************* 读取数据 *******************/
struct TreeNode* newTreeNode(int val) {
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->val = val;
    node->left = node->right = NULL;
    return node;
}

struct TreeNode* constructTree(int size) {
    if (size == 0)
        return NULL;

    struct TreeNode** nodes = (struct TreeNode**)malloc(size * sizeof(struct TreeNode*));
    for (int i = 0; i < size; i++) {
        int val;
        scanf("%d", &val);
        if (val == -1) {
            nodes[i] = NULL;
        } else {
            nodes[i] = newTreeNode(val);
        }
    }

    for (int i = 0, j = 1; j < size; i++) {
        if (nodes[i] != NULL) {
            if (j < size)
                nodes[i]->left = nodes[j++];
            if (j < size)
                nodes[i]->right = nodes[j++];
        }
    }

    struct TreeNode* root = nodes[0];
    free(nodes);
    return root;
}

void readOps(int ***ops, int *opsSize) {
    scanf("%d", opsSize);
    *ops = (int **)malloc(*opsSize * sizeof(int *));
    while(getchar() != '[') {}
    for (int i = 0; i < *opsSize; i++) {
        (*ops)[i] = (int *)malloc(3 * sizeof(int));
        while(getchar() != '[') {}
        for (int j = 0; j < 3; j++) {
            scanf("%d", &((*ops)[i][j]));
        }
        while(getchar() != ']') {}
    }
}
/*****************************************************/

int main() {
    int nodeSize;
    scanf("%d", &nodeSize);
    struct TreeNode* root = constructTree(nodeSize);
    int **ops, opsSize;
    readOps(&ops, &opsSize);
    getNumber(root, ops, opsSize);

    return 0;
}