#include <stdio.h>
#include <malloc.h>
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
#include <stdlib.h>

typedef struct
{
       int AA[100];
        int top;
        int front,rear;
}StateQueue;

main()
{
      StateQueue p;
      p.top=-1;
      p.front=0;
      p.rear=-1;
      int e;
      int i=0,n;
      printf("请输入字符串长度：\n");
      scanf("%d",&n);
      printf("请输入字符串：\n");
      for(i=0;i<n;i++)
      {
          scanf("%d",&e);
          p.top++;
          p.rear++;
          p.AA[p.rear]=e; 
          
      }
      for(i=0;i<n/2;i++)
      {
          if(p.AA[p.top]==p.AA[p.front])
          {
               p.top--;
               p.front++;
          }
          else 
          {
               printf("不是回文数！\n");
               break;
          }          
      }
      if(i>=n/2) printf("是回文数！\n");
      system("pause");
} 
      
