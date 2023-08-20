#pragma once

#include<cstdio>
#include<cstdlib>
#include<cstring>

enum TOKENS{AUTO,BREAK,CASE,CHAR,CONST,CONTINUE,DEFAULT,DO,
DOUBLE,ELSE,ENUM,EXTERN,FLOAT,FOR,GOTO,IF,
INT,LONG,REGISTER,RETURN,SHORT,SIGNED,SIZEOF,STATIC,
STRUCT,SWITCH,TYPEDEF,UNION,UNSIGNED,VOID,VOLATILE,WHILE, INCLUDE, DEFINE,      //Ϊ�ؼ���
IDENT, //��ʶ��
INT_CONST, UNSIGNED_CONST, LONG_CONST, UNSIGNED_LONG_CONST, DOUBLE_CONST, FLOAT_CONST,
LONG_DOUBLE_CONST, CHAR_CONST, STRING_CONST,  //����
PLUS,MINUS, MULTIPLY, DIVIDE, MOD,//˫Ŀ�����
MORE,LESS,EQUAL,UNEQUAL,MORE_EQUAL,LESS_EQUAL, //��ϵ�����
AND,OR,
EQUAL_TO,  //��ֵ�����
LL,RL,LM,RM,LS,RS, //���ţ�large,medium,small��
LINENOTE,BLOCKNOTE,SEMI,COMMA,ERROR_TOKEN,POUND  //��������,����SEMIΪ�ֺţ�COMMAΪ����,POUNDΪ����,ERROR_TOKEN��ʶ����

};

//����ؼ��ֵĽṹ��
typedef struct keyword {
	char key[10];
	int enum_key;
}keyword;

int GetToken(FILE* fp);

extern keyword n[IDENT]; //�������ؼ��ֵ�����
extern char token_text[100]; //�ݴ泣��
extern int line_num; //�����������


