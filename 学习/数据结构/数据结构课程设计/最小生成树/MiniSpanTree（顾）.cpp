#include <iostream>
#include <cstdlib>
#include <fstream>
using namespace std;

typedef struct vertex //��������Ľṹ��
{
	int r;
	int p;
	char num;
}vertex;

typedef struct edge //�����ߵĽṹ��
{
	char a;
	char b;
	int flag;
	int dis;
}edge;

int cmp( const void *a ,const void *b)    //��������
{ 
	return (*(edge *)a). dis> (*(edge *)b).dis ? 1 : -1; 
} 

void initial(edge *e,vertex *v,int n,int m)  //��ʼ��
{
	int i;
	printf("��ֱ����붥�����: ");
	for(i=0;i<n;i++)
	{
		getchar();
		scanf("%c",&v[i].num);
		v[i].p=v[i].r=i;
	}
	printf("�����붥��A,����B�Լ�����֮��ľ���: \n");
	for(i=0;i<m;i++)
	{
		getchar();
		scanf("%c %c %d",&e[i].a,&e[i].b,&e[i].dis);
		e[i].flag=0;
	}
}

int find(vertex *v,vertex *u) //���Ҷ���u�ĸ��ڵ�
{
	if(u->r==u->p)
		return u->p;
	else
	{
		return find(v,&v[u->p]);
	}
}

void merge(vertex *v,int aa,int bb)   //�����Ϊaa��bb�Ķ��㲢��ͬһ����
{
	v[aa].p=bb;
}

int main(void) 
{
	int i,j,n,m;
	int aa,bb,sum;
	vertex *v;
	edge *e;
	printf("����������ͱ���:");
	scanf("%d %d",&n,&m);
	e=(edge *)malloc(m*sizeof(edge));
	v=(vertex *)malloc(n*sizeof(vertex));

	initial(e,v,n,m);  
    qsort(e,m,sizeof(e[0]),cmp);  
	sum=0;                   //������
	for(i=0;i<m;i++) 
	{
		for(j=0;j<n;j++)     //���ұ�ab����������ĸ��ڵ�,a�ĸ��ڵ�Ϊaa,b�ĸ��ڵ�Ϊbb
		{
			if(v[j].num==e[i].a)
				aa=find(v,&v[j]);
			if(v[j].num==e[i].b)
				bb=find(v,&v[j]);
		}
		if(aa!=bb)          //��aa������bb,��aa,bb�ϲ���ͬһ������
		{
			merge(v,aa,bb);
			e[i].flag=1;    //��Ǹ�����Ϊ�Ѷ�
			sum++;
			if(sum==n-1)
				break;
		}
	}
	printf("��С������Ϊ\n");
	for(i=0;i<m;i++)
	{
		if(e[i].flag==1)
		{
			printf("%c <--> %c:%d\n",e[i].a,e[i].b,e[i].dis);
		}
	}
	ofstream f;           //�ļ�������ʹ��С�������ĸ������Լ���Ӧ��Ȩֵ���ı���ʽ���
	f.open("MiniSpanTree.txt");
	for(i=0;i<m;i++)
	{
		if(e[i].flag==1)
		{
		    f<<e[i].a<<"<-->"<<e[i].b<<":"<<e[i].dis<<endl;
		}
	}
	f.close();
	return 0;
}
