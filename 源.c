#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
typedef struct Queue
{
	int* data;
	int head, tail;
	int length, cnt;//cnt����ǰ�����д洢��Ԫ��������
}Queue;

Queue* init(int n)
{
	Queue* q = (Queue*)malloc(sizeof(Queue));
	if (!q)return (q);//�������ڴ�֮���һ���¾����ж�
	q->data = (int*)malloc(sizeof(int) * n);
	q->head = q->tail = q->cnt = 0;//ȫ�¸�ֵ��ʽ
	q->length = n;//length��ʾ������������ܳ���
	return (q);
}

int empty(Queue* q)//Judge whether the queue is empty
{
	if (!q)return 0;
	return q->cnt == 0;//����Ԫ�ظ���Ϊ���򷵻�1
}

int front(Queue* q)
{
	if (!q)return 0;
	return (q->data[q->head]);
}

int push(Queue* q, int val)//������Ӳ���
{
	if (!q)return 0;
	if (q->cnt == q->length)return 0;//tail��head �����±꣬tail���������һ��Ԫ�ص��±꣬���Ǳ����Ԫ�ص��±��һ
	q->data[q->tail++] = val;//tail��λ�ÿ������Ϊ����Ϊ�ա���������ָʾ����ʱ�����ģ�ÿ�β�����֮��tail����ƶ�һλ
	if (q->tail == q->length) q->tail -= q->length;//���ƶ���֮���±�����ˣ���֮��Ϊ��
	q->cnt += 1;
	return 1;
}

int pop(Queue* q)//���г��Ӳ���
{
	if (!q)return 0;
	if (empty(q))return 0;
	q->head++;
	if (q->head == q->length) q->head -= q->length;
	q->cnt -= 1;
	return 1;
}

void clear(Queue* q)
{
	if (!q)return;
	free(q->data);
	free(q);
		return;
}

void output(Queue* q)
{
	printf("queue = [");
	for (int i = q->head,j = 0;j < q->cnt;j++)//ȫ��ѭ����ʽ��ͬʱ������������ʱ�ڶ���ǰ�治�ܼ�int
	{
		int ind = (i + j) % q->length;//�ǳ������һ���±����÷��������Դ�headλ�ÿ�ʼ����ߣ�������󣬴������ڴ��ͷ������������ֱ�������е����һ��Ԫ��
		if (ind == q->head)
		{
			printf("%d",q->data[ind]);
			continue;
		}
		printf(" %d", q->data[ind]);
	}
	printf("]\n");
	return;
}
int main(void)
{
	srand(time(0));
	#define MAX_OP 20
	Queue* q = init(MAX_OP);
	for (int i = 0;i < MAX_OP;i++)
	{
		int val = rand() % 100, op = rand() % 2;
		switch (op)
		{
			case 0:
			{
				printf("Push %d to queue = %d\n", val, push(q, val));
			}break;
			case 1:
			{
				int head = front(q);
				int ret = pop(q);
				if (!ret)
				{
					printf("The queue is empty, pop from queue = %d\n",ret);
					break;
				}
				printf("Pop %d from queue = %d\n", head, ret);
				break;

			}
		}
		output(q);
	}
	printf("Head: %d                            Tail:%d                      Count:%d\n", q->head, q->tail, q->cnt);
	for (int i = 0;i < MAX_OP;i++)
	{
		int val = rand() % 100;
		printf("Push %d to queue = %d\n", val, push(q, val));
		output(q);
	}
	clear(q);
	return 0;
}