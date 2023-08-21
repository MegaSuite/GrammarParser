#pragma once

#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<stack>
#include<queue>
using namespace std;

#define OK 1
#define ERROR 0
#define INFEASIBLE (-1)
typedef int status; //��������ֵ����


/*���νṹ������˵����*/
typedef struct Child		//���ӽ��
{
	int child;
	Child* next;
}*CNode;

typedef struct CTNode
{
	char* data;
	int indent;		//�ý��ĺ���Ҫ���ӵ�������
	CNode FirstChild;	//��������ͷ���
}CTNode;

typedef struct CTree
{
	CTNode nodes[1000];
	int n, r;				//������͸���λ��
}CTree;


status InitTree(CTree& T);
status InsertChild(CTree& T, int p, int i, CTree c);
status GetParent(CTree T, int child, int& parent);
status TraverseTree(CTree T, status(*visit)(char*, int));



/*ջ�ṹ������˵��*/
typedef CTree* SElemType;	//����Ԫ������
typedef struct
{
	SElemType* base;			//��ջ����֮ǰ������֮��base��ֵΪNULL
	SElemType* top;			    //ջ��ָ��
	int StackSize;				//��ǰ�ѷ���Ĵ洢�ռ䣬��Ԫ��Ϊ��λ
}SqStack;


status InitStack(SqStack& S);
status GetTop(SqStack S, SElemType& e);
status Push(SqStack& S, SElemType e);
status Pop(SqStack& S, SElemType& e);

