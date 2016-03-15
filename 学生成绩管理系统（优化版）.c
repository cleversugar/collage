#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Student//学生类型（链表实现） 
{
        int Sno;//学号  
        char Sname[10];//姓名 
        int Chinese;
        int Math;
        int English;
        int Computer;
        struct Student *next;
}Student;

typedef struct Grade//分数类型（二叉平衡树） 
{
        int score;//分数
        struct Student* head;//学生 
        int ltag,ldata,rdata,LH,RH;//ltag为标志,ldata,rdata,LH,RH分别为左数据，右数据，左深度和右深度值
	    struct Grade *lchild,*rchild;
}Grade;

void ShowMainMenu()//显示菜单函数 
{
     printf("             ------------------------------------------------------\n\n"); 
     printf("             -------------* 欢迎进入学生成绩查询系统 *-------------\n");
     printf("\n");
     printf("                              *  1.录入学生成绩\n"); 
     printf("                              *  2.插入学生成绩\n");
     printf("                              *  3.输出学生成绩\n");
     printf("                              *  4.查找学生信息\n");
     printf("                              *  5.删除学生信息\n");
     printf("                              *  6.统计学生信息\n\n");
     printf("             ------------------------------------------------------\n\n\n");  
     printf("    请注意：录入功能可以批量录入学生成绩；插入功能只能录入一个学生的成绩；输出功能可以输出所有学生信息，并实现成绩从低到高排列；查找功能可以查找一个学生的成绩或查找任意分数段的学生信息；删除功能为删除某一学生的成绩；统计功能为统计学生总人数并显示各分数段的学生人数及平均分。\n\n"); 
}

int depth(Grade *p)//求深度函数
{
	int H=1;//深度 
	while(p!=NULL)
	{
		if(p->ldata>p->rdata)//左边的数据大于右边的则往左边走
		{
			H++;
			p=p->lchild;
		}
		else if(p->ldata<=p->rdata)//左边的数据小于或等于右边的则往右边走
		{
			H++;
			p=p->rchild;
		}
	}
	return  H;
}

Grade* judge(Grade *T)//判断是否为平衡二叉树
{
	Grade *q[20],*p,*r;
	int top=-1,m;
	p=T;
	while(p!=NULL)
	{
		q[++top]=p;
		p->ltag=1;
		p=p->lchild;
	}
	while(top!=-1)
	{
		p=q[top];
		r=p;
		if(p->rchild!=NULL && p->ltag!=-1)
		{
			p->ltag=-1;
			p=p->rchild;
			q[++top]=p;
			p->ltag=1;
		}
		else
		{
			--top;
			r->LH=depth(r->lchild);
			r->RH=depth(r->rchild);
			r->ltag=0;
			m=r->LH-r->RH;
			if(m<-1 || m>1)
			{
				r->ltag=2;//ltag为2标志为此树不平衡
				return r;
			}
		}
		while(p->lchild!=NULL && p->ltag!=0)
		{
			p=p->lchild;
			q[++top]=p;
			p->ltag=1;
		}
	}
	T ->ltag=3;//ltag为3标志为此树平衡
	return T;
}

Grade* adjust(Grade *T,Grade *p)//调整为平衡二叉树
{
	Grade *q,*r,*s,*t;
	int m;
	//寻找p的前驱结点
	t=T;
	while(t!=p)
	{
		s=t;
		if(t->score<p->score)
			t=t->rchild;
		else if(t->score>p->score)
			t=t->lchild;
	}
	q=p->lchild;
	r=p->rchild;
	p->LH=depth(p->lchild);//返回左子树深度
	p->RH=depth(p->rchild);//返回右子树深度
	m=p->LH-p->RH;
	if(m==2)
	{
		q->LH=depth(q->lchild);
		q->RH=depth(q->rchild);
		m=q->LH-q->RH;
		if(m==1)//LL型调整
		{
			p->lchild=q->rchild;
			q->rchild=p;
			p->ldata=q->rdata;
			q->rdata=q->rdata+p->rdata+1;
			if(t==T)
				T=q;
			else
			{
				if(t->score<s->score)
					s->lchild=q;
				else
					s->rchild=q;
			}
			return T;
		}
		else//LR型调整
		{
			r=q->rchild;
			q->rchild=r->lchild;
			p->lchild=r->rchild;
			r->lchild=q;
			r->rchild=p;
			q->rdata=r->ldata;
			r->ldata=q->ldata+r->ldata+1;
			p->ldata=r->rdata;
			r->rdata=p->ldata+p->rdata+1;
			if(t==T)
				T=r;
			else
			{
				if(t->score<s->score)
					s->lchild=r;
				else
					s->rchild=r;
			}
			return T;
		}
	}
	else
	{
		r->LH=depth(r->lchild);
		r->RH=depth(r->rchild);
		m=r->LH-r->RH;
		if(m==1)//RL型调整
		{
			q=r->lchild;
			p->rchild=q->lchild;
			r->lchild=q->rchild;
			q->lchild=p;
			q->rchild=r;
			p->rdata=q->ldata;
			r->ldata=q->rdata;
			q->ldata=p->ldata+p->rdata+1;
			q->rdata=r->ldata+r->rdata+1;
			if(t==T)
				T=q;
			else
			{
				if(t->score<s->score)
					s->lchild=q;
				else
					s->rchild=q;
			}
			return T;
		}
		else//RR型调整
		{
			p->rchild=r->lchild;
			r->lchild=p;
			p->rdata=r->ldata;
			r->ldata=p->ldata+p->rdata+1;
			if(t==T)
				T=r;
			else
			{
				if(t->score<s->score)
					s->lchild=r;
				else
					s->rchild=r;
			}
			return T;
		}
	}
}

