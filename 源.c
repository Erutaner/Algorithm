#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
typedef struct Queue
{
	int* data;
	int head, tail;
	int length, cnt;
}Queue;

Queue* init(int n)
{
	Queue* q = (Queue*)malloc(sizeof(Queue));
	if (!q)return q;
	q->data = (int*)malloc(sizeof(int) * n);
	if (!(q->data))return q;
	q->head = q->tail = q->cnt = 0;
	q->length = n;//��������length����
	return q;//���Ƿ���ֵ����Ϊָ��
}

int empty(Queue* q)
{
	if (!q)return 0;
	return q->cnt==0;//��дΪ��  q->head == q->tail, ��head��tail�غϣ��п�����head����ǰ�棬���иոշ�����tail�ص���һ��Ԫ�ص�λ�ã���ʱ����������
}

int front(Queue* q)
{
	if (!q)return 0;
	if (!q->cnt)return 0;
	return (q->data[q->head]);
}

int push(Queue* q, int val)
{
	if (!q)return 0;
	if (q->cnt == q->length)return 0;
	q->data[q->tail++] = val;
	if (q->tail == q->length)q->tail -= q->length;//�ҽ���һ�з�������һ�����棬��ᵼ�º������ý����� tail��ָ�롱Խ�������
	q->cnt++;
	return 1;
}

int pop(Queue* q)
{
	if (!q)return 0;
	if (empty(q))return 0;
	q->head++;
	if (q->head == q->length)
		q->head -= q->length;
	q->cnt--;
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
	if (!q)return;
	int ind = 0;
	printf("Queue = [");
	for (int i = q->head, j = 0;j < q->cnt;j++)
	{
		ind = (i + j) % q->length;//��ģ����cnt
		if (ind == q->head)
		{
			printf("%d", q->data[ind]);
		}
		else
		{
			printf(" %d", q->data[ind]);
		}
	}
	printf("]\n");
	return;
}

int main(void)
{
	#define MAX_OP 20
	srand(time(0));
	Queue* q = init(MAX_OP);
	for (int i = 0;i < MAX_OP;i++)
	{
		int val = rand() % 100;
		int op = rand() % 2;
		switch (op)
		{
			case 0:
			{
				printf("Push %d to queue = %d\n", val, push(q, val));
			}break;
			case 1:
			{
				if (empty(q))
				{
					printf("The queue is empty, pop from queue = %d\n", pop(q));
					break;
				}
				else
				{
					int fir = front(q);
					printf("Pop %d from queue = %d\n", fir, pop(q));
					break;
				}
			}
		}
		output(q);
	}
	printf("Queue head = %d               Queue tail = %d                Queue count = %d\n",
		q->head,
		q->tail,
		q->cnt);
	for (int i = 0;i < MAX_OP;i++)
	{
		int val = rand() % 100;
		printf("Push %d to queue = %d\n", val, push(q, val));
		output(q);
	}
	clear(q);

	return 0;
}