#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Student//ѧ�����ͣ�����ʵ�֣� 
{
        int Sno;//ѧ��  
        char Sname[10];//���� 
        int Chinese;
        int Math;
        int English;
        int Computer;
        struct Student *next;
}Student;

typedef struct Grade//�������ͣ�����ƽ������ 
{
        int score;//����
        struct Student* head;//ѧ�� 
        int ltag,ldata,rdata,LH,RH;//ltagΪ��־,ldata,rdata,LH,RH�ֱ�Ϊ�����ݣ������ݣ�����Ⱥ������ֵ
	    struct Grade *lchild,*rchild;
}Grade;

void ShowMainMenu()//��ʾ�˵����� 
{
     printf("             ------------------------------------------------------\n\n"); 
     printf("             -------------* ��ӭ����ѧ���ɼ���ѯϵͳ *-------------\n");
     printf("\n");
     printf("                              *  1.¼��ѧ���ɼ�\n"); 
     printf("                              *  2.����ѧ���ɼ�\n");
     printf("                              *  3.���ѧ���ɼ�\n");
     printf("                              *  4.����ѧ����Ϣ\n");
     printf("                              *  5.ɾ��ѧ����Ϣ\n");
     printf("                              *  6.ͳ��ѧ����Ϣ\n\n");
     printf("             ------------------------------------------------------\n\n\n");  
     printf("    ��ע�⣺¼�빦�ܿ�������¼��ѧ���ɼ������빦��ֻ��¼��һ��ѧ���ĳɼ���������ܿ����������ѧ����Ϣ����ʵ�ֳɼ��ӵ͵������У����ҹ��ܿ��Բ���һ��ѧ���ĳɼ��������������ε�ѧ����Ϣ��ɾ������Ϊɾ��ĳһѧ���ĳɼ���ͳ�ƹ���Ϊͳ��ѧ������������ʾ�������ε�ѧ��������ƽ���֡�\n\n"); 
}

int depth(Grade *p)//����Ⱥ���
{
	int H=1;//��� 
	while(p!=NULL)
	{
		if(p->ldata>p->rdata)//��ߵ����ݴ����ұߵ����������
		{
			H++;
			p=p->lchild;
		}
		else if(p->ldata<=p->rdata)//��ߵ�����С�ڻ�����ұߵ������ұ���
		{
			H++;
			p=p->rchild;
		}
	}
	return  H;
}

Grade* judge(Grade *T)//�ж��Ƿ�Ϊƽ�������
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
				r->ltag=2;//ltagΪ2��־Ϊ������ƽ��
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
	T ->ltag=3;//ltagΪ3��־Ϊ����ƽ��
	return T;
}