Grade* creatGrade(Grade *T)//建立二叉树
{
    int No(Grade *T,int no);//函数说明，重复学号将被提示 
    int tag;//是否为重复学号的标志 
    int k;
	Grade *p,*q,*r;	
    Student *s;	
	r=(Grade*)malloc(sizeof(Grade));
	s=(Student*)malloc(sizeof(Student));
	char f;//排除不必要的回车等字符对变量输入的影响 	
    scanf("%d",&s->Sno);
    tag=No(T,s->Sno);
    if(tag==1)
    {
        printf("该学号已存在，请查证后输入！\n");
        printf("查证后请输入："); 
        scanf("%d",&s->Sno); 
    }
    printf("请输入该生姓名：");
    f=getchar(); 
    scanf("%s",s->Sname); 
    f=getchar(); 
    printf("请输入该生的语文成绩(0~100)：");
	scanf("%d",&s->Chinese);
	while(s->Chinese>100|s->Chinese<0)//分数在0以下或者100以上 
    {
       printf("该分数为无效分数，请重新输入！\n该生的分数为：");
       scanf("%d",&s->Chinese);
    } 
    printf("请输入该生的数学成绩(0~100)：");
	scanf("%d",&s->Math);
	while(s->Math>100||s->Math<0)//分数在0以下或者100以上 
    {
       printf("该分数为无效分数，请重新输入！\n该生的分数为：");
       scanf("%d",&s->Math);
    } 
    printf("请输入该生的英语成绩(0~100)：");
	scanf("%d",&s->English);
	while(s->English>100||s->English<0)//分数在0以下或者100以上 
    {
       printf("该分数为无效分数，请重新输入！\n该生的分数为：");
       scanf("%d",&s->English);
    } 
    printf("请输入该生的计算机成绩(0~100)：");
	scanf("%d",&s->Computer); 
    while(s->Computer>100||s->Computer<0)//分数在0以下或者100以上 
    {
       printf("该分数为无效分数，请重新输入！\n该生的分数为：");
       scanf("%d",&s->Computer);
    }      
    s->next=NULL;
	r->head=s;
	r->ldata=0;
	r->rdata=0;
    k=s->Chinese+s->Math+s->English+s->Computer;  
   	r->score=k;	
	r->lchild=NULL;
	r->rchild=NULL;	
	if(T==NULL)//为空时添加必然为平衡树，不需要判断平衡与否 
	{
		T=r;
		return T;
	}
	p=T;
	while(p!=NULL)
	{
		q=p;
		if(p->score<k)
		{
	     	p->rdata++;//左数据加1
			p=p->rchild;
		}
		else if(p->score>k)
		{
		    p->ldata++;//右数据加1
			p=p->lchild;
		}
		else if(p->score==k)//在链表上插入，不影响二叉树平衡，也不需要判断平衡 
		{
            if(p->head==NULL)                      
		     	p->head=s;
			else
            {
                s->next=p->head;
                p->head=s;
            }               
			return T;
		}
	}
	if(q->score<k)
		q->rchild=r;
	else
		q->lchild=r;
    p=judge(T);//判断是否为平衡二叉树
	if(p->ltag==2)//此二叉树不平衡时
	T=adjust(T,p);//调整为平衡二叉树
	return T;
}

void ShowAll(Grade *T)//遍历二叉树（采用中序遍历实现成绩的从低到高输出） 
{
     Grade *stack[100];
     int top=0;
     Grade *p;
     p=T;
     Student *q;
     while(p||top)
     {                  
            while(p)
            {
                    stack[top++]=p;                                     
                    p=p->rchild;
            }
            if(top>0)
            {
                     p=stack[--top];
                     q=p->head; 
                     while(q)
                     {                          
                          printf("%d\t%s\t%d\t%d\t%d\t%d\t%d\n",q->Sno,q->Sname,q->Chinese,q->Math,q->English,q->Computer,p->score);
                          q=q->next;
                     }                                                              
                     p=p->lchild;                     
            }
     }
}

void PreShowAll(Grade *T)//二叉树的先序遍历，只用于测试平衡，与成绩管理系统无关 
{
     Grade *stack[100];
     int top=0;
     Grade *p;
     p=T;
     Student *q;
     while(p||top)
     {                  
            while(p)
            {                     
                    q=p->head; 
                    while(q)
                     {                          
                          printf("%d\t%s\t%d\t%d\t%d\t%d\t%d\n",q->Sno,q->Sname,q->Chinese,q->Math,q->English,q->Computer,p->score);
                          q=q->next;
                     } 
                    stack[top++]=p;                                                        
                    p=p->lchild;
            }
            if(top>0)
            {
                     p=stack[--top];                 
                     p=p->rchild;                     
            }
     }
}

int No(Grade *T,int no)//无输出遍历，采用非递归,检验重复学号 
{
     int tag; 
     int top=0;
     Grade *p,*stack[100];
     Student *q;
     p=T;     
     while(p||top)
     {
                  
            while(p)
            {
                    stack[top++]=p;
                    q=p->head;
                    while(q&&q->Sno!=no)q=q->next;
                    if(q)
                    tag=1;                    
                    p=p->lchild;
            }
            if(top>0)
            {
                     p=stack[--top];
                     q=p->head;                   
                     p=p->rchild;
            }
     }    
    return tag;    
}

void NoSearch(Grade *T,int nosearch)//按照学号查找某个学生 
{
    Student *p; 
    if(T)
    {
         p=T->head;
         while(p&&p->Sno!=nosearch)p=p->next;
         if(p)        
              printf("%s同学成绩：\n语文成绩为：%d\n数学成绩为：%d\n英语成绩为：%d\n计算机成绩为：%d\n总分为：%d\n\n",p->Sname,p->Chinese,p->Math,p->English,p->Computer,T->score);
         NoSearch(T->lchild,nosearch);
         NoSearch(T->rchild,nosearch);
    }    
}

void NaSearch(Grade *T,char nasearch[10])//按照姓名查找某个学生 
{
    Student *p; 
    if(T)
    {
         p=T->head;         
         while(p&&strcmp(p->Sname,nasearch)!=0)p=p->next;
         if(p)
              printf("%s同学成绩：\n语文成绩为：%d\n数学成绩为：%d\n英语成绩为：%d\n计算机成绩为：%d\n总分为：%d\n\n",p->Sname,p->Chinese,p->Math,p->English,p->Computer,T->score);
         NaSearch(T->lchild,nasearch);
         NaSearch(T->rchild,nasearch);
    }    
}

void ScoreSearch(Grade*T,int low,int high)
{
    //Grade *q;
    Student *p; 
    if(T)
    {
         p=T->head;         
         while(p&&T->score>=low&&T->score<=high)
         {
             printf("%d\t\t%s\t\t%d\n",p->Sno,p->Sname,T->score);
             p=p->next;
         }
         ScoreSearch(T->lchild,low,high);
         ScoreSearch(T->rchild,low,high);
    } 
}

Grade* dele(Grade *T,Grade *p,Grade *r)//删除某个树节点 
{
	Grade *q,*child;
	if(p->lchild&&p->rchild)//左右子树均不为空
	{
		q=r=p;
		p=p->rchild;
		q->score=p->score;
		q->head=p->head;
	}
	if(p->lchild)//左子树不为空
		child=p->lchild;
	else//左子树为空
		child=p->rchild;
	if(!r)
		T=child;
	else if(p==r->lchild)
		r->lchild=child;
	else
		r->rchild=child;
	free(p);
	return T;
}

