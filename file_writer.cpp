#include"file_writer.h"

status PrintFile(FILE* fp) 
{
	int IndentNum=0, line = 1;//IndentNumΪ����������lineΪ����
	int i;//ѭ������
    char c;//���ڶ�ȡ�ļ�

	FILE* print_fp;

	char filename[30] = "C_OUT.txt";//����ļ���
	print_fp = fopen(filename, "w");

	while (!printList.empty())
	{
		IndentNum = printList.front().indent;//��������
		printList.pop();
		while (!printList.empty() && line == printList.front().line_num)//�����ͬһ��
                printList.pop();

		while (!printList.empty() && line < printList.front().line_num)//�������һ��
		{
			for (i = 0; i < IndentNum; i++)//����
				fputc('\t', print_fp);

			while ((c = fgetc(fp)) != '\n')//����������д���ļ�
				fputc(c, print_fp);

			fputc(c, print_fp);//�����з�д���ļ�
			line++;
		}
	}
	while ((c = fgetc(fp)) != EOF)//��ʣ������д���ļ�
		fputc(c, print_fp);

	fclose(print_fp);//�ر��ļ�
	return OK;
}