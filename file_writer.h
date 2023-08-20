#pragma once

#include<cstdio>
#include<cstring>
#include"parser.h"

#define ERROR 0
#define OK 1

typedef int status;
status PrintFile(FILE* fp);