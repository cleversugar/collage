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
    printf("������Ԫ�ظ�����\n"); 
    scanf("%d",&n); 
    printf("������Ԫ�أ�\n");    
    for(i=n;i>0;--i)
    {
     
      //p=(LinkList) malloc (sizeof (LNode));
      scanf("%d",&x);
      p->next=(LinkList)malloc(sizeof(LNode));
      p->data=x;
	  p=p->next;
   	  
     
    }
    
 
 p->next=NULL;
    printf("������ɣ�\n"); 
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
       while (p->next&&j<i-1)//Ѱ�ҵ�i���ڵ㣬����pָ����ǰ�� 
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
     printf("ԭ����Ϊ��");      
     Print_L(L); 
     printf("������Ҫ�����λ��:\n");
     scanf("%d",&i);
     printf("������Ҫ���������:\n");
     scanf("%d",&e);
     L=Insert_L(L,i,e);
     Print_L(L);
     printf("������Ҫɾ����λ��:\n");
     scanf("%d",&i);
     L=Delete_L(L,i,e); 
     printf("��ɾ��������:%d\n",e);
     Print_L(L);
     system("pause");
} 
