#include<iostream> 
#include<cstdio>
#include<cstring> 
#include<alloc.h>
using namespace std;

typedef struct node {
	int posx,posy;
	int dir; // dirΪ��һ���ķ���  1:���� ��2�������� ��3�������ߣ�4������ 
	struct node *pre;//��Ϊջ���Ƚ��������topɾ���� ������Ҫ֪��topǰ����Ǹ��ڵ㣬���Խڵ��ָ������������ǰ����ַ���� 
}SNode;

typedef struct{
	SNode *base;
	SNode *top;
}LinkStack,*PLinkStack;

//int maze[101][101];
int hash[101][101]; //��¼�㼣 
int dir[4][2] = {0,1,1,0,0,-1,-1,0};
 
void InitMaze(int n,int m,int maze[100][100]){
	printf("���ʼ���Թ���\n");
	int i,j;
	for(i=0;i<n;i++){
		for(j=0;j<m;j++){
			scanf("%d",&maze[i][j]);
		}
	}
	printf("���λ�ã�%d %d\n",1,1);
	printf("����λ�ã�%d %d\n",n,m);
//	printf("\n\n");
	memset(hash,0,sizeof(hash));
}

void InitStack(PLinkStack &S){
	S->base = S->top = NULL;
}

bool Pass(int x,int y,int n,int m,int maze[100][100]){
	
	if(x<0||x>n||y<0||y>m)return false;
	//cout<<"Pass: "<<x+1<<' '<<y+1<<' '<<maze[x][y]<<endl; 
	if(maze[x][y]==1||hash[x][y]!=0)return false;
	return true;
}

void Push(PLinkStack &S,SNode &e){
	SNode *p = (SNode *)malloc(sizeof(SNode));
	*p = e;//���д�� 
	/*p->posx = e.posx;
	p->posy = e.posy;
	p->dir = e.dir;*/
	if(S->base==NULL&&S->top==NULL){//������Ϊ��ʱ,�ƽ���һ���ڵ� ��ʱ��S->base ,S->top��ָ��ýڵ� 
		p->pre = NULL;
		S->base = p;
		S->top = p;
	}
	else{
		p->pre = S->top;//��Ϊ��ʱ���½ڵ��preָ��top ,���޸ĵ�ǰ��topΪָ��p; 
		S->top = p;
	}
}

bool StackEmpty(PLinkStack &S){
	if(S->base==NULL && S->top == NULL)
		return true;
	return false;
}

void Pop(PLinkStack &S,SNode &e){
	/*e.posx = S->top->posx;
	e.posy = S->top->posy;
	e.dir = S->top->dir;
	e.pre = S->top->pre;*/
	e = *S->top;
	if(S->base == S->top){//��base == top ʱ˵��ջ��ֻ��һ���ڵ� ��ʱɾ���ڵ���base,top ��ֵΪNULL ��˵�����ǿ�ջ 
		free(S->top);
		S->base = S->top = NULL;
	}
	else {
		SNode *p = S->top;
		S->top = p->pre;
		free(p);
	}
}

