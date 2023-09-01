#pragma once

#include<queue>
#include<stack>
#include"tokens_define.h"
#include"structure_define.h"
using namespace std;


#define OK 1
#define ERROR 0
//#define INFEASIBLE -1

struct print
{
	int indent;						//��¼����ֵ
	int line_num;					//��¼�������к�
};

typedef int status;
extern int indent0;					//��¼Դ���������ֵ
extern queue<print> printList;		//�洢������ӡ��ʽ��Ԫ
extern int w;						//���GetToken�����ķ���ֵ������ĵ����������
extern char kind[100];			    //��ȡ���͹ؼ���
extern char tokenText0[100];		//��ȡ������������

status Program(FILE* fp, CTree& T); //�﷨��λ<����>���ӳ���
status ExternalDefList(FILE* fp, CTree& T);//�﷨��λ<�ⲿ��������>���ӳ���
status ExternalDef(FILE* fp, CTree& T);//�﷨��λ<�ⲿ����>���ӳ���
status ExternalVariableDef(FILE* fp, CTree& T);//�﷨��λ<�ⲿ��������>�ӳ���
status VariableList(FILE* fp, CTree& T);//�﷨��λ<��������>�ӳ���
status Function(FILE* fp, CTree& T);//�﷨��λ<��������>�ӳ���
status ParameterList(FILE* fp, CTree& T);//�﷨��λ<�β�����>�ӳ���
status FormParameterDef(FILE* fp, CTree& T);//�﷨��λ<�βζ���>�ӳ���
status ComplexStat(FILE* fp, CTree& T);//�﷨��λ<�������>�ӳ���
status LocalVariableList(FILE* fp, CTree& T);//�﷨��λ<�ֲ�������������>�ӳ���
status LocalVariableDef(FILE* fp, CTree& T);//�﷨��λ<�ֲ���������>�ӳ���
status StatementList(FILE* fp, CTree& T);//�﷨��λ<�������>�ӳ���
status Statement(FILE* fp, CTree& T);//�﷨��λ<���>�ӳ���
status Expression(FILE* fp, CTree& T, int endsym);//�﷨��λ<���ʽ>�ӳ���
char Precedence(char* a, char* b);//�Ƚ�a��b�����ȼ�
status PrintTree(char* data, int indent); //��ӡ����
