#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};


//自写，树节点构造
struct TreeNode* maketreenode(int x)
{
    struct TreeNode* TreeNode=(struct TreeNode*)malloc(sizeof(struct TreeNode));
    TreeNode->val=x;
    TreeNode->left=NULL;
    TreeNode->right=NULL;
    return TreeNode;
}


struct TreeNode* buildTree(int* preorder, int preorderSize, int* inorder, int inorderSize) {
    // TODO
    if(!preorderSize||!inorderSize)
    {
        return NULL;
    }

    int temp=*preorder;  //取到根节点
    struct TreeNode* TreeNode=maketreenode(temp);  //创建根节点

    int *l1=preorder;   //左子树前序遍历指针
    int *r1=preorder;   //右子树前序遍历指针
    int *l2=inorder;    //左子树中序遍历指针
    int *r2=inorder;   //右子树中序遍历指针

    int ls=preorderSize;    //左子树递归节点个数
    int rs=inorderSize;   //右子树递归节点个数

    int t=preorderSize;   //临时变量
    //接下来要给这几个变量正确赋值
    while((*r2)!=temp)
    {
        r2++;
        t--;
    }

    ls=preorderSize-t;   //左子树节点个数
    rs=t-1;   //右子树节点个数

    r2=inorder;  //初始化
    if(rs)
    {
        for(int i=0;i<ls+1;i++)
        {
            r2++;     //右子树中序遍历指针
        }
    }
    //else不动

    if(ls)
    {
        l1++;
    }
    //else不动


    if(rs)
    {
        for(int i=0;i<ls+1;i++)
        {
            r1++;
        }
    }
    //else不动



    TreeNode->left=buildTree(l1,ls,l2,ls);   //递归左子树
    TreeNode->right=buildTree(r1,rs,r2,rs);   //递归右子树
    return TreeNode;   //返回根节点
}

struct TreeNode* q[100010];
int hh=0;
int tt=-1;
void printTree(struct TreeNode* root) {
    // TODO
    q[++tt]=root;
    while(hh<=tt)
    {
        if(q[hh])
        {
            printf("%d ",q[hh]->val);
        }
        else
        {
            printf("null ");
        }
        if(q[hh])q[++tt]=q[hh]->left;
        if(q[hh])q[++tt]=q[hh]->right;
        q[hh++];
    }
}

int main() {
    int preorderSize;
    scanf("%d", &preorderSize);
    int* preorder = (int*)malloc(preorderSize * sizeof(int));
    for (int i = 0; i < preorderSize; i++) {
        scanf("%d", &preorder[i]);
    }

    int inorderSize = preorderSize;
    int* inorder = (int*)malloc(inorderSize * sizeof(int));
    for (int i = 0; i < inorderSize; i++) {
        scanf("%d", &inorder[i]);
    }

    struct TreeNode* root = buildTree(preorder, preorderSize, inorder, inorderSize);
    printTree(root);

    return 0;
}