#pragma once //预处理

#include<cstdio>
#include<cstdlib>
#include<cstring>

typedef int status;


#define OK 1
#define ERROR 0


//储存define宏定义数据
typedef struct DefineStruct {
	char ident[50];
	char string[50];
}DefineStruct;


//储存include头文件定义数据
typedef struct IncludeStruct {
	char string[50];
}IncludeStruct;


extern DefineStruct DefineDef[10];//用于储存define宏定义的内容
extern IncludeStruct IncludeDef[10];//用于储存include文件包含的内容
extern int MacroNum;
status Process(FILE* fp);