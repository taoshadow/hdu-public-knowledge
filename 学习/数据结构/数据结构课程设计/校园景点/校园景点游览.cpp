#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

#define MAX 1023717496

typedef struct ArcCell{
	int adj;//�����ľ��� 
}ArcCell,AdjMatrix[100][100];

typedef struct {
	char scename[30];//�羰���� 
	int scenum;//�羰���� 
	char sceintro[200];//�羰��� 
}Scenery;

typedef struct {
	Scenery vexs[100];
	AdjMatrix arcs;
	int vexnum,arcnum;
}MGraph;//ͼ�������ʾ�� 

int Path[100];//��¼���·�� 
int D[100];//��¼�ڵ㵽��ʼ�ڵ�ľ��� 
bool final[100];//��Ǹýڵ��Ƿ���·���� 
                                           
int GetSce(char scename[],MGraph G){//�ɷ羰���õ��羰�������е��±� 
	int i;
	for(i=1;i<=G.vexnum;i++)
		if(strcmp(scename,G.vexs[i].scename)==0)return i;
	return -1;
}

void CreatMGraph(MGraph &G){
	int i,j;
	int dis,n1,n2;
	char name1[30],name2[30];
	printf("�����뾰�����: ");
	scanf("%d",&G.vexnum);
	printf("�������ͼ��·������: ");
	scanf("%d",&G.arcnum);
	printf("\n������ÿ���������Ϣ���羰���ƣ��羰���ţ��羰���). \n");
	for(i=1;i<=G.vexnum;i++){
		printf("�� %d �����㣨�羰���ƣ��羰���ţ��羰���: ",i);
		scanf("%s",G.vexs[i].scename);
		scanf("%d",&G.vexs[i].scenum);
		scanf("%s",G.vexs[i].sceintro);
	}
	printf("\n�����뾰��֮���·��·�ĳ���: \n");
	for(i=1;i<=G.vexnum;i++){
		for(j=1;j<=G.vexnum;j++){
			G.arcs[i][j].adj = MAX;
		}
	}
	
	for(i=1;i<=G.arcnum;i++){
		printf("��������ʼĳ��·����ʼ����ֹ��������ƣ�������·�ĳ���: ");
		scanf("%s",name1);
		scanf("%s",name2);
		n1 = GetSce(name1,G);
		n2 = GetSce(name2,G);
		scanf("%d",&dis);
		G.arcs[n1][n2].adj = dis;
		G.arcs[n2][n1].adj = dis;
	}
	printf("\n");
}


void OutPutPath(MGraph G,bool find,int sn,int en){
	int i;
	int path[100];
	if(!find){
		printf("�����ҵ��Ӿ��� %s ������ %s ��·.\n\n",G.vexs[sn].scename,G.vexs[en].scename);
		return;
	}
	else {
        
		printf("\n���� %s ������ %s �����·���ĳ���Ϊ: %d\n\n",G.vexs[sn].scename,G.vexs[en].scename,D[en]);
		printf("���� %s ������ %s ���·���еķ羰����Ϊ: \n",G.vexs[sn].scename,G.vexs[en].scename);
	    //for(i=1;i<=G.vexnum;i++)cout<<Path[i]<<' ';cout<<endl;
		path[0] = en;
		int k = 1,x = Path[en];
		while(x != sn){
			path[k++] = x;
			x = Path[x];
		}
        path[k] = sn;
		for(i=k;i>=0;i--){
            printf("�����·���ϵ� %d ������Ϊ(���ƣ����ţ����)��%s %d %s \n",k-i+1,G.vexs[path[i]].scename,G.vexs[path[i]].scenum,G.vexs[path[i]].sceintro);
		}
		printf("\n");
	}
}


void ShortestPath_DIJ(MGraph G,int sn,int en){
	int i;
	int v,min;
	for(i=1;i<=G.vexnum;i++){
		final[i] = false;//���ڼ�¼�Ƿ�����ȷ���ĵ�ļ����� 
		D[i] = G.arcs[sn][i].adj;//ÿ���������ľ��� 
		if(D[i]!= MAX)Path[i] = sn;//��ʼ��Path[] ���������������Ϊ��� ������Ϊ0 
		else Path[i] = 0;
	}
	D[sn] = 0;
	final[sn] = true;
	Path[sn] = sn;
	bool find = false;
	while(1){
		min = MAX;
		v = -1;
		for(i=1;i<=G.vexnum;i++){//�ҵ���ǰλ�����������ĵ� 
			if(final[i]==false&&D[i]<min){
				v = i;
				min = D[i];
			}
		}
		if(v==-1){
			find = false;
			break;
		}
	//	cout<<"v: "<<v<<" MIN: "<<min<<endl;
		final[v] = true;
		for(i=1;i<=G.vexnum;i++){//�޸�ÿ���㵽����������� �����޸��� ��˵��ͨ��v���޸ĵ����������� ��ʱ��¼Path[i] = v; 
			if(final[i]==false&&(min+G.arcs[v][i].adj<D[i])){
				D[i] = min+G.arcs[v][i].adj;
				Path[i] = v;
			}
		} 
	//	for(i=1;i<=G.vexnum;i++)cout<<D[i]<<' ';cout<<endl;
		if(v==en){
			find = true;
			break;
		}
	}
	OutPutPath(G,find,sn,en);
}




int main(){
    while(1){
    	MGraph G;
    	char name1[30],name2[30],name[30],num;
    	int sn,en,cho;
    	CreatMGraph(G);
    	while(1){
			printf("Ҫ��ѯ���㣬������ 1��Ҫ��ѯ���������ľ��룬������ 2.\n");
			scanf("%d",&cho);
			if(cho==2){
        		printf("��������ʼ��������:");
				scanf("%s",name1);
				printf("��������ֹ��������:");
        		scanf("%s",name2);
        		sn = GetSce(name1,G);
        		en = GetSce(name2,G);
        		if(sn==en)
					 printf("��ʼ���㼴Ϊ��ֹ����.\n\n");
				else 
        			 ShortestPath_DIJ(G,sn,en);
			}
			else{
				printf("������Ҫ���ҵľ��������: ");
				scanf("%s",name);
				num = GetSce(name, G);
				
				printf("����%s�ķ羰����Ϊ%d:\n",name,G.vexs[num].scenum);
				cout<<"����"<<name<<"�ķ羰���Ϊ"<<G.vexs[num].sceintro<<endl;
			}
        	printf("ֹͣ��ѯ�������� 1 .�������� 0 .\n\n");
        	int q;
			scanf("%d",&q);
			if(q)break;
         }
     }
	return 0;
}

/*
6 
8
v1 1 11
v2 2 22
v3 3 33
v4 4 44
v5 5 55
v6 6 66
v1 v3 10
v1 v5 30
v1 v6 100
v2 v3 5
v3 v4 50
v4 v6 10
v4 v5 20
v5 v6 60
*/






	



	                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   
