#include"tokens_define.h"
#include"main_parser.h"
#include"structure_define.h"
#include"process_ahead.h"
#include"file_writer.h"

char filename[100];
int ch = 1;

int main()
{
	CTree T;
	FILE* fp,*mid_fp;

	extern define_data data_Def[10];//用于储存define宏定义的内容
	extern int data_Def_num;
	extern int line_num;
	extern char token_text[100];

	int error_line[100];//记录错误行数
	int error_line_num=0;//记录错误总个数

ChooseFile://选择文件标志
    printf("请输入文件名：\n→" );
    scanf("%s", filename);
	if (!(fp = fopen(filename, "r")))
	{
		printf("...选择文件错误，请重新选择...\n");
		goto ChooseFile;
	}
	else
        fclose(fp);

	while (ch)
	{
		printf("---基于高级语言源程序格式处理工具菜单---\n");
        printf("\t1. 词法分析\n\t2. 语法分析\n\t3. 缩进编排\n\t4. 选择文件\n\t0. 退出程序\n");
        printf("---请选择：\n→");
		scanf("%d", &ch);

		switch (ch)
		{
            case 1:
                error_line_num = 1;
                line_num = 1;  //行数初始化为1
                if (!(fp = fopen(filename, "r")))
                {
                    printf("...选择文件错误，请重新选择...\n");
                    break;
                }
                printf("....正在预编译文件....\n");
                if (pre_process(fp))
                    printf("预编译成功！按任意键继续...\n");

                else
                {
                    printf("预编译失败！退出系统！请检查错误！\n");
                    return 0;
                }

                mid_fp = fopen("C_mid_file.txt", "r");
                line_num = 1;  //行数初始化为1
                printf("\n");
                printf("\t单词类别\t\t\t\t单词值\n");
                printf("\t---------------------------------------------\n");

                while (!feof(mid_fp))
                {
                    w = GetToken(mid_fp);
                    if (w >= AUTO && w <= DEFINE)
                    {
                        printf("	关键字					%s\n", token_text);
                    }
                    switch (w)
                    {
                        case POUND:
                            printf("	井号					%s\n", token_text);
                            break;
                        case IDENT:
                            printf("	标识符					%s\n", token_text);
                            break;
                        case INT_CONST:
                            printf("	整型常量				%s\n", token_text);
                            break;
                        case UNSIGNED_CONST:
                            printf("	无符号整型常量			         %s\n", token_text);
                            break;
                        case LONG_CONST:
                            printf("	长整型常量				%s\n", token_text);
                            break;
                        case UNSIGNED_LONG_CONST:
                            printf("	无符号长整型常量		         %s\n", token_text);
                            break;
                        case DOUBLE_CONST:
                            printf("	双精度浮点型常量	    	        %s\n", token_text);
                            break;
                        case FLOAT_CONST:
                            printf("	浮点型常量				%s\n", token_text);
                            break;
                        case LONG_DOUBLE_CONST:
                            printf("	长双精度浮点型常量		         %s\n", token_text);
                            break;
                        case CHAR_CONST:
                            printf("	字符型常量				%s\n", token_text);
                            break;
                        case STRING_CONST:
                            printf("	字符串常量				%s\n", token_text);
                            break;
                        case EQUAL_TO:
                            printf("	赋值运算符				=\n");
                            break;
                        case PLUS:
                            printf("	加法运算符				+\n");
                            break;
                        case MINUS:
                            printf("	减法运算符				-\n");
                            break;
                        case MULTIPLY:
                            printf("	乘法运算符				*\n");
                            break;
                        case DIVIDE:
                            printf("	除法运算符				/\n");
                            break;
                        case MOD:
                            printf("	取模运算符				%%\n");
                            break;
                        case MORE:
                            printf("	关系运算符				>\n");
                            break;
                        case LESS:
                            printf("	关系运算符				<\n");
                            break;
                        case EQUAL:
                            printf("	关系运算符				==\n");
                            break;
                        case UNEQUAL:
                            printf("	关系运算符				!=\n");
                            break;
                        case MORE_EQUAL:
                            printf("	关系运算符				>=\n");
                            break;
                        case LESS_EQUAL:
                            printf("	关系运算符				<=\n");
                            break;
                        case AND:
                            printf("	逻辑与					&&\n");
                            break;
                        case OR:
                            printf("	逻辑或					||\n");
                            break;
                        case LS:
                            printf("	左小括号				(\n");
                            break;
                        case RS:
                            printf("	右小括号				)\n");
                            break;
                        case LM:
                            printf("	左中括号				[\n");
                            break;
                        case RM:
                            printf("	右中括号				]\n");
                            break;
                        case LL:
                            printf("	左大括号				{\n");
                            break;
                        case RL:
                            printf("	右大括号				}\n");
                            break;
                        case SEMI:
                            printf("	分号					;\n");
                            break;
                        case COMMA:
                            printf("	逗号					,\n");
                            break;
                        case ERROR_TOKEN:
                        {
                            error_line[error_line_num] = line_num;
                            error_line_num++;
                            break;
                        }
                        default:
                            break;
                    }
                }

                printf("\n");
                printf("\t     --------错误列表--------\n");
                printf("\t\t  错误总数:  %d\n", error_line_num - 1);
                if (error_line_num > 1)
                {
                    printf("\n");
                    printf("\t\t  序号	  行数\n");
                    for (int i = 0; i < error_line_num - 1; i++)
                        printf("\t\t     %d       %d\n", i+1, error_line[i+1]);//从1开始，避免0号位0的输出

                }
                fclose(fp);
                fclose(mid_fp);
                printf("\n按任意键继续...\n");
                getchar();
                getchar();
                break;


            case 2:
                printf(".....正在预编译文件.....\n");
                line_num = 1;  //行数初始化为1
                fp = fopen(filename, "r");
                if (pre_process(fp))
                    printf("预编译成功！\n");

                else
                {
                    printf("预编译失败！退出系统！请检查错误！\n");
                    return 0;
                }
                mid_fp = fopen("C_mid_file.txt", "r");
                line_num = 1;  //行数初始化为1
                if (!Program(mid_fp, T))
                {
                    printf("发生生成错误！错误行号：%d\n", line_num);
                    printf("按任意键继续...\n");
                    break;
                }
                TraverseTree(T, PrintTree);
                printf("\n按任意键继续...\n");
                fclose(fp);
                fclose(mid_fp);
                getchar();
                getchar();
                break;


            case 3:
                line_num = 1;  //行数初始化为1
                fp = fopen(filename, "r");

                if (!pre_process(fp))   //预编译
                {
                    printf("预编译失败！退出系统！请检查错误！\n");
                    return 0;
                }

                line_num = 1;
                mid_fp = fopen("C_mid_file.txt", "r");

                if (!Program(mid_fp, T))
                {
                    printf("程序存在语法错误！无法缩进打印！\n");
                    break;
                }
                else
                    printf("程序语法正确！\n");

                fclose(fp);
                fp = fopen(filename, "r");
                PrintFile(fp);
                printf("缩进编排文件生成成功，请进入[cmake-build-debug]文件夹查看！\n");
                printf("按任意键继续...\n");

                getchar();
                getchar();
                fclose(fp);
                fclose(mid_fp);
                break;

            case 4:
                goto ChooseFile;

            default:
                return 0;
		}
	}
	return 1;

}