Grade* adjust(Grade *T,Grade *p)//����Ϊƽ�������
{
	Grade *q,*r,*s,*t;
	int m;
	//Ѱ��p��ǰ�����
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
	p->LH=depth(p->lchild);//�������������
	p->RH=depth(p->rchild);//�������������
	m=p->LH-p->RH;
	if(m==2)
	{
		q->LH=depth(q->lchild);
		q->RH=depth(q->rchild);
		m=q->LH-q->RH;
		if(m==1)//LL�͵���
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
		else//LR�͵���
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
		if(m==1)//RL�͵���
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
		else//RR�͵���
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

Grade* creatGrade(Grade *T)//����������
{
    int No(Grade *T,int no);//����˵�����ظ�ѧ�Ž�����ʾ 
    int tag;//�Ƿ�Ϊ�ظ�ѧ�ŵı�־ 
    int k;
	Grade *p,*q,*r;	
    Student *s;	
	r=(Grade*)malloc(sizeof(Grade));
	s=(Student*)malloc(sizeof(Student));
	char f;//�ų�����Ҫ�Ļس����ַ��Ա��������Ӱ�� 	
    scanf("%d",&s->Sno);
    tag=No(T,s->Sno);
    if(tag==1)
    {
        printf("��ѧ���Ѵ��ڣ����֤�����룡\n");
        printf("��֤�������룺"); 
        scanf("%d",&s->Sno); 
    }
    printf("���������������");
    f=getchar(); 
    scanf("%s",s->Sname); 
    f=getchar(); 
    printf("��������������ĳɼ�(0~100)��");
	scanf("%d",&s->Chinese);
	while(s->Chinese>100|s->Chinese<0)//������0���»���100���� 
    {
       printf("�÷���Ϊ��Ч���������������룡\n�����ķ���Ϊ��");
       scanf("%d",&s->Chinese);
    } 
    printf("�������������ѧ�ɼ�(0~100)��");
	scanf("%d",&s->Math);
	while(s->Math>100||s->Math<0)//������0���»���100���� 
    {
       printf("�÷���Ϊ��Ч���������������룡\n�����ķ���Ϊ��");
       scanf("%d",&s->Math);
    } 
    printf("�����������Ӣ��ɼ�(0~100)��");
	scanf("%d",&s->English);
	while(s->English>100||s->English<0)//������0���»���100���� 
    {
       printf("�÷���Ϊ��Ч���������������룡\n�����ķ���Ϊ��");
       scanf("%d",&s->English);
    } 
    printf("����������ļ�����ɼ�(0~100)��");
	scanf("%d",&s->Computer); 
    while(s->Computer>100||s->Computer<0)//������0���»���100���� 
    {
       printf("�÷���Ϊ��Ч���������������룡\n�����ķ���Ϊ��");
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
	if(T==NULL)//Ϊ��ʱ��ӱ�ȻΪƽ����������Ҫ�ж�ƽ����� 
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
	     	p->rdata++;//�����ݼ�1
			p=p->rchild;
		}
		else if(p->score>k)
		{
		    p->ldata++;//�����ݼ�1
			p=p->lchild;
		}
		else if(p->score==k)//�������ϲ��룬��Ӱ�������ƽ�⣬Ҳ����Ҫ�ж�ƽ�� 
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
    p=judge(T);//�ж��Ƿ�Ϊƽ�������
	if(p->ltag==2)//�˶�������ƽ��ʱ
	T=adjust(T,p);//����Ϊƽ�������
	return T;
}

void ShowAll(Grade *T)//�����������������������ʵ�ֳɼ��Ĵӵ͵�������� 
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

void PreShowAll(Grade *T)//�����������������ֻ���ڲ���ƽ�⣬��ɼ�����ϵͳ�޹� 
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

int No(Grade *T,int no)//��������������÷ǵݹ�,�����ظ�ѧ�� 
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

void NoSearch(Grade *T,int nosearch)//����ѧ�Ų���ĳ��ѧ�� 
{
    Student *p; 
    if(T)
    {
         p=T->head;
         while(p&&p->Sno!=nosearch)p=p->next;
         if(p)        
              printf("%sͬѧ�ɼ���\n���ĳɼ�Ϊ��%d\n��ѧ�ɼ�Ϊ��%d\nӢ��ɼ�Ϊ��%d\n������ɼ�Ϊ��%d\n�ܷ�Ϊ��%d\n\n",p->Sname,p->Chinese,p->Math,p->English,p->Computer,T->score);
         NoSearch(T->lchild,nosearch);
         NoSearch(T->rchild,nosearch);
    }    
}

void NaSearch(Grade *T,char nasearch[10])//������������ĳ��ѧ�� 
{
    Student *p; 
    if(T)
    {
         p=T->head;         
         while(p&&strcmp(p->Sname,nasearch)!=0)p=p->next;
         if(p)
              printf("%sͬѧ�ɼ���\n���ĳɼ�Ϊ��%d\n��ѧ�ɼ�Ϊ��%d\nӢ��ɼ�Ϊ��%d\n������ɼ�Ϊ��%d\n�ܷ�Ϊ��%d\n\n",p->Sname,p->Chinese,p->Math,p->English,p->Computer,T->score);
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

Grade* dele(Grade *T,Grade *p,Grade *r)//ɾ��ĳ�����ڵ� 
{
	Grade *q,*child;
	if(p->lchild&&p->rchild)//������������Ϊ��
	{
		q=r=p;
		p=p->rchild;
		q->score=p->score;
		q->head=p->head;
	}
	if(p->lchild)//��������Ϊ��
		child=p->lchild;
	else//������Ϊ��
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

Grade* Delnode(Grade *T,int e)//ɾ���ɼ�
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
		printf("û�и����ĳɼ�");
	else
		T=dele(T,p,r);
		return T; 
}

Grade* NaDelete(Grade *T,char nadel[10])//ɾ��ĳ��ѧ��(���������� 
{
     Grade *stack[100];
     int top=0;
     Grade *p,*ppre;//*pper��¼p��˫��,*m������˫֧����ɾ��ʱ��p�����ӣ����ճ�Ϊp��ǰ��
     p=T;
     Student *q,*qpre;//*qper��¼q��ǰ��      
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
                     if(q)// �ҵ�Ҫɾ����ѧ����ѧ��
                     {
                           //����ͷ������Ӳ�֪һ��ѧ����ɾ�� 
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
                           else  //headΪ�գ��÷���û�д��ڵ����壬����Ҫɾ�����ڵ� 
                           {
                                T=Delnode(T,p->score);                                                                         
                           }       
                      }                                                          
                     p=p->rchild;                     
            }
     }
     return T;
}

Grade* NoDelete(Grade *T,int nodel)//ɾ��ĳ��ѧ��������ѧ�ţ� 
{
     Grade *stack[100];
     int top=0;
     Grade *p,*ppre,*parent;//*pper��¼p��˫��,*m������˫֧����ɾ��ʱ��p�����ӣ����ճ�Ϊp��ǰ��,parentΪ���ĸ��ڵ㣬����ɾ�����Ŀ��� 
     p=T;
     Student *q,*qpre;//*qper��¼q��ǰ��      
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
                     if(q)// �ҵ�Ҫɾ����ѧ����ѧ��
                     {
                           //����ͷ����ɾ�� 
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
                           else  //headΪ�գ��÷���û�д��ڵ����壬����Ҫɾ�����ڵ� 
                           {                              
                              T=Delnode(T,p->score);                                           
                           }       
                      }                                                          
                     p=p->rchild;                      
            }
     }
     p=judge(T);//�ж��Ƿ�Ϊƽ�������
	 if(p->ltag==2)//�˶�������ƽ��ʱ
     T=adjust(T,p);//����Ϊƽ�������
     return T;
}

