#include"process_ahead.h"
#include"tokens_define.h"

DefineStruct DefineDef[10];//用于储存define宏定义的内容，全局
IncludeStruct IncludeDef[10];//用于储存include文件包含的内容，全局
int MacroNum;//宏定义个数


/*预编译函数,本次实验的主题函数之二，
 * 对文件开头的宏定义和自定义头文件进行预编译，
 * 判断是否有错误
 * 并把除宏定义之外的语句写入C_TEMP.txt,
 * 供Program使用*/
status Process(FILE* fp)
{
	int w; //接收GetToken得到的元素
	int i=0,j=0,m;//i是宏定义个数，j是include个数
	int pre_line_num=1;//用于记录换行情况
	char container;//暂时存储字符判断结尾处的分号
	int a, b;//比较行数
	int flag=0;//判断语句中是否出现define的定义
	FILE* mid_fp;
	char filename[50];

	strcpy(filename, "C_TEMP.txt"); //中间文件
	mid_fp = fopen(filename, "w");
	w = GetToken(fp);

	do {
		if (w == POUND)//检测到#号，进入程序
        {
			w = GetToken(fp);//获取#号后的单词，【#define】or【#include】
			if (w == DEFINE)
            {
				w = GetToken(fp);
				a = line_num;

				if (w == ERROR_TOKEN)//检测到错误标识
                {
                    printf("ERROR: line %d:错误标识!\n", line_num);
                    return ERROR;
                }
                else if(w == SEMI)//检测到分号
                {
                    printf("ERROR: line %d:错误定义，检测到';'！\n", line_num);
                    return ERROR;
                }
                else if (w == POUND)//检测到尾部#
                {
                    printf("ERROR: line %d:定义错误,检测到尾部'#'!\n", line_num);
                    return ERROR;
                }
				else
					strcpy(DefineDef[i].ident, token_text);

				w = GetToken(fp);//获取宏定义的内容
				b = line_num;

                if (w == ERROR_TOKEN)//检测到错误标识
                {
                    printf("ERROR: line %d:错误标识!\n", line_num);
                    return ERROR;
                }
                else if(w == SEMI)//检测到分号
                {
                    printf("ERROR: line %d:错误定义，检测到';'！\n", line_num);
                    return ERROR;
                }
                else if (w == POUND)//检测到尾部#
                {
                    printf("ERROR: line %d:定义错误,检测到尾部'#'!\n", line_num);
                    return ERROR;
                }
                else
                	strcpy(DefineDef[i++].string, token_text);

				if (a != b)//检测到宏定义未完成
                {
                    printf("ERROR: line %d:检测到宏定义未完成!\n", line_num-1);
                    return ERROR;
                }

                MacroNum = i;//宏定义个数
				fprintf(mid_fp, "\n");
				w = GetToken(fp);//获取下一个单词
				pre_line_num = line_num;
				continue;
			}
			else if (w == INCLUDE)
            {
				w = GetToken(fp);
				if (w == ERROR_TOKEN)
                {
                    printf("ERROR: line %d:请使用'<>'或'\"\"'包裹!\n", line_num);
                    return ERROR;
                }
				else if(w== STRING_CONST)//检测自定义头文件  #include "xxx.h"
                {
					strcpy(IncludeDef[j++].string, token_text);
					if ((container = fgetc(fp)) != ';')//检测到句尾不是';'
                    {
                        ungetc(container, fp);//将读取到的字符放回缓冲区
                        fprintf(mid_fp, "\n");
                        w = GetToken(fp);
                        pre_line_num = line_num;
                        continue;
                    }
					else
                    {
                        printf("ERROR: line %d:自定义头文件定义错误,检测到句尾';'!\n", line_num);
                        return ERROR;
                    }
				}
				else if (w == LESS)
                {
					w = GetToken(fp);
					a = line_num;
					if (w != IDENT)
                    {
                        printf("ERROR: line %d:头文件错误!\n", line_num);
                        return ERROR;
                    }
					else
                    {
						w = GetToken(fp);
						b = line_num;
						if (w != MORE)
                        {
                            printf("ERROR: line %d:头文件'>'丢失!\n", line_num-1);
                            return ERROR;
                        }
						if (a != b)
                        {
                            printf("ERROR: line %d:宏定义不完整!\n", line_num);
                            return ERROR;
                        }
						if ((container = fgetc(fp)) != ';')
                        {
                            ungetc(container, fp);
                            fprintf(mid_fp, "\n");
                            w = GetToken(fp);
                            pre_line_num = line_num;
                            continue;
                        }
						else
                        {
                            printf("ERROR: line %d:宏定义错误,检测到错误符号!\n", line_num);
                            return ERROR;
                        }
					}
				}
			}
			else
            {
                printf("ERROR: line %d:检测不到正确的宏定义:[#define] or [#include]!\n", line_num);
                return ERROR;
            }
		}

		MacroNum = i;//宏定义个数

		if (w != POUND)
        {

			if (w == IDENT)
            {
				for (m = 0; m < MacroNum; m++)//检测读取到的关键词是否为宏定义
                {
					if (!strcmp(token_text, DefineDef[m].ident))//是宏定义
                    {
						if (pre_line_num != line_num)//发生换行
                        {
							fprintf(mid_fp, "\n%s ", DefineDef[m].string);
							flag = 1;
						}
						else
                        {
                            fprintf(mid_fp, "%s ", DefineDef[m].string);
                            flag = 1;
                        }
					}
				}
				if (flag != 0)//如果是宏定义，flag重新置为0
					flag = 0;

				else
                {
					if (pre_line_num != line_num)
						fprintf(mid_fp, "\n%s ", token_text);

					else
                        fprintf(mid_fp, "%s ", token_text);
				}
			}
			else if (w == LINENOTE)
            {
				pre_line_num = line_num;
				w = GetToken(fp);
				continue;
			}
			else if (w == BLOCKNOTE)
            {
				for(m=0;m<line_num-pre_line_num;m++)
                    fprintf(mid_fp, "\n");
				pre_line_num = line_num;
				w = GetToken(fp);
				continue;
			}
			else if (w == ERROR_TOKEN)
            {
				if (pre_line_num != line_num)
					fprintf(mid_fp, "\n%s", token_text);

				else
                    fprintf(mid_fp, "%s", token_text);
			}
			else
            {
				if (pre_line_num != line_num)
					fprintf(mid_fp, "\n%s ", token_text);

				else
                    fprintf(mid_fp, "%s ", token_text);
			}
		}

		pre_line_num = line_num;//重置换行标志

		w = GetToken(fp);
	} while (w != EOF);

	fclose(mid_fp);
	return OK;
}