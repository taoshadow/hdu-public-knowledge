#include<iostream>
typedef struct
{
	TElemType data;
	BiTNode *lchild,*rchild;
}BiTNode,*BiTree;
int InitBiTree(BiTree &T)
{ // ����ն�����T
   T=NULL;
   return 1;
}
void CreateBiTree(BiTree &T)
{//���������ǰ׺���ʽ��������������ʾ�Ķ�����T��
	if(ch==Nil) // ��
		T=NULL;
	else
	{
		T=(BiTree)malloc(sizeof(BiTNode));
		 if(!T)
		   exit(OVERFLOW);
		 T->data=ch; // ���ɸ����
		 CreateBiTree(T->lchild); // ����������
		 CreateBiTree(T->rchild); // ����������
		   }
	 }


}