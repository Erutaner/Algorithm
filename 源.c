#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
typedef struct ListNode
{
	int data;//������
	struct ListNode* next;
}ListNode;//����Ľڵ��������������������ṹ
typedef struct LinkList
{
	ListNode head;//����ͷ��㣬��������ɵڸ�һ���ڵ㣬�䱾��Ҳ��һ���ڵ�����
	int length;//������ܳ���
}LinkList;//����Ľṹ�����Ϊ�����֣����������ֳ�ʼ��
ListNode* init_listnode(int val)//����ȥһ��ֵ��������һ��ָ��ýڵ��ָ��
{
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));
	if (!p)return p;
	p->data = val;
	p->next = NULL;//��ʼ��һ���ڵ�֮��nextָ��Ϊ��
	return p;
}
LinkList* init_linklist()
{
	LinkList* l = (LinkList*)malloc(sizeof(LinkList));
	if (!l)return l;
	l->head.next= NULL;//����ͷ�ڵ����һλ�����ǵ���λ��ע��������Ҳ�е���λ��˵��
	l->length = 0;
	return l;
}//��������ʼ�������������ٲ���
void clear_listnode(ListNode* node)
{
	if (!node)return;
	free(node);//�������ڵ����������malloc�����ģ��ǵ������������������ٽڵ㱾��
	return;
}
void clear_linklist(LinkList* l)
{
	if (!l)return;
	ListNode* p = l->head.next, * q;
	while (p)//˳������ȥ����ÿһ���ڵ�
	{
		q = p->next;
		clear_listnode(p);//��������õĺ��������������涨�����
		p = q;
	}
	free(l);
	return;
}
int insert(LinkList* l, int ind, int val)//����ֵ����ɹ���ʧ��
{
	if (!l)return 0;
	if (ind<0 || ind>l->length)return 0;
	ListNode* p = &(l->head), * node = init_listnode(val);
	while (ind--)//������ͷ�ڵ㿪ʼ�������ind����ע������ͷ�ڵ�Ҳ�Ǹ��ڵ����͵Ľṹ��
	{
		p = p->next;//��ѭ��������pָ�������λ�õ�ǰһ��λ��
	}
	node->next = p->next;//����ָ����Ϊ��ֵ���ڵ�ʱ�����Ϊĳһ���ĵ�ַ����һ�θ��������ֵʱ����һ���ǰ�NULL��NULL
	p->next = node;//��Ϊ��ֵ���ڵ�ʱ�����Ϊĳһ�ڵ���ָ�����ŵ�ֵ
	l->length += 1;
	return 1;
}
int erase(LinkList* l, int ind)
{
	if (!l)return 0;
	if (ind < 0 || ind >= l->length)return 0;
	ListNode* p = &(l->head), * q;
	while (ind--)
	{
		p = p->next;
	}
	q = p->next->next;//pָ���ɾ���ڵ��ǰһ��λ�ã�����->nextָ���ɾ���ڵ����һ��λ�ã��ȰѸ�λ�ñ���
	clear_listnode(p->next);//ɾ����ɾ���ڵ�
	p->next = q;//��p��ָ����ֵΪ��������һ���ڵ����һ���ڵ�ĵ�ַ
	l->length -= 1;//�����ɾ����Ҫ�Ѽ�¼���ȵ�length�Լ�
	return 1;
}
void output(LinkList* l)//�������Ҳ�ǽṹ����
{
	printf("LinkList(%d) : ", l->length);
	for (ListNode* p = l->head.next;p;p = p->next)//��һ��������������ʼ��һ��������ָ�������ڵ㣬�ڶ����ж�p�Ƿ�Ϊ��ָ�룬��������λp
	{
		printf("%d -> ", p->data);
	}
	printf("NULL\n");
	return;
}
#define MAX_OP 30
int main(void)
{
	srand(time(0));
	LinkList* l = init_linklist();
	for (int i = 0;i < MAX_OP;i++)
	{
		int op = rand() % 3;
		int ind = rand() % (l->length + 1);
		int val = rand() % 100;
		switch (op)
		{
		case 0:
		case 1:
		{
			printf("Inserted %d at %d to LinkList = %d\n",//ע�ⶺ�Ŵ�ĩβ���Ի��м�������
				val, ind, insert(l, ind, val));//���һ��%d�����Ƿ�ɹ�
		}break;
		case 2:
		{
			printf("Erased item at %d from LinkList = %d\n",
				ind, erase(l, ind));
		}break;
		}
		output(l);
		printf("\n");
	}
	clear_linklist(l);
	return 0;
}