Grade* Delnode(Grade *T,int e)//删除成绩
{    
    Grade *p,*r;
    p=T;
	r=NULL;
	while(p&&p->score!=e)
	{
		r=p;
		if(e<p->score)
		{
            p->ldata--;
			p=p->lchild;
        }
		else
		{
            p->rdata--;
			p=p->rchild;
        }
	}
	if(!p)
		printf("没有该生的成绩");
	else
		T=dele(T,p,r);
		return T; 
}

Grade* NaDelete(Grade *T,char nadel[10])//删除某个学生(按照姓名） 
{
     Grade *stack[100];
     int top=0;
     Grade *p,*ppre;//*pper记录p的双亲,*m是在有双支结点的删除时的p的左孩子，最终成为p的前驱
     p=T;
     Student *q,*qpre;//*qper记录q的前驱      
     while(p||top)
     {                  
            while(p)
            {
                    stack[top++]=p;
                    ppre=p;                                     
                    p=p->lchild;
            }
           if(top>0)
            {
                     p=stack[--top];
                     q=p->head; 
                     while(q&&strcmp(q->Sname,nadel)!=0)
                     {                         
                        qpre=q;                     
                        q=q->next;
                     } 
                     if(q)// 找到要删除的学生的学号
                     {
                           //考虑头结点链接不知一个学生的删除 
                           if(p->head->next) 
                           {
                               if(p->head!=q)
                                {
                                    qpre->next=q->next;
                                    free (q); 
                                }
                                else
                                {
                                    p->head=p->head->next;
                                    free(q);
                                } 
                                return T;                 
                           }
                           else  //head为空，该分数没有存在的意义，所以要删除树节点 
                           {
                                T=Delnode(T,p->score);                                                                         
                           }       
                      }                                                          
                     p=p->rchild;                     
            }
     }
     return T;
}

Grade* NoDelete(Grade *T,int nodel)//删除某个学生（按照学号） 
{
     Grade *stack[100];
     int top=0;
     Grade *p,*ppre,*parent;//*pper记录p的双亲,*m是在有双支结点的删除时的p的左孩子，最终成为p的前驱,parent为根的父节点，避免删除根的可能 
     p=T;
     Student *q,*qpre;//*qper记录q的前驱      
     while(p||top)
     {                  
            while(p)
            {
                    stack[top++]=p;
                    ppre=p;                                     
                    p=p->lchild;
            }
           if(top>0)
            {
                     p=stack[--top];
                     q=p->head; 
                     while(q&&q->Sno!=nodel)
                     {                         
                        qpre=q;                     
                        q=q->next;
                     } 
                     if(q)// 找到要删除的学生的学号
                     {
                           //考虑头结点的删除 
                           if(p->head->next) 
                           {
                                if(p->head!=q)
                                {
                                    qpre->next=q->next;
                                    free (q); 
                                }
                                else
                                {
                                    p->head=p->head->next;
                                    free(q);
                                }                
                           }                           
                           else  //head为空，该分数没有存在的意义，所以要删除树节点 
                           {                              
                              T=Delnode(T,p->score);                                           
                           }       
                      }                                                          
                     p=p->rchild;                      
            }
     }
     p=judge(T);//判断是否为平衡二叉树
	 if(p->ltag==2)//此二叉树不平衡时
     T=adjust(T,p);//调整为平衡二叉树
     return T;
}

