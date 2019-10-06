#include<iostream>
#include<malloc.h>
#include<math.h>
#define STACK_INIT_SIZE 10 // �洢�ռ��ʼ������
#define STACKINCREMENT 2 // �洢�ռ��������
#define MAXLENGTH 8 // ������Ϊ8x8����
typedef int BoardType[MAXLENGTH][MAXLENGTH]; // ��������[��][��]
BoardType b; // ��������
int HTry1[8]={-2,-1,1,2,2,1,-1,-2};
int HTry2[8]={1,2,2,1,-1,-2,-2,-1};
int select[8][8][8]={-1};
typedef struct
{
	int i;
	int j;
	int dir;
}PosType;//��������λ������
typedef struct 
{
   PosType *base;
   PosType *top; 
   int stacksize; 
}SqStack; // ˳��ջ

int InitStack(SqStack &S)
 { // ����һ����ջS
   if(!(S.base=(PosType*)malloc(STACK_INIT_SIZE*sizeof(PosType))))
     exit(OVERFLOW); // �洢����ʧ��
   S.top=S.base;
   S.stacksize=STACK_INIT_SIZE;//????????????
   return 1;
 }
int StackEmpty(SqStack S)
 { // ��ջSΪ��ջ���򷵻�1�����򷵻�0
   if(S.top==S.base)
     return 1;
   else
     return 0;
}
int Push(SqStack &S,PosType e)
 { // ����Ԫ��eΪ�µ�ջ��Ԫ��
   if(S.top-S.base>=S.stacksize) // ջ����׷�Ӵ洢�ռ�
   {
     S.base=(PosType*)realloc(S.base,(S.stacksize+STACKINCREMENT)*sizeof(PosType));
     if(!S.base)
       exit(OVERFLOW); // �洢����ʧ��
     S.top=S.base+S.stacksize;
     S.stacksize+=STACKINCREMENT;
   }
   *(S.top)++=e;
   return 1;
 }

int Pop(SqStack &S,PosType &e)
 { // ��ջ���գ���ɾ��S��ջ��Ԫ�أ���e������ֵ��������1�����򷵻�0
   if(S.top==S.base)
     return 0;
   e=*--S.top;
   return 1;
 }

int Pass(PosType p)
{
	if(p.i>=0&&p.i<=7&&p.j>=0&&p.j<=7&&b[p.i][p.j]==0)//p(i,j)Ҫ��b[8][8]���鷶Χ�ڣ����Ҹ�λ�ò��ڵ�ǰ·����
	return 1;
	else return 0;
}
int PassCount(PosType p)//���ߵ�λ�õĸ���
{
	int count=0,k;
	for(k=0;k<8;k++)
	{
		p.i+=HTry1[k];
		p.j+=HTry2[k];
		if(Pass(p))
			count++;
		p.i-=HTry1[k];
		p.j-=HTry2[k];
	}
		return count;
}
/*void BestSelect(PosType p)
{//����һ��λ��	
	int count=0,t,k,h,row[8];//����������С����
	count=PassCount(p);
	for(k=0;k<count;k++)
	{
		for(h=0;h<8;h++)
		{
		 p.i+=HTry1[h];
		 p.j+=HTry2[h];
		 if(Pass(p))
		 {	
			t=PassCount(p);
			select[p.i][p.j][k]=h;//��¼����λ���еĵ��jλ��
			row[k]=t;
		 }
		 p.i-=HTry1[h];
		 p.j-=HTry2[h];
		}
	}
	for(k=0;k<count;k++)
		for(h=k+1;h<count;h++)
			if(row[k]>row[h])
			{
				t=select[p.i][p.j][k];
				select[p.i][p.j][k]=select[p.i][p.j][h];
				select[p.i][p.j][h]=t;
				t=row[k];
				row[k]=row[h];
				row[h]=t;
			}
//	h=select[p.i][p.j][nextp];
//	p.i+=HTry1[h];
//    p.j+=HTry2[h];
	//return p;
}
/*PosType NextPos(PosType c,int nextp)
{//����һ��λ�ã�
	int h;
	h=select[c.i][c.j][nextp];
	c.i+=HTry1[h];
    c.j+=HTry2[h];
	return c;
}*/
PosType NextPos(PosType pos)
{
	int Max=8;
	int k,temx,temy,temdir;
	PosType p;
	p.i=pos.i;
	p.j=pos.j;
	int count=0;
	for(k=0;k<8;k++)
	{
		p.i+=HTry1[k];
		p.j+=HTry2[k];
		if(Pass(p))//�ҿ����ߵ�λ�����ٵ���һ������Ϊ���ŵ���һ������
		{	
			count=PassCount(p);
			if(count<Max)
			{
				Max=count;
				temx=p.i;
				temy=p.j;
			   	temdir=k;
			}
		}
		p.i-=HTry1[k];
		p.j-=HTry2[k];
		p.dir=temdir;
	}
	p.i=temx;
	p.j=temy;
	return p;
}

void ChessBoardPath(BoardType b,PosType start)
{//����߱����̵�·�����ҵ�·������1�����򷵻�0
	SqStack S;
	PosType curpos,e,e1;//��ǰλ��
	int m,n,num=0;
    for(m=0;m<8;m++)
		for(n=0;n<8;n++)
			b[m][n]=0;//Broad�����ʼ��0
	InitStack(S);
	curpos=start;
	do
	{
		if(Pass(curpos))//��ǰλ�ÿ���
		{
			e1.i=curpos.i;
			e1.j=curpos.j;
			e1.dir=0;
			num++;
			b[e1.i][e1.j]=num;	
			Push(S,e1);
			if(num==64) break;//����ȫ�̣�����
			else 
			{
				//BestSelect(curpos);//���㵱ǰ����select[][][]������
				curpos=NextPos(curpos);//̽����һ��������һ��λ�ÿ��ܵ�λ�ø������ٵķ��򣩲�ʹ����Ϊ��ǰλ��
			}
		}
		
     else
     { // ��ǰλ�ò�����
       if(!StackEmpty(S))
       {
		   int n;
           Pop(S,e); // ��ջ��ǰһλ��
		   n=PassCount(e)-1;
         while(e.dir==n&&!StackEmpty(S)) // ǰһλ�ô������һ������
         {
			 b[e.i][e.j]=0;
             Pop(S,e); // �˻�һ��
         }
		 n=PassCount(e)-1;
         if(e.dir<n) // û�����һ������
         {
           e.dir++; // ����һ������̽��
           Push(S,e);
	       curpos=NextPos(e); // �趨��ǰλ���Ǹ��·����ϵ����ڿ�
         }
       }
     }
   }while(!StackEmpty(S));
}

void main()
{
	PosType start;
	int i,j;
	printf("���������������ϵĳ�ʼλ��(i,j)��ֵ: ");
	scanf("%d%d",&start.i,&start.j);
	ChessBoardPath(b,start);	
	printf("����·��Ϊ:\n");
	for(i=0;i<8;i++)
		for(j=0;j<8;j++)
		{
			printf("%d ",b[i][j]);
			if(j==7)
				printf("\n");
		}
}