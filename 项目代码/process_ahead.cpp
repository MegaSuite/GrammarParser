#include"process_ahead.h"
#include"tokens_define.h"

DefineStruct DefineDef[10];//���ڴ���define�궨������ݣ�ȫ��
IncludeStruct IncludeDef[10];//���ڴ���include�ļ����������ݣ�ȫ��
int MacroNum;//�궨�����


/*Ԥ���뺯��,����ʵ������⺯��֮����
 * ���ļ���ͷ�ĺ궨����Զ���ͷ�ļ�����Ԥ���룬
 * �ж��Ƿ��д���
 * ���ѳ��궨��֮������д��C_TEMP.txt,
 * ��Programʹ��*/
status Process(FILE* fp)
{
	int w; //����GetToken�õ���Ԫ��
	int i=0,j=0,m;//i�Ǻ궨�������j��include����
	int pre_line_num=1;//���ڼ�¼�������
	char container;//��ʱ�洢�ַ��жϽ�β���ķֺ�
	int a, b;//�Ƚ�����
	int flag=0;//�ж�������Ƿ����define�Ķ���
	FILE* mid_fp;
	char filename[50];

	strcpy(filename, "C_TEMP.txt"); //�м��ļ�
	mid_fp = fopen(filename, "w");
	w = GetToken(fp);

	do {
		if (w == POUND)//��⵽#�ţ��������
        {
			w = GetToken(fp);//��ȡ#�ź�ĵ��ʣ���#define��or��#include��
			if (w == DEFINE)
            {
				w = GetToken(fp);
				a = line_num;

				if (w == ERROR_TOKEN)//��⵽�����ʶ
                {
                    printf("ERROR: line %d:�����ʶ!\n", line_num);
                    return ERROR;
                }
                else if(w == SEMI)//��⵽�ֺ�
                {
                    printf("ERROR: line %d:�����壬��⵽';'��\n", line_num);
                    return ERROR;
                }
                else if (w == POUND)//��⵽β��#
                {
                    printf("ERROR: line %d:�������,��⵽β��'#'!\n", line_num);
                    return ERROR;
                }
				else
					strcpy(DefineDef[i].ident, token_text);

				w = GetToken(fp);//��ȡ�궨�������
				b = line_num;

                if (w == ERROR_TOKEN)//��⵽�����ʶ
                {
                    printf("ERROR: line %d:�����ʶ!\n", line_num);
                    return ERROR;
                }
                else if(w == SEMI)//��⵽�ֺ�
                {
                    printf("ERROR: line %d:�����壬��⵽';'��\n", line_num);
                    return ERROR;
                }
                else if (w == POUND)//��⵽β��#
                {
                    printf("ERROR: line %d:�������,��⵽β��'#'!\n", line_num);
                    return ERROR;
                }
                else
                	strcpy(DefineDef[i++].string, token_text);

				if (a != b)//��⵽�궨��δ���
                {
                    printf("ERROR: line %d:��⵽�궨��δ���!\n", line_num-1);
                    return ERROR;
                }

                MacroNum = i;//�궨�����
				fprintf(mid_fp, "\n");
				w = GetToken(fp);//��ȡ��һ������
				pre_line_num = line_num;
				continue;
			}
			else if (w == INCLUDE)
            {
				w = GetToken(fp);
				if (w == ERROR_TOKEN)
                {
                    printf("ERROR: line %d:��ʹ��'<>'��'\"\"'����!\n", line_num);
                    return ERROR;
                }
				else if(w== STRING_CONST)//����Զ���ͷ�ļ�  #include "xxx.h"
                {
					strcpy(IncludeDef[j++].string, token_text);
					if ((container = fgetc(fp)) != ';')//��⵽��β����';'
                    {
                        ungetc(container, fp);//����ȡ�����ַ��Żػ�����
                        fprintf(mid_fp, "\n");
                        w = GetToken(fp);
                        pre_line_num = line_num;
                        continue;
                    }
					else
                    {
                        printf("ERROR: line %d:�Զ���ͷ�ļ��������,��⵽��β';'!\n", line_num);
                        return ERROR;
                    }
				}
				else if (w == LESS)
                {
					w = GetToken(fp);
					a = line_num;
					if (w != IDENT)
                    {
                        printf("ERROR: line %d:ͷ�ļ�����!\n", line_num);
                        return ERROR;
                    }
					else
                    {
						w = GetToken(fp);
						b = line_num;
						if (w != MORE)
                        {
                            printf("ERROR: line %d:ͷ�ļ�'>'��ʧ!\n", line_num-1);
                            return ERROR;
                        }
						if (a != b)
                        {
                            printf("ERROR: line %d:�궨�岻����!\n", line_num);
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
                            printf("ERROR: line %d:�궨�����,��⵽�������!\n", line_num);
                            return ERROR;
                        }
					}
				}
			}
			else
            {
                printf("ERROR: line %d:��ⲻ����ȷ�ĺ궨��:[#define] or [#include]!\n", line_num);
                return ERROR;
            }
		}

		MacroNum = i;//�궨�����

		if (w != POUND)
        {

			if (w == IDENT)
            {
				for (m = 0; m < MacroNum; m++)//����ȡ���Ĺؼ����Ƿ�Ϊ�궨��
                {
					if (!strcmp(token_text, DefineDef[m].ident))//�Ǻ궨��
                    {
						if (pre_line_num != line_num)//��������
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
				if (flag != 0)//����Ǻ궨�壬flag������Ϊ0
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

		pre_line_num = line_num;//���û��б�־

		w = GetToken(fp);
	} while (w != EOF);

	fclose(mid_fp);
	return OK;
}