#pragma once //Ԥ����

#include<cstdio>
#include<cstdlib>
#include<cstring>

typedef int status;


#define OK 1
#define ERROR 0


//����define�궨������
typedef struct DefineStruct {
	char ident[50];
	char string[50];
}DefineStruct;


//����includeͷ�ļ���������
typedef struct IncludeStruct {
	char string[50];
}IncludeStruct;


extern DefineStruct DefineDef[10];//���ڴ���define�궨�������
extern IncludeStruct IncludeDef[10];//���ڴ���include�ļ�����������
extern int MacroNum;
status Process(FILE* fp);