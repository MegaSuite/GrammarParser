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

	extern define_data data_Def[10];//���ڴ���define�궨�������
	extern int data_Def_num;
	extern int line_num;
	extern char token_text[100];

	int error_line[100];//��¼��������
	int error_line_num=0;//��¼�����ܸ���

ChooseFile://ѡ���ļ���־
    printf("�������ļ�����\n��" );
    scanf("%s", filename);
	if (!(fp = fopen(filename, "r")))
	{
		printf("...ѡ���ļ�����������ѡ��...\n");
		goto ChooseFile;
	}
	else
        fclose(fp);

	while (ch)
	{
		printf("---���ڸ߼�����Դ�����ʽ�����߲˵�---\n");
        printf("\t1. �ʷ�����\n\t2. �﷨����\n\t3. ��������\n\t4. ѡ���ļ�\n\t0. �˳�����\n");
        printf("---��ѡ��\n��");
		scanf("%d", &ch);

		switch (ch)
		{
            case 1:
                error_line_num = 1;
                line_num = 1;  //������ʼ��Ϊ1
                if (!(fp = fopen(filename, "r")))
                {
                    printf("...ѡ���ļ�����������ѡ��...\n");
                    break;
                }
                printf("....����Ԥ�����ļ�....\n");
                if (pre_process(fp))
                    printf("Ԥ����ɹ��������������...\n");

                else
                {
                    printf("Ԥ����ʧ�ܣ��˳�ϵͳ���������\n");
                    return 0;
                }

                mid_fp = fopen("C_mid_file.txt", "r");
                line_num = 1;  //������ʼ��Ϊ1
                printf("\n");
                printf("\t�������\t\t\t\t����ֵ\n");
                printf("\t---------------------------------------------\n");

                while (!feof(mid_fp))
                {
                    w = GetToken(mid_fp);
                    if (w >= AUTO && w <= DEFINE)
                    {
                        printf("	�ؼ���					%s\n", token_text);
                    }
                    switch (w)
                    {
                        case POUND:
                            printf("	����					%s\n", token_text);
                            break;
                        case IDENT:
                            printf("	��ʶ��					%s\n", token_text);
                            break;
                        case INT_CONST:
                            printf("	���ͳ���				%s\n", token_text);
                            break;
                        case UNSIGNED_CONST:
                            printf("	�޷������ͳ���			         %s\n", token_text);
                            break;
                        case LONG_CONST:
                            printf("	�����ͳ���				%s\n", token_text);
                            break;
                        case UNSIGNED_LONG_CONST:
                            printf("	�޷��ų����ͳ���		         %s\n", token_text);
                            break;
                        case DOUBLE_CONST:
                            printf("	˫���ȸ����ͳ���	    	        %s\n", token_text);
                            break;
                        case FLOAT_CONST:
                            printf("	�����ͳ���				%s\n", token_text);
                            break;
                        case LONG_DOUBLE_CONST:
                            printf("	��˫���ȸ����ͳ���		         %s\n", token_text);
                            break;
                        case CHAR_CONST:
                            printf("	�ַ��ͳ���				%s\n", token_text);
                            break;
                        case STRING_CONST:
                            printf("	�ַ�������				%s\n", token_text);
                            break;
                        case EQUAL_TO:
                            printf("	��ֵ�����				=\n");
                            break;
                        case PLUS:
                            printf("	�ӷ������				+\n");
                            break;
                        case MINUS:
                            printf("	���������				-\n");
                            break;
                        case MULTIPLY:
                            printf("	�˷������				*\n");
                            break;
                        case DIVIDE:
                            printf("	���������				/\n");
                            break;
                        case MOD:
                            printf("	ȡģ�����				%%\n");
                            break;
                        case MORE:
                            printf("	��ϵ�����				>\n");
                            break;
                        case LESS:
                            printf("	��ϵ�����				<\n");
                            break;
                        case EQUAL:
                            printf("	��ϵ�����				==\n");
                            break;
                        case UNEQUAL:
                            printf("	��ϵ�����				!=\n");
                            break;
                        case MORE_EQUAL:
                            printf("	��ϵ�����				>=\n");
                            break;
                        case LESS_EQUAL:
                            printf("	��ϵ�����				<=\n");
                            break;
                        case AND:
                            printf("	�߼���					&&\n");
                            break;
                        case OR:
                            printf("	�߼���					||\n");
                            break;
                        case LS:
                            printf("	��С����				(\n");
                            break;
                        case RS:
                            printf("	��С����				)\n");
                            break;
                        case LM:
                            printf("	��������				[\n");
                            break;
                        case RM:
                            printf("	��������				]\n");
                            break;
                        case LL:
                            printf("	�������				{\n");
                            break;
                        case RL:
                            printf("	�Ҵ�����				}\n");
                            break;
                        case SEMI:
                            printf("	�ֺ�					;\n");
                            break;
                        case COMMA:
                            printf("	����					,\n");
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
                printf("\t     --------�����б�--------\n");
                printf("\t\t  ��������:  %d\n", error_line_num - 1);
                if (error_line_num > 1)
                {
                    printf("\n");
                    printf("\t\t  ���	  ����\n");
                    for (int i = 0; i < error_line_num - 1; i++)
                        printf("\t\t     %d       %d\n", i+1, error_line[i+1]);//��1��ʼ������0��λ0�����

                }
                fclose(fp);
                fclose(mid_fp);
                printf("\n�����������...\n");
                getchar();
                getchar();
                break;


            case 2:
                printf(".....����Ԥ�����ļ�.....\n");
                line_num = 1;  //������ʼ��Ϊ1
                fp = fopen(filename, "r");
                if (pre_process(fp))
                    printf("Ԥ����ɹ���\n");

                else
                {
                    printf("Ԥ����ʧ�ܣ��˳�ϵͳ���������\n");
                    return 0;
                }
                mid_fp = fopen("C_mid_file.txt", "r");
                line_num = 1;  //������ʼ��Ϊ1
                if (!Program(mid_fp, T))
                {
                    printf("�������ɴ��󣡴����кţ�%d\n", line_num);
                    printf("�����������...\n");
                    break;
                }
                TraverseTree(T, PrintTree);
                printf("\n�����������...\n");
                fclose(fp);
                fclose(mid_fp);
                getchar();
                getchar();
                break;


            case 3:
                line_num = 1;  //������ʼ��Ϊ1
                fp = fopen(filename, "r");

                if (!pre_process(fp))   //Ԥ����
                {
                    printf("Ԥ����ʧ�ܣ��˳�ϵͳ���������\n");
                    return 0;
                }

                line_num = 1;
                mid_fp = fopen("C_mid_file.txt", "r");

                if (!Program(mid_fp, T))
                {
                    printf("��������﷨�����޷�������ӡ��\n");
                    break;
                }
                else
                    printf("�����﷨��ȷ��\n");

                fclose(fp);
                fp = fopen(filename, "r");
                PrintFile(fp);
                printf("���������ļ����ɳɹ��������[cmake-build-debug]�ļ��в鿴��\n");
                printf("�����������...\n");

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