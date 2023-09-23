#include"file_writer.h"

status PrintFile(FILE* fp) 
{
	int IndentNum=0, line = 1;//IndentNum为缩进个数，line为行数
	int i;//循环变量
    char c;//用于读取文件

	FILE* print_fp;

	char filename[30] = "C_OUT.txt";//输出文件名
	print_fp = fopen(filename, "w");

	while (!printList.empty())
	{
		IndentNum = printList.front().indent;//缩进个数
		printList.pop();
		while (!printList.empty() && line == printList.front().line_num)//如果是同一行
                printList.pop();

		while (!printList.empty() && line < printList.front().line_num)//如果是下一行
		{
			for (i = 0; i < IndentNum; i++)//缩进
				fputc('\t', print_fp);

			while ((c = fgetc(fp)) != '\n')//将该行内容写入文件
				fputc(c, print_fp);

			fputc(c, print_fp);//将换行符写入文件
			line++;
		}
	}
	while ((c = fgetc(fp)) != EOF)//将剩余内容写入文件
		fputc(c, print_fp);

	fclose(print_fp);//关闭文件
	return OK;
}