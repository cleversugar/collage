#include <stdio.h>
#include <stdlib.h>

typedef struct BiNode               //��������� 
{
        char data;
        struct BiNode *Lchild;
        struct BiNode *Rchild; 
}BiNode,*BiTreeLink;

typedef struct                   //����ջ 
{
        BiTreeLink s[100];
        int  top;
}Stack;

BiTreeLink CreateBiTree(BiTreeLink T)//���������� 
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

void PreOrder(BiTreeLink T)//ǰ����� 
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

void InOrder(BiTreeLink T)//������� 
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

void PostOrder(BiTreeLink T)//������� 
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
      printf("���ɶ�������\n");
      T=CreateBiTree(T); 
      printf("ǰ�������"); 
      PreOrder(T);
      printf("\n");
      printf("���������"); 
      InOrder(T);
      printf("\n");
      printf("���������"); 
      PostOrder(T);
      printf("\n");      
      system("pause");
}
