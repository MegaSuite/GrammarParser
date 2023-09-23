#include"structure_define.h"
#include<cmath>


/*树的相关函数*/
status InitTree(CTree& T) //初始化树
{
	T.n = 0; T.r = -1;	//根的初始位置为-1，说明当前树没有根
	return OK;
}


//插入孩子,在p结点处插入孩子子树c，i表示第i棵子树
status InsertChild(CTree& T, int p, int i, CTree c)
{
	if (p < 0 || p >= T.n)
        return ERROR;

    if (!c.n)
        return ERROR;

    int k = 0, j = T.n;

    CNode prior = T.nodes[p].FirstChild;
	CNode cur = prior;
	CNode t;

    while (k < c.n)  //添加子树
	{
		T.nodes[j] = c.nodes[k++];
		for (t = T.nodes[j].FirstChild; t; t = t->next)
            t->child += T.n;

        j++;
	}

	t = (CNode)malloc(sizeof(CTNode));

	t->child = T.n + c.r;	//子树根的位置
	t->next = nullptr;
	T.n += c.n;

	if (i == 1)
	{
		if (prior)
		{
			t->next = prior;
			prior = t;
		}
		else
            prior = t;

        T.nodes[p].FirstChild = prior;
	}
	else if (i < 1)
        return ERROR;//如果i输入非法，返回ERROR
    else
    {
		k = 1;//k表示当前是第几棵子树
		while (k < i && cur)
		{
			k++;
			prior = cur;
			cur = cur->next;
		}
		if (cur)
		{
			prior->next = t;
			t->next = cur;
		}
		else if (k == i)
		{
			prior->next = t;
			t->next = NULL;
		}
		else
            return ERROR;
    }
	return OK;
}


//求孩子结点的双亲结点
status GetParent(CTree T, int child, int& parent)
{
	CNode t; int i = 0;
	if (child >= T.n)
        return ERROR;

    for (; i < T.n; i++)
	{
		t = T.nodes[i].FirstChild;
		while (t && t->child != child)
			t = t->next;

		if (t && t->child == child)
		{
			parent = i;
			return OK;
		}
	}
	return INFEASIBLE;
}


//求树的深度
status TraverseTree(CTree T, status(*visit)(char*, int))
{
	stack<int> stack;
	int status = 0;//用来标志是否所有孩子都被访问过
	int i; int j;
	int indent = 0;//缩进量
	int parent;
	CNode t;
	int visited[100] = { 0 };//访问标志数组初始化

	if (!T.n)
        return OK;//树为空直接结束

    for (i = 0; i < T.n; i++)
	{
		indent = 0;
		if (!visited[i])//对尚未访问的结点进行访问
		{
			stack.push(i);
			visited[i] = 1;
			if (GetParent(T, i, parent) == OK)
				indent += T.nodes[parent].indent;

			if (T.nodes[i].indent)
				visit(T.nodes[i].data, indent);

			t = T.nodes[i].FirstChild;

			while (t && !status)//如果该结点有孩子
			{
				while (visited[t->child] && t->next)//寻找未被访问过的孩子
					t = t->next;

				if (!visited[t->child])
				{
					visited[t->child] = 1;
					if (T.nodes[t->child].FirstChild)
						stack.push(t->child);

					GetParent(T, t->child, parent);
					indent += T.nodes[parent].indent;
					if (T.nodes[t->child].indent)
                        visit(T.nodes[t->child].data, indent);

                    t = T.nodes[t->child].FirstChild;
					status = 0;
				}
				else
                    status = 1;
			}
		}
		while (!stack.empty())//循环到栈为空
		{
			j = stack.top();
			indent -= T.nodes[j].indent;
			t = T.nodes[j].FirstChild;
			status = 0;
			while (t && !status)//如果该结点有孩子
			{
				while (visited[t->child] && t->next)//寻找未被访问过的孩子
					t = t->next;

				if (!visited[t->child])
				{
					visited[t->child] = 1;
					if (T.nodes[t->child].FirstChild)
						stack.push(t->child);

					GetParent(T, t->child, parent);
					indent += T.nodes[parent].indent;

					if (T.nodes[t->child].indent)
						visit(T.nodes[t->child].data, indent);

					t = T.nodes[t->child].FirstChild;
					status = 0;
				}
				else
                    status = 1;
			}
			if (t)
                stack.pop();
		}
	}
	return OK;
}


/*栈的相关函数*/
status InitStack(SqStack& S)//构造一个空栈S
{
	S.base = (SElemType*)malloc(100 * sizeof(SElemType));
	if (!S.base)
        exit(OVERFLOW);	//存储分配失败
	S.top = S.base;
	S.StackSize = 100;
	return OK;
}


//若栈不空，则用e返回S的栈顶元素，并返回OK；否则返回ERROR
status GetTop(SqStack S, SElemType& e)
{
	if (S.top == S.base)
        return ERROR;
	e = *(S.top - 1);
	return OK;
}


//插入元素e为新的栈顶元素
status Push(SqStack& S, SElemType e)
{
	if (S.top - S.base >= S.StackSize)//栈满，追加存储空间
	{
		S.base = (SElemType*)realloc(S.base,(S.StackSize + 100) * sizeof(SElemType));
		if (!S.base)
            exit(OVERFLOW);	//存储分配失败
		S.top = S.base + S.StackSize;
		S.StackSize += 100;
	}
	*S.top++ = e;
	return OK;
}


//若栈不空，则删除S的栈顶元素，用e返回其值，并返回OK；否则返回ERROR
status Pop(SqStack& S, SElemType& e)
{
	if (S.top == S.base)
        return ERROR;
	e = *(--S.top);
	return OK;
}