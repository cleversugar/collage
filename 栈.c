#include <stdio.h>
#include <malloc.h>
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10

typedef struct{        
        int *base;
        int *top;
        int stacksize;
}SqStack;

SqStack Create(SqStack *S)
{
     int i,n;
     int e;
     S->base=(int*)malloc(STACK_INIT_SIZE*sizeof(int));
     S->top=S->base;
     S->stacksize=STACK_INIT_SIZE;
     printf("������Ҫ����ջ��Ԫ�ظ�����\n");
     scanf("%d",&n);
     if(n>=S->stacksize)
        S->base=(int*)realloc(S->base,(S->stacksize+STACKINCREMENT)*sizeof(int));
     for(i=0;i<n;i++)
       {
        printf("�������%d��Ԫ�أ�\n",i+1);
        scanf("%d",&e);
        *(S->top)=e;
        S->top=S->top+1;
        }
     return *S; 
}

int GetTop(SqStack *S,int e)
{
     //if(S->top==S->base)return 0;
     e=*(S->top-1);
     printf("ȡ��ջ��Ԫ�أ�%d\n",e);
     return e;
}

main()
{
      SqStack S;
      int e;
      S=Create(&S); 
      while(S.top!=S.base){
      e=GetTop(&S,e);S.top--;}
      system("pause"); 
}
     
      