bool MathPath(int sx,int sy,int ex,int ey,PLinkStack &S,int maze[100][100]){
	InitStack(S);
	int cntposx = sx,cntposy = sy;
	int cntstep = 1;
	do{
		if(Pass(cntposx,cntposy,ex,ey,maze)){ //�ýڵ������ ����ջ ���������ߵ���һ���ڵ� 
			hash[cntposx][cntposy] = 2;//�����㼣
			SNode e;
			e.posx = cntposx;
			e.posy = cntposy;
			e.dir = 1;
			Push(S,e);            
			if(cntposx == ex && cntposy == ey)return true;
			cntposx += dir[0][0];
			cntposy += dir[0][1];
			cntstep++;
	     	//cout<<"Push: "<<S->top->posx+1<<' '<<S->top->posy+1<<' '<<1<<' '<<S->top->ord<<endl;getchar();
		}
		else { //�ýڵ��߲�ͨ��ɾ������ǰ�ڵ�Ľڵ㣬�޸�ɾ���ڵ�ķ��򣬽��޸Ĺ��Ľڵ���ջ ��Ȼ���������ջ�Ľڵ�������һ���ڵ� 
			if(!StackEmpty(S)){
				SNode e;
				Pop(S,e);
		    	//if(!StackEmpty(S))cout<<"pop: "<<S->top->posx<<' '<<S->top->posy<<' '<<S->top->dir<<endl;
				while(e.dir == 4 && !StackEmpty(S)){ //���4���������߹� ��ɾ���ýڵ㣻 
					hash[e.posx][e.posy] = 3;//���������߹�������ͨ�����㼣 
					Pop(S,e);
				    //cout<<"pop77: "<<e.posx+1<<' '<<e.posy+1<<' '<<e.dir<<endl;//	getchar();
				}
				if(e.dir < 4){
					e.dir++;//�ı䷽�� 
					Push(S,e); 
                    //cout<<"Push77: "<<e.posx+1<<' '<<e.posy+1<<' '<<e.dir<<endl; 
					cntposx = e.posx+dir[e.dir-1][0];
	    			cntposy = e.posy+dir[e.dir-1][1];;
	    		    //cout<<"cntpos77: "<<cntposx+1<<' '<<cntposy+1<<' '<<e.dir<<' '<<cntstep<<endl;getchar();
				}
			}
		}
	}while(!StackEmpty(S));
	return false;
}
			
void PrintPath(bool succ,PLinkStack S){
	if(!succ){
		printf("���Թ��Ҳ���һ������ڵ����ڵ�·.\n\n\n");
	}
	else {
		SNode *e[1000],*p = S->top;
		int i = 0,k=0;
		while(p){
			e[i++] = p;
			p = p->pre;  
		}
		printf("���Թ�һ������ڵ����ڵ�·����������:\n"); 
		for(int j=i-1;j>=0;j--){
			printf("�� %03d �� (posx,posy,dir) �� ( %d,%d,%d )\n",++k,e[j]->posx+1,e[j]->posy+1,e[j]->dir);	
		}
	//	printf("\n\n");
	}
}

void PrintMaze(bool succ,PLinkStack &S,int n,int m,int maze[100][100]){
	int i,j;
	if(succ){
		printf("�Ҹ�����·���㼣����:\n");
		for(i=0;i<n;i++){
			for(j=0;j<m;j++){          
				if(maze[i][j]==1) printf("# ");
				else if(hash[i][j]==0) printf("  ");
				else if(hash[i][j]==2) printf("* ");
				else if(hash[i][j]==3) printf("@ ");
			}
			printf("\n");
		}
		printf("\n\n");
	}
}
		
int main(){
	int n,m;
	bool succ;
	PLinkStack S = (PLinkStack)malloc(sizeof(LinkStack));
	int maze[100][100];
	while(1){
		printf("�������Թ��ĳ��Ϳ�\n"); 
		scanf("%d %d",&n,&m);
		//printf("\n\n");
		InitMaze(n,m,maze);
	    succ = MathPath(0,0,n-1,m-1,S,maze);
	    PrintPath(succ,S);
	    PrintMaze(succ,S,n,m,maze);
	}
}

 /*
9 8
0 0 1 0 0 0 1 0
0 0 1 0 0 0 1 0
0 0 0 0 1 1 0 1
0 1 1 1 0 0 1 0 
0 0 0 1 0 0 0 0
0 1 0 0 0 1 0 1
0 1 1 1 1 0 0 1
1 1 0 0 0 1 0 1
1 1 0 0 0 0 0 0

3 2 
0 0
0 0
0 0

3 4
0 0 0 0 
0 0 1 1
0 0 0 0

4 9
0 0 0 0 0 0 1 0 0
0 1 0 0 0 1 0 0 0
0 0 1 1 1 0 0 1 1
0 0 1 1 1 0 1 0 0

 
 */
	
	
	 
