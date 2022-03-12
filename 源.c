#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
typedef struct Stack
{
	int* data;
	int top, size;
}Stack;

Stack* init(int n)
{
	Stack* s = (Stack*)malloc(sizeof(Stack));
	if (!s)return s;
	s->data = (int*)malloc(sizeof(int) * n);
	if (!s->data)return NULL;
	s->top = -1;
	s->size = n;
	return s;
}

int empty(Stack* s)
{
	if (!s)return 2;
	return s->top == -1;
}

int clear(Stack* s)
{
	if (!s)return 0;
	free(s->data);
	free(s);
	return 1;
}

int top(Stack* s)
{
	if (!s)return 0;
	if (empty(s))return 0;
	return s->data[s->top];
}

int push(Stack* s, int val)
{
	if (!s)return 0;
	if (s->size == s->top + 1)return 0;
	s->top++;
	s->data[s->top] = val;
	return 1;
}

int pop(Stack* s)
{
	if (!s)return 0;
	if (empty(s))return 0;
	s->top -= 1;
	return 1;
}

void output(Stack* s)
{
	if (!s)return;
	printf("Stack(%d) = [", s->top + 1);
	for (int i = s->top;i >= 0;i--)//ע�⵹�������������������Ϊ���Լ�
	{
		if (i == s->top)
			printf("%d", s->data[i]);
		else
			printf(" %d", s->data[i]);
	}
	printf("]\n");
	return;
}
int main(void)
{
	#define MAX_OP 20
	Stack* s = init(MAX_OP);
	srand(time(0));
	for (int i = 0;i < MAX_OP;i++)
	{
		int val = rand() % 100, op = rand() % 3;
		switch (op)
		{
			case 0:
			{
				if (empty(s) == 2)//������һ���汾����bug�ģ���ʵֻ��Ҫ�ж��䲻����2�������ٳɹ����Զ��庯����ʶ���ջΪ�յ����������  ����=0 ����ʽ��ʾ��
				{
					printf("The stack initialization failed\n");
					break;
				}
				else
				{
					int fir = top(s);
					printf("Pop %d from stack = %d\n", fir, pop(s));
				}
				break;
			}
			case 1:
			{
				printf("Push %d to stack = %d\n", val, push(s, val));
				break;
			}
			case 2:
			{
				printf("Push %d to stack = %d\n", val, push(s, val));
				break;
			}
		}
		output(s);
		printf("\n");
	}
	clear(s);
	return 0;
}