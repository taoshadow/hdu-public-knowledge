#include <iostream>
#include <cstdlib>
#include<io.h> 
#include <fstream.h>
#define MAX_VERTEX_NUM 30 // ��󶥵����
struct VertexType
{
	char vex;
	int parent;
};
struct ArcCellType
{
	int adj;// Ȩֵ
	int vi,vj;//�˵�
};
struct MGraph
{
	 VertexType vexs[MAX_VERTEX_NUM]; // ��������
	 ArcCellType arcs[MAX_VERTEX_NUM*(MAX_VERTEX_NUM-1)/2+1];//�洢�ߵ�����
     int vexnum,arcnum; // ͼ�ĵ�ǰ�������ͻ���
};
struct MFSet
{
	VertexType nodes[MAX_VERTEX_NUM];
	int r,n;//����λ�úͽ����
};
void InitMfset(MFSet &S,MGraph G)
{//��ʼ���ȼ���
	int i;
	S.n=G.vexnum;
	for(i=0;i<S.n;i++)
	S.nodes[i].parent=-1;
}
int LocateVex(MGraph G,char u)
{//��G�д��ڶ���u,�򷵻ظö�����ͼ��λ��;���򷵻�-1
   int i;
   for(i=0;i<G.vexnum;++i)
     if(u==G.vexs[i].vex)
       return i;
   return -1;
}
void CreateAN(MGraph &G)
{//����������G
	int i,j,k,w;
	char va,vb;  
	FILE *graphlist;
	graphlist=fopen("mincstree.txt","r");
	fscanf(graphlist,"%d",&G.vexnum);
    fscanf(graphlist,"%d",&G.arcnum);
	for(i=0;i<G.vexnum;++i)//���춥������
		fscanf(graphlist,"%s",&G.vexs[i].vex);
    for(k=1;k<=G.arcnum;++k)
	{
		fscanf(graphlist,"%s %s %d",&va,&vb,&w);	
		i=LocateVex(G,va);
		j=LocateVex(G,vb);
		G.arcs[k].adj=w;
		G.arcs[k].vi=i;
		G.arcs[k].vj=j;
	}
}
int find_mfset(MFSet &S,int i)
{//����i�������ڼ��ϲ�����
	int j,k,t;
	if(i<0||i>S.n-1) return -1;//������S����һ�Ӽ�
	for(j=i;S.nodes[j].parent>=0;j=S.nodes[j].parent);
	for(k=i;k!=j;k=t)
	{
		t=S.nodes[k].parent;
		S.nodes[k].parent=j;
	}
	return j;
}
int is_mfset(MFSet &S,int vi,int vj)
{//�ж�i j�Ƿ�����һ�����ϣ��Ƿ���1�����򷵻�0
	if(find_mfset(S,vi)==find_mfset(S,vj))
		return 1;
	else return 0;
}
int min_mfset(MFSet &S,int i,int j)
{//�Ͳ�i j���ڵ���������
	if(i<0||i>S.n-1||j<0||j>S.n-1) return 0;
	if(S.nodes[i].parent>S.nodes[j].parent)
	{
		S.nodes[j].parent+=S.nodes[i].parent;
		S.nodes[i].parent=j;
	}
	else
	{
		S.nodes[i].parent+=S.nodes[j].parent;
		S.nodes[j].parent=i;
	}
	return 1;
}
int Partition(ArcCellType arcs[],int low,int high)
{//����L��elem[low..high]�ļ�¼�������¼��λ��������������λ�ã���ʱ����֮ǰ�ļ�¼����������
	int pivotkey;
	arcs[0].adj=arcs[low].adj;//���ӱ�ĵ�һ����¼�������¼
    arcs[0].vi=arcs[low].vi;
    arcs[0].vj=arcs[low].vj;
    pivotkey=arcs[low].adj;//��Ȩֵ���ؼ���
    while(low<high)
	{
		while(low<high&&arcs[high].adj>=pivotkey)
			--high;
		arcs[low].adj=arcs[high].adj;//���������¼С�ļ�¼�Ƶ��Ͷ�
		arcs[low].vi=arcs[high].vi;
		arcs[low].vj=arcs[high].vj;
		while(low<high&&arcs[low].adj<=pivotkey)
			++low;
		arcs[high].adj=arcs[low].adj;//���������¼��ļ�¼�Ƶ��߶�
		arcs[high].vi=arcs[low].vi;
		arcs[high].vj=arcs[low].vj;
	}
	arcs[low].adj=arcs[0].adj;
	arcs[low].vi=arcs[0].vi;
	arcs[low].vj=arcs[0].vj;
	return low; // ��������λ��
}
void QSort(ArcCellType arcs[],int low,int high)
{//��L�е�L.elem[low..high]����������
	int pivotloc;
    if(low<high)
	{//���ȴ���1
		pivotloc=Partition(arcs,low,high);
		QSort(arcs,low,pivotloc-1);
		QSort(arcs,pivotloc+1,high);
	}
}
void minspantree(MGraph &G,MFSet &S)
{//��³˹�㷨����С������
	int ecnum,i,v,w;
	FILE *output;
	output=fopen("mincstreeOutput.txt","w"); //�ļ�������ʹ��С�������ĸ������Լ���Ӧ��Ȩֵ���ı���ʽ���
	QSort(G.arcs,1,G.arcnum);
	i=1;
	ecnum=G.vexnum; //��ͨ��������
	while(ecnum>1)
	{
		v=find_mfset(S,G.arcs[i].vi);
		w=find_mfset(S,G.arcs[i].vj);
		if(!is_mfset(S,G.arcs[i].vi,G.arcs[i].vj)) 
		{//�����˵㲻��һ���ȼ���
			min_mfset(S,v,w); //�ϲ���ͨ����
		    printf("%c%c %d\n",G.vexs[G.arcs[i].vi].vex,G.vexs[G.arcs[i].vj].vex,G.arcs[i].adj);
			fprintf(output,"%c%c %d\n",G.vexs[G.arcs[i].vi].vex,G.vexs[G.arcs[i].vj].vex,G.arcs[i].adj);
		    ecnum--;
		}
		i++;
	}
}
void main()
{
	MGraph G;
	MFSet S;
	CreateAN(G);
	InitMfset(S,G);
	minspantree(G,S);
}