void Statistics(Grade *T)//ͳ�Ƹ��������ε�ѧ������
{
     int ca=0,ma=0,ea=0,cpa=0;     
     int cb=0,mb=0,eb=0,cpb=0;
     int cc=0,mc=0,ec=0,cpc=0;
     int cd=0,md=0,ed=0,cpd=0;
     int ce=0,me=0,ee=0,cpe=0;
     int n=0;//������
     int sum=0;//�ܷ�
     int Sc=0,Sm=0,Se=0,Scp=0;//�����ܷ� 
     float ave;//ƽ���� 
     float Ac,Am,Ae,Acp;//����ƽ���� 
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
     printf("����ͳ�ƣ�\n");
     printf("��ѧ����Ϊ%d��\n\n",n);
     printf("���ĳɼ���Ϣ��\n"); 
     printf("������90�����ϵ�ѧ������Ϊ��%d��\n",ca);
     printf("������80�ֵ�89��֮���ѧ������Ϊ��%d��\n",cb);  
     printf("������70�ֵ�79��֮���ѧ������Ϊ��%d��\n",cc); 
     printf("������60�ֵ�69��֮���ѧ������Ϊ��%d��\n",cd); 
     printf("������60�����µ�ѧ������Ϊ��%d��\n",ce);
     printf("ƽ����(������λС��)Ϊ%.2f\n\n",Ac);
     printf("��ѧ�ɼ���Ϣ��\n");      
     printf("������90�����ϵ�ѧ������Ϊ��%d��\n",ma);
     printf("������80�ֵ�89��֮���ѧ������Ϊ��%d��\n",mb);  
     printf("������70�ֵ�79��֮���ѧ������Ϊ��%d��\n",mc); 
     printf("������60�ֵ�69��֮���ѧ������Ϊ��%d��\n",md); 
     printf("������60�����µ�ѧ������Ϊ��%d��\n",me);
     printf("ƽ����(������λС��)Ϊ%.2f\n\n",Am);
     printf("Ӣ��ɼ���Ϣ��\n");
     printf("������90�����ϵ�ѧ������Ϊ��%d��\n",ea);
     printf("������80�ֵ�89��֮���ѧ������Ϊ��%d��\n",eb);  
     printf("������70�ֵ�79��֮���ѧ������Ϊ��%d��\n",ec); 
     printf("������60�ֵ�69��֮���ѧ������Ϊ��%d��\n",ed); 
     printf("������60�����µ�ѧ������Ϊ��%d��\n",ee);
     printf("ƽ����(������λС��)Ϊ%.2f\n\n",Ae);
     printf("������ɼ���Ϣ��\n");
     printf("������90�����ϵ�ѧ������Ϊ��%d��\n",cpa);
     printf("������80�ֵ�89��֮���ѧ������Ϊ��%d��\n",cpb);  
     printf("������70�ֵ�79��֮���ѧ������Ϊ��%d��\n",cpc); 
     printf("������60�ֵ�69��֮���ѧ������Ϊ��%d��\n",cpd); 
     printf("������60�����µ�ѧ������Ϊ��%d��\n",cpe);
     printf("ƽ����(������λС��)Ϊ%.2f\n\n",Acp);     
     printf("�ܷ�ƽ����(������λС��)Ϊ%.2f\n\n",Acp);
}

