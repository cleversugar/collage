#include <stdio.h>
#include <stdlib.h>
#include<malloc.h>
typedef struct node
{
        int data;
        struct node *next;
}LNode,*LinkList;

LinkList CreateList_L(LinkList L)
{
    int i,n,x;
    LinkList p; 
    L=(LinkList) malloc (sizeof (LNode));
    
    p=L;
    printf("请输入元素个数：\n"); 
    scanf("%d",&n); 
    printf("请输入元素：\n");    
    for(i=n;i>0;--i)
    {
     
      //p=(LinkList) malloc (sizeof (LNode));
      scanf("%d",&x);
      p->next=(LinkList)malloc(sizeof(LNode));
      p->data=x;
	  p=p->next;
   	  
     
    }
    
 
 p->next=NULL;
    printf("输入完成！\n"); 
    return L;
}

void Print_L(LinkList L)
{
       LinkList p;
       p=L;
       while(p!=NULL)
       {
	   printf("%d\t",p->data);
	   p=p->next;
       } 
} 

LinkList Insert_L(LinkList L,int i,int e)
{
    LinkList p,s;
    p=L;
    int j=0;
    while(p&&j<i-1){p=p->next;++j;}
    if(!p||j>i-1)return 0;
    s=(LinkList)malloc(sizeof(LNode));
    s->data=e;
    s->next=p->next; 
    p->next=s;
    return L;
}

LinkList Delete_L(LinkList L,int i,int e)
{
       LinkList p,q;
       p=L;
       int j=0;
       while (p->next&&j<i-1)//寻找第i个节点，并由p指向其前驱 
       {  
           p=p->next;
           ++j;
       }
       q=p->next;
       p->next=q->next;
       e=q->data;
       free(q);
       return L;
}
       
             

int main()  
{
     LinkList L;
     int i,e;
     L=CreateList_L(L);
     printf("原链表为：");      
     Print_L(L); 
     printf("请输入要插入的位置:\n");
     scanf("%d",&i);
     printf("请输入要插入的数据:\n");
     scanf("%d",&e);
     L=Insert_L(L,i,e);
     Print_L(L);
     printf("请输入要删除的位置:\n");
     scanf("%d",&i);
     L=Delete_L(L,i,e); 
     printf("被删除的数据:%d\n",e);
     Print_L(L);
     system("pause");
} 
