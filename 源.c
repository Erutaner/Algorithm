#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
typedef struct Vector
{
	int* data;//��ָ�����;����˿������ݵ�����
	int size, length;
}Vector;
Vector* init(int n)
{
	Vector* vec = (Vector*)malloc(sizeof(Vector));//�����ڴ濪�ٺ��������뵽ʧ�ܻ�����
	if (vec == NULL)return vec;//��ʧ����ֱ�ӷ��ؿ�ָ��
	vec->data = (int*)malloc(sizeof(int) * n);//data����ά��������ݵ���һ������ڴ�
	vec->size = n;
	vec->length = 0;
	return vec;//�����ռ��ں��������󲻻��Զ��ͷţ�����ֻҪ��ָ�봫��ȥ�Ϳ����ں�����ά��
}//˳���ĳ�ʼ������
int expand(Vector* vec)
{
	int new_size = 2 * vec->size;//����ֱ��vec->size*=2; Ҫȷ���ڴ���չ�ɹ����ٸı�size��ֵ
	int* ptr = (int*)realloc(vec->data, new_size*sizeof(int));
	if (!ptr)return 0;
	else
	{
		vec->size = new_size;
		vec->data = ptr;
		return 1;
	}
}

int insert(Vector* vec, int ind, int val)//ind ��ʾindex   val��ʾvalue
{
	if (vec == NULL)return 0;//�Ƿ�����
	if (vec->size == vec->length)
	{
		if (!expand(vec))return 0;
		printf("Expand Vector size to %d succeeded\n", vec->size);
	}
	if (ind<0 || ind>vec->length)return 0;//�±�С������±���ڵ�ǰԪ�ص�  �±����length ��ʱ���ǺϷ���
	for (int i = vec->length;i > ind;i--)//������Ԫ�ض�����һλ��Ϊ������Ԫ��������λ
	{
		vec->data[i] = vec->data[i-1];
	}
	vec->data[ind] = val;//��ָ��ά��һ��˳���ʹ�÷�������������
	vec->length += 1;
	return 1;
}//ʵ�ֲ������
int erase(Vector* vec, int ind)
{
	if (vec == NULL)return 0;
	if (vec->length == 0)return 0;
	if (ind < 0 || ind >= vec->length)return 0;//���жϴ˴β����Ϸ���
	for (int i = ind;i < vec->length-1;i++)
	{
		vec->data[i] = vec->data[i + 1];
	}
	vec->length-=1;
	return 1;
}//ɾ������
void clear(Vector* vec)
{
	if (vec == NULL)return;
	free(vec->data);
	free(vec);
	return;
}//˳��������
void output(Vector* vec)
{
	if (!vec)return;
	printf("Vector(%d)=[", vec->length);
	for (int i = 0;i < vec->length;i++)
	{
		if (i)printf(", ");
		printf("%d", vec->data[i]);
	}
	printf("]\n\n");
	return;//��ʹ���ؿ�ֵ��ҲҪ��ò�Ե�returnһ��
}
int main(void)
{
	srand(time(0));
	#define MAX_OP 20
	Vector* vec = init(1);
	int op, ind, val;
	for (int i = 0;i < MAX_OP;i++)
	{
		op = rand() % 2;
		ind = rand() % (vec->length + 1);//ģ���ǷǷ���
		val = rand() % 100;
		switch (op)
		{
		case 0:
		{
			insert(vec, ind, val);
			printf("Inserted %d at %d to Vector, the length now is %d\n", val, ind, vec->length);
		}break;
		case 1:
		{
			if (ind == vec->length)continue;//switch case ������ѭ���ڵ�
			erase(vec, ind);//eraseȷʵ����Ķ��±�Ϊlength���ڴ棬���÷�֧�ṹ�Ի����һ�飬������һ�������Ϊ�����������ʱ������������printf
			printf("Erased item at %d from Vector, the length now is %d\n", ind, vec->length);
		}break;
		}
		output(vec);
	}

	return 0;
}