main()//������ 
{
     
      Grade *T=NULL;    
      int ch;//���ر���������ѡ���� 
      int i;//ѭ��ʱ�ļ�����
      int n;//¼��ѧ���������� 
      int con=1;//�ж��Ƿ񻹼���
      int srch;//���ҷ�ʽ��ѡ��  
      int nosearch;//Ҫ���ҵ�ѧ��
      char nasearch[10];//Ҫ���ҵ�����
      int low,high;//������ 
      int del;//ɾ����ʽ��ѡ�� 
      int nodel;//Ҫɾ����ѧ�� 
      char nadel[10];//Ҫɾ��������      
      while(con)
      {      
          ShowMainMenu();
          printf("��ѡ�������Ŀ�������ţ���"); 
          scanf("%d",&ch);      
          switch(ch){//����ѡ�� 
                case 1:      //////////���¼��//////////////
                     { 
                          printf("������Ҫ¼���ѧ������:");       
                          scanf("%d",&n); 
                          for(i=0;i<n;i++)
                          {
                                printf("�������%d��ѧ�ţ�",i+1);
                                T=creatGrade(T);
                                printf("¼��%d�˳ɹ�����ʣ��%d�˴�¼��!\n\n",i+1,n-i-1);
                          } 
                          printf("�ɼ�ȫ��¼��ɹ�!\n");   
                          printf("�㻹Ҫ����������<1.����;0.�˳�>:");
                          scanf("%d",&con);  
                          break;
                     }
               case 2:        //////////��ɲ���//////////////
                    {    
                         printf("������Ҫ�����ѧ����ѧ�ţ�");  
                         T=creatGrade(T);    
                         printf("�ɼ�����ɹ�!\n");                         
                         printf("�㻹Ҫ����������<1.����;0.�˳�>:");
                         scanf("%d",&con);  
                         break; 
                     }  
              case 3:            //////////����ѧ����Ϣ//////////////
                   {          
                         printf("�ɼ����а��ִܷӸߵ��ͣ�\n"); 
                         printf("ѧ��\t����\t����\t��ѧ\tӢ��\t�����\t�ܷ�\n");
                         ShowAll(T);
                         printf("�㻹Ҫ����������<1.����;0.�˳�>:");
                         scanf("%d",&con);      
                         break;
                   }                                      
              case 4:           //////////����ѧ���ɼ�//////////////
                   {
                         printf("��ѡ����ҷ�ʽ<1.��ѧ��;2.������;3.�����β�ѯ>:\n"); 
                         scanf("%d",&srch); 
                         if(srch==1)
                         {
                              printf("�����������ѧ����ѧ�ţ�");
                              scanf("%d",&nosearch);
                              NoSearch(T,nosearch);
                         }
                         else if(srch==2)
                         { 
                              printf("�����������ѧ����������");
                              scanf("%s",nasearch);
                              NaSearch(T,nasearch);
                         }
                         else if(srch==3)
                         {
                               printf("����������ҷ��������䣺\n");
                               printf ("�ͷ�:\t");
                               scanf("%d",&low);
                               printf("�߷�:");
                               scanf("%d",&high);
                               printf("�÷����ε�ѧ����:\n");
                               printf("ѧ��:\t\t����\t\t����\n"); 
                               ScoreSearch(T,low,high);
                         } 
                         else printf("��������"); 
                         printf("�㻹Ҫ����������<1.����;�����˳�>:");
                         scanf("%d",&con);
                         break;
                   }    
              case 5://////////ɾ��ѧ����Ϣ//////////////
                   {
                         printf("��ѡ��ɾ����ʽ<1.��ѧ��;2.������>:\n"); 
                         scanf("%d",&del);
                         if(del==1)
                         {
                               printf("�������ɾ����ѧ����ѧ�ţ�");
                               scanf("%d",&nodel);
                               T=NoDelete(T,nodel);
                               printf("ɾ����ϣ�\n");
                               printf("ɾ��������ĳɼ����а��ִܷӸߵ��ͣ�\n");
                               printf("ѧ��\t����\t����\t��ѧ\tӢ��\t�����\t�ܷ�\n");      
                               ShowAll(T);                               
                         }
                         else if(del==2)
                         {
                               printf("�������ɾ����ѧ����������");
                               scanf("%s",nadel);
                               T=NaDelete(T,nadel);
                               printf("ɾ����ϣ�\n");
                               printf("ɾ��������ĳɼ����а��ִܷӸߵ��ͣ�\n");
                               printf("ѧ��\t����\t����\t��ѧ\tӢ��\t�����\t�ܷ�\n");      
                               ShowAll(T);       
                         }
                         printf("�㻹Ҫ����������<1.����;0.�˳�>:");
                         scanf("%d",&con);
                         break;
                   }     
              case 6://////////ѧ������ͳ��//////////////
                   {
                         Statistics(T);
                         printf("�㻹Ҫ����������<1.����;0.�˳�>:");
                         scanf("%d",&con);
                         break;
                   } 
      
             default:
                     {
                         printf("\n\n�����������������룺\n\n\n");
                         con=1;
                         break;
                     } 
             }
      }      
      printf("��������������ܲ��ԣ���\n"); 
      PreShowAll(T);      
      system("pause"); 
}

