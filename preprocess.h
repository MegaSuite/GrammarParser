#pragma once //Ԥ����
#include<cstdio>
#include<cstdlib>
#include<cstring>

typedef int status;

#define OK 1
#define ERROR 0

//���ڴ���define�궨������
typedef struct define_data {
	char ident[50];
	char string[50];
}define_data;

//���ڴ���includeͷ�ļ���������
typedef struct include_data {
	char string[50];
}include_data;

extern define_data data_Def[10];//���ڴ���define�궨�������
extern include_data data_Include[10];//���ڴ���include�ļ�����������
extern int data_Def_num;
status pre_process(FILE* fp);