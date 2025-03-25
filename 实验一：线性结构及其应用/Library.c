#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//=============图书信息结构体定义================

typedef struct {
    char bookID[20];   //书号，长度小于20
    char title[100];  //书名，长度小于100
    char author[50];  //作者，长度小于50
    int stock;     //库存数量
}Book;



//===============定义链表节点=================


typedef struct Node{      //图书节点链表定义
    Book book;      //定义图书信息
    struct Node *next;    //只向下一个节点的定义
}Node;



//==========================定义函数===========================


//=======================5.根据书号查找图书信息==================
Node *my_FindBook (Node *head,char bookid[])
{
    if(head)
    {
        Node *temp=head;  //定义临时头结点，用于查找
        while((strcmp(temp->book.bookID,bookid)!=0)&&temp)temp=temp->next;   //查找直到找到与bookid匹配的节点,或者查找到末尾节点停止循环
        if(temp)   //当temp->next不为空
        {
            return temp;   //查找到节点，直接返回
        }
        else
        {
            return NULL;  //没找到节点，返回NULL
        }
    }
    else
    {
        return NULL;    //头结点为空，直接返回NULL
    }
}




//=======================1.创建新链表节点==================
Node* CreateNode(Book book)
{
    Node *new_node=(Node*)malloc(sizeof(Node)); //申请内存
    if(!new_node)     //申请内存失败异常情况处理
    {
        printf("malloc eroor!");    //打印错误信息
        exit(1);   //退出程序
    }
    else
    {
        new_node->book=book;   //初始化图书信息
        new_node->next=NULL;  //指针指向空
        return new_node;    //返回指针
    }
}


//=======================2.在链表尾部插入图书信息==================

void InsertBook(Node **head,Book book)
{
    Node* new_node=CreateNode(book);  //创建新节点
    if(*(head))    //如果链表不空
    {
        Node* temp=*head;  //创建临时头指针
        while(temp->next)temp=temp->next;//找到末尾节点
        temp->next=new_node;    //在尾部插入节点
    }
    else
    {
        *head=new_node;     //直接令头结点指向新建节点
    }
}



//=======================3.根据书号删除图书信息==================
int DeleteBook(Node **head,char bookid[])
{
    if(*(head))
    {
        Node *temp =NULL;  
        temp =my_FindBook(*head,bookid);   //找到图书信息节点
        if(!temp)
        {
            return 0;
        }
        else
        {
            if(temp==*head)
            {
                printf("图书%s删除成功！\n",temp->book.bookID);
                *head=(*head)->next;
                free(temp);
                return 1;
            }
            else
            {
                printf("图书%s删除成功！\n",temp->book.bookID);
                Node *t=*head;  //定义临时头结点
                while(t->next!=temp)t=t->next;
                t->next=temp->next;
                free(temp);
                return 1;
            }
        }
    }
    else
    {
        return 0;
    }

}



//=======================4。根据书号修改图书库存数量==================

int UpdateStock(Node *head,char bookid[],int newStock)
{
    Node *temp=head;   //定义临时头结点
    while(temp)
    {
        if(!(strcmp(temp->book.bookID,bookid)))
        {
            temp->book.stock=newStock;
            printf("图书%s的库存数量已修改为%d！\n",temp->book.bookID,temp->book.stock);
            return 1;
        }
        else
        {
            temp=temp->next;
        }
    }
    return 0;
}
//=======================5.根据书号查找图书信息==================
Node *FindBook (Node *head,char bookid[])
{
    if(head)
    {
        Node *temp=head;  //定义临时头结点，用于查找
        while(temp&&(strcmp(temp->book.bookID,bookid)!=0))temp=temp->next;   //查找直到找到与bookid匹配的节点,或者查找到末尾节点停止循环
        if(temp)   //当temp->next不为空
        {
            printf("查找的图书信息：\n");
            printf("书号：%s,书名：%s,作者：%s,库存：%d",temp->book.bookID,temp->book.title,temp->book.author,temp->book.stock);
            printf("\n");  //换行
            return temp;   //查找到节点，直接返回
        }
        else
        {
            return NULL;  //没找到节点，返回NULL
        }
    }
    else
    {
        return NULL;    //头结点为空，直接返回NULL
    }
}
//=======================6.遍历并输出所有图书信息==================
void TraverseList(Node *head)
{
    if(head)
    {
        Node *temp=head;  //定义临时头结点
        printf("图书列表：\n");
        while(temp)
        {
            printf("书号：%s,书名：%s,作者：%s,库存：%d",temp->book.bookID,temp->book.title,temp->book.author,temp->book.stock);
            printf("\n");
            temp=temp->next;
        }
    }
}


int main(){
    Node *head = NULL; // 链表头节点
    char bookId_find[4], bookId_update[4], bookId_delete[4];
    int num;
    scanf("%s", bookId_find);
    scanf("%s", bookId_update);
    scanf("%d", &num);
    scanf("%s", bookId_delete);

    // 添加图书信息
    Book book1 = {"001", "C程序设计", "谭浩强", 10};
    Book book2 = {"002", "数据结构", "严蔚敏", 5};
    Book book3 = {"003", "算法导论", "Thomas H. Cormen", 3};
    InsertBook(&head, book1);
    InsertBook(&head, book2);
    InsertBook(&head, book3);

    // 查找图书信息
    FindBook(head, bookId_find);

    // 修改图书库存数量
    UpdateStock(head, bookId_update, num);

    // 删除图书信息
    DeleteBook(&head, bookId_delete);

    // 遍历输出图书列表
    TraverseList(head);

    return 0;
}