void Statistics(Grade *T)//统计各个分数段的学生人数
{
     int ca=0,ma=0,ea=0,cpa=0;     
     int cb=0,mb=0,eb=0,cpb=0;
     int cc=0,mc=0,ec=0,cpc=0;
     int cd=0,md=0,ed=0,cpd=0;
     int ce=0,me=0,ee=0,cpe=0;
     int n=0;//总人数
     int sum=0;//总分
     int Sc=0,Sm=0,Se=0,Scp=0;//各科总分 
     float ave;//平均分 
     float Ac,Am,Ae,Acp;//各科平均分 
     Grade *stack[100],*p;
     int top=0;
     Student *q;
     p=T;     
     while(p||top)
     {
                  
            while(p)
            {
                    stack[top++]=p;
                    q=p->head;
                    while(q)
                    {
                        if(q->Chinese=90&&q->Chinese<=100){ca++;Sc=Sc+q->Chinese;}
                        if(q->Chinese=80&&q->Chinese<=89){cb++;Sc=Sc+q->Chinese;}
                        if(q->Chinese=70&&q->Chinese<=79){cc++;Sc=Sc+q->Chinese;}
                        if(q->Chinese=60&&q->Chinese<=69){cd++;Sc=Sc+q->Chinese;}
                        if(q->Chinese=0&&q->Chinese<=59){ce++;Sc=Sc+q->Chinese;}
                        if(q->Math=90&&q->Math<=100){ma++;Sm=Sm+q->Math;}
                        if(q->Math=80&&q->Math<=89){mb++;Sm=Sm+q->Math;}
                        if(q->Math=70&&q->Math<=79){mc++;Sm=Sm+q->Math;}
                        if(q->Math=60&&q->Math<=69){md++;Sm=Sm+q->Math;}
                        if(q->Math=0&&q->Math<=59){me++;Sm=Sm+q->Math;}
                        if(q->English=90&&q->English<=100){ea++;Se=Se+q->English;}
                        if(q->English=80&&q->English<=89){eb++;Se=Se+q->English;}
                        if(q->English=70&&q->English<=79){ec++;Se=Se+q->English;}
                        if(q->English=60&&q->English<=69){ed++;Se=Se+q->English;}
                        if(q->English=0&&q->English<=59){ee++;Se=Se+q->English;}
                        if(q->Computer=90&&q->Computer<=100){cpa++;Scp=Scp+q->Computer;}
                        if(q->Computer=80&&q->Computer<=89){cpb++;Scp=Scp+q->Computer;}
                        if(q->Computer=70&&q->Computer<=79){cpc++;Scp=Scp+q->Computer;}
                        if(q->Computer=60&&q->Computer<=69){cpd++;Scp=Scp+q->Computer;}
                        if(q->Computer=0&&q->Computer<=59){cpe++;Scp=Scp+q->Computer;}
                        n++;
                        sum=sum+p->score;
                        q=q->next;
                    }
                    p=p->lchild;
            }
            if(top>0)
            {
                     p=stack[--top];
                     q=p->head;                   
                     p=p->rchild;
            }
     }
     ave=sum/n;
     Ac=Sc/n;
     Am=Sm/n;
     Ae=Se/n;
     Acp=Scp/n;
     printf("分数统计：\n");
     printf("总学生数为%d人\n\n",n);
     printf("语文成绩信息：\n"); 
     printf("分数在90分以上的学生人数为：%d人\n",ca);
     printf("分数在80分到89分之间的学生人数为：%d人\n",cb);  
     printf("分数在70分到79分之间的学生人数为：%d人\n",cc); 
     printf("分数在60分到69分之间的学生人数为：%d人\n",cd); 
     printf("分数在60分以下的学生人数为：%d人\n",ce);
     printf("平均分(保留两位小数)为%.2f\n\n",Ac);
     printf("数学成绩信息：\n");      
     printf("分数在90分以上的学生人数为：%d人\n",ma);
     printf("分数在80分到89分之间的学生人数为：%d人\n",mb);  
     printf("分数在70分到79分之间的学生人数为：%d人\n",mc); 
     printf("分数在60分到69分之间的学生人数为：%d人\n",md); 
     printf("分数在60分以下的学生人数为：%d人\n",me);
     printf("平均分(保留两位小数)为%.2f\n\n",Am);
     printf("英语成绩信息：\n");
     printf("分数在90分以上的学生人数为：%d人\n",ea);
     printf("分数在80分到89分之间的学生人数为：%d人\n",eb);  
     printf("分数在70分到79分之间的学生人数为：%d人\n",ec); 
     printf("分数在60分到69分之间的学生人数为：%d人\n",ed); 
     printf("分数在60分以下的学生人数为：%d人\n",ee);
     printf("平均分(保留两位小数)为%.2f\n\n",Ae);
     printf("计算机成绩信息：\n");
     printf("分数在90分以上的学生人数为：%d人\n",cpa);
     printf("分数在80分到89分之间的学生人数为：%d人\n",cpb);  
     printf("分数在70分到79分之间的学生人数为：%d人\n",cpc); 
     printf("分数在60分到69分之间的学生人数为：%d人\n",cpd); 
     printf("分数在60分以下的学生人数为：%d人\n",cpe);
     printf("平均分(保留两位小数)为%.2f\n\n",Acp);     
     printf("总分平均分(保留两位小数)为%.2f\n\n",Acp);
}

