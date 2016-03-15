#include <stdio.h>
#include <stdlib.h>

typedef struct BiNode               //定义二叉树 
{
        char data;
        struct BiNode *Lchild;
        struct BiNode *Rchild; 
}BiNode,*BiTreeLink;

typedef struct                   //定义栈 
{
        BiTreeLink s[100];
        int  top;
}Stack;

BiTreeLink CreateBiTree(BiTreeLink T)//创建二叉树 
{
     char ch;
     ch=getchar();
     if(ch=='#')T=NULL;
     else{
          T=(BiNode *)malloc(sizeof(BiNode));
          T->data=ch;
          T->Lchild=CreateBiTree(T->Lchild);
          T->Rchild=CreateBiTree(T->Rchild);
          }
     return T;
}

void PreOrder(BiTreeLink T)//前序遍历 
{
    Stack S;
    BiTreeLink p;
    S.top=0;
    p=T;
    while(p||S.top)
   {
            while(p!=NULL)
            {
                     printf("%c",p->data);
                     S.s[S.top++]=p;
                     p=p->Lchild;
            }
   
             if(S.top>0)
            {
               p=S.s[--S.top];
               p=p->Rchild;
             } 
   }   
}

void InOrder(BiTreeLink T)//中序遍历 
{
    Stack S;
    BiTreeLink p;
    S.top=0;
    p=T;
    while(p||S.top)
   {
            while(p!=NULL)
            {
                    
                     S.s[S.top++]=p;
                     p=p->Lchild;
            }
   
             if(S.top>0)
            {  
               p=S.s[--S.top];
               printf("%c",p->data);
               p=p->Rchild;
             } 
   }   
}

void PostOrder(BiTreeLink T)//后序遍历 
{
 if(T)
     {
         PostOrder(T->Lchild);
         PostOrder(T->Rchild);
         printf("%c",T->data);
     }
}




main()
{
      BiTreeLink T;
      printf("生成二叉树：\n");
      T=CreateBiTree(T); 
      printf("前序遍历："); 
      PreOrder(T);
      printf("\n");
      printf("中序遍历："); 
      InOrder(T);
      printf("\n");
      printf("后序遍历："); 
      PostOrder(T);
      printf("\n");      
      system("pause");
}