main()//主函数 
{
     
      Grade *T=NULL;    
      int ch;//开关变量，用于选择功能 
      int i;//循环时的计数器
      int n;//录入学生的总人数 
      int con=1;//判断是否还继续
      int srch;//查找方式的选择  
      int nosearch;//要查找的学号
      char nasearch[10];//要查找的姓名
      int low,high;//分数段 
      int del;//删除方式的选择 
      int nodel;//要删除的学号 
      char nadel[10];//要删除的姓名      
      while(con)
      {      
          ShowMainMenu();
          printf("请选择服务项目（输入编号）："); 
          scanf("%d",&ch);      
          switch(ch){//功能选择 
                case 1:      //////////完成录入//////////////
                     { 
                          printf("请输入要录入的学生人数:");       
                          scanf("%d",&n); 
                          for(i=0;i<n;i++)
                          {
                                printf("请输入第%d个学号：",i+1);
                                T=creatGrade(T);
                                printf("录入%d人成功，还剩余%d人待录入!\n\n",i+1,n-i-1);
                          } 
                          printf("成绩全部录入成功!\n");   
                          printf("你还要继续操作吗<1.继续;0.退出>:");
                          scanf("%d",&con);  
                          break;
                     }
               case 2:        //////////完成插入//////////////
                    {    
                         printf("请输入要插入的学生的学号：");  
                         T=creatGrade(T);    
                         printf("成绩插入成功!\n");                         
                         printf("你还要继续操作吗<1.继续;0.退出>:");
                         scanf("%d",&con);  
                         break; 
                     }  
              case 3:            //////////遍历学生信息//////////////
                   {          
                         printf("成绩排行榜（总分从高到低）\n"); 
                         printf("学号\t姓名\t语文\t数学\t英语\t计算机\t总分\n");
                         ShowAll(T);
                         printf("你还要继续操作吗<1.继续;0.退出>:");
                         scanf("%d",&con);      
                         break;
                   }                                      
              case 4:           //////////查找学生成绩//////////////
                   {
                         printf("请选择查找方式<1.按学号;2.按姓名;3.分数段查询>:\n"); 
                         scanf("%d",&srch); 
                         if(srch==1)
                         {
                              printf("请输入待查找学生的学号：");
                              scanf("%d",&nosearch);
                              NoSearch(T,nosearch);
                         }
                         else if(srch==2)
                         { 
                              printf("请输入待查找学生的姓名：");
                              scanf("%s",nasearch);
                              NaSearch(T,nasearch);
                         }
                         else if(srch==3)
                         {
                               printf("请输入待查找分数段区间：\n");
                               printf ("低分:\t");
                               scanf("%d",&low);
                               printf("高分:");
                               scanf("%d",&high);
                               printf("该分数段的学生有:\n");
                               printf("学号:\t\t姓名\t\t分数\n"); 
                               ScoreSearch(T,low,high);
                         } 
                         else printf("输入有误！"); 
                         printf("你还要继续操作吗<1.继续;——退出>:");
                         scanf("%d",&con);
                         break;
                   }    
              case 5://////////删除学生信息//////////////
                   {
                         printf("请选择删除方式<1.按学号;2.按姓名>:\n"); 
                         scanf("%d",&del);
                         if(del==1)
                         {
                               printf("请输入待删除的学生的学号：");
                               scanf("%d",&nodel);
                               T=NoDelete(T,nodel);
                               printf("删除完毕！\n");
                               printf("删除该生后的成绩排行榜（总分从高到低）\n");
                               printf("学号\t姓名\t语文\t数学\t英语\t计算机\t总分\n");      
                               ShowAll(T);                               
                         }
                         else if(del==2)
                         {
                               printf("请输入待删除的学生的姓名：");
                               scanf("%s",nadel);
                               T=NaDelete(T,nadel);
                               printf("删除完毕！\n");
                               printf("删除该生后的成绩排行榜（总分从高到低）\n");
                               printf("学号\t姓名\t语文\t数学\t英语\t计算机\t总分\n");      
                               ShowAll(T);       
                         }
                         printf("你还要继续操作吗<1.继续;0.退出>:");
                         scanf("%d",&con);
                         break;
                   }     
              case 6://////////学生分数统计//////////////
                   {
                         Statistics(T);
                         printf("你还要继续操作吗<1.继续;0.退出>:");
                         scanf("%d",&con);
                         break;
                   } 
      
             default:
                     {
                         printf("\n\n输入有误，请重新输入：\n\n\n");
                         con=1;
                         break;
                     } 
             }
      }      
      printf("先序遍历（程序功能测试）：\n"); 
      PreShowAll(T);      
      system("pause"); 
}

