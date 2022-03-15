#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
/*
	���ڵݹ�ļ���������⣺
	1. �ݹ麯����˼·�ǽ�ĳ�ֺ�������ʱ�����������з������ۣ��������Ϊ����ֵ�ࡱ�͡��ݹ��ࡱ����
	2. ��ֵ���ǽӽ���ײ�����������̬���ݹ���������ֵ���𼶿���
	3. ��ֵ��д��ǰ���ݹ���д�ں�
	4. ����ֵ��Ϊ��ֵ����ֵ�͵�������ֵ��ǰ����ζ��������򻯺�����ײ����⣬���߷��ڵݹ���֮�����ڡ��������ݹ����
	5. �ݹ���ͱ�ֵ�඼����Ϊ���������һ���ݹ�������ж���ݹ���ڣ�Ҳ�����ж���ݹ������ѡ��ִ�У��������clearNode��insertNode��
	6. �ݹ���ں͵�������ֵ֮������в������ò���Ϊ��������֮ǰ���Ҫ��ɵ�������ɾ���ڵ㣩
*/
typedef struct Node
{
	int val;
	struct Node* lchild, * rchild;
}Node;//�ڵ����͸��������������ָ��

typedef struct Tree
{
	Node* root;//���ڵ��ַ��ע�����ĵ�ַ��ͬ�ڸ��ڵ�ĵ�ַ
	int n;//��ǰ�������ڵ���Ŀ
}Tree;//�����ͱ����Ÿ��ڵ��ַ��������һЩ�����ѧ������˫�ṹ����ֹ�������Ϊ���ƣ����ֳ����ʵ�ͬһ��

Node* getNewNode(int val)//�����ڵ㣬��ʼ���ڵ㣬���ؽڵ��ַ
{
	Node* p = (Node*)malloc(sizeof(Node));//��ȡһ���ڵ�
	if (!p)return p;//�п�
	p->val = val;//������ֵ
	p->lchild = p->rchild = NULL;//ָ����ֵ����ֵΪ�գ��д��������
	return p;//�����ڵ��ַ
}

Tree* getNewTree()//����������ʼ�������������ĵ�ַ
{
	Tree* tree = (Tree*)malloc(sizeof(Tree));//����һ��������ȡ���ĵ�ַ
	if (!tree)return tree;//�п�
	tree->n = 0;//��ʼ�����������ڵ���Ϊ��
	tree->root = NULL;//��ʼ�����ڵ�
	return tree;//�����ĵ�ַ����
}

Node* insertNode(Node* root, int val,int* ret)//�������ۣ���ֵ�ࡢ�ݹ�������ж������ֵ���ǰ��
{
	if (root == NULL)//��һ����ֵ�ࣺ�ڵ㲻���ڣ�ֻҪ���ֽڵ���ھͲ���ִ����һ�顣
	{
		*ret = 1;//��ret��ֵΪ1
		return getNewNode(val);//����getNewNode������getNewNode�ķ���ֵ����һ���½ڵ��ַ
	}//���ڵ�һ����ֵ�࣬����һ���µĽڵ㣬�����ɲ����ڱ�Ϊ���ڣ������½��ڵ�ĵ�ַ
	if (root->val == val)return root;//�ڶ�����ֵ�ࣺ����ڵ��������ȡֵ�������������ͬ����ֱ�ӷ��ش���ڵ�ĵ�ַ���������½ڵ�
	if (root->val > val)root->lchild = insertNode(root->lchild, val,ret);//��һ�ݹ��ࣺ���ֽڵ��������ȡֵ���ڴ��������ݣ��ݹ���ñ�������������ֵ��ֵ����ָ�룬��ȷ�����β�������������ĳ��λ��
	else root->rchild = insertNode(root->rchild, val,ret);//�ڶ��ݹ��ࣺ�����ֽڵ��������ȡֵС�ڴ��������ݣ��ݹ���ñ�������������ֵ��ֵ����ָ�룬��ȷ�����β�������������ĳ��λ��
	return root;//���ر��ֽڵ�ĵ�ַ��ǰһ�֣����ڡ���������ֵ�������ֵ����ֵ��Ӧ����ݹ���֮��û���������㣬����𼶿��ٽ��������ݹ����
}//С������壬������Ҳ壬���������

void insert(Tree* tree, int val)
{
	int flag = 0;
	tree->root = insertNode(tree->root, val,&flag);//�������������ĸ��ڵ�ĵ�ַ
	tree->n += flag;//�������⴫����Ϣ����ͨ������ֵ��ַ�����½��˽ڵ㣬���ں����ڲ�flag�ᱻ��ֵΪ1
	return;
}
void clearNode(Node* node)
{
	if (!node)return;//�ӽڵ�Ҳ�ǽڵ㣬Ҳ�����ӽڵ�ĸ��ڵ㣬��ʶ���������ӵĸ�  ��һ��ֵ�ࣺ�ڵ㲻����
	clearNode(node->lchild);//�ݹ�ǰ����return��ǰ��ı�ֵ����������ֹ���룬����������𼶷��أ���ϣ�������������ֵ��ʲô��������return�ķ���ֵһ�����ʲô
	clearNode(node->rchild);//˫�ݹ���ڣ�����ĳ�ڵ�û�����������������������
	free(node);//����ڵݹ�������𼶷���֮��Ĳ��������µ���������
	return;
}//�˺������������ݹ���ڣ���ֻ��һ���ݹ���

void clearTree(Tree* tree)
{
	clearNode(tree->root);
	free(tree);
	return;
}

void outputNode(Node* root)
{
	if (root == NULL)return;//��һ��ֵ�ࣺ�ڵ㲻���ڣ���������
	printf("%d", root->val);//�ڵ���ڣ������������������
	if (root->lchild == NULL && root->rchild == NULL)return;//�ڶ���ֵ�࣬�ڵ�Ϊ������Ľڵ㣬���������Ѿ�����˱��ڵ����ݣ���ֱ�ӽ���
	printf("(");//�ڵ�Ϊ���ڵ㣬���ӡ���������������׼��
	outputNode(root->lchild);//�ݹ��ࣺ���ӽڵ㣬����ȷ���������ң�����ڸ��������ڵ�
	printf(",");
	outputNode(root->rchild);//����ڸ�������ҽڵ�
	printf(")");
	return;
}

void outputTree(Tree* tree)
{
	printf("tree(%d) = ", tree->n);
	outputNode(tree->root);
	printf("\n\n"); 
	return;
}

void preorderNode(Node* node)
{
	if (!node)return;
	printf(" %d", node->val);
	preorderNode(node->lchild);
	preorderNode(node->rchild);
	return;
}

void preorder(Tree* tree)
{
	printf("Preorder : ");
	preorderNode(tree->root);
	printf("\n\n");
	return;
}

void inorderNode(Node* node)
{
	if (!node)return;
	inorderNode(node->lchild);
	printf(" %d", node->val);
	inorderNode(node->rchild);
	return;
}

void inorder(Tree* tree)
{
	printf("Inorder : ");
	inorderNode(tree->root);
	printf("\n\n");
	return;
}

void postorderNode(Node* node)
{
	if (!node)return;
	postorderNode(node->lchild);
	postorderNode(node->rchild);
	printf(" %d", node->val);
	return;
}

void postorder(Tree* tree)
{
	printf("Postorder : ");
	postorderNode(tree->root);
	printf("\n\n");
	return;
}

int main(void)
{
	srand(time(0));
	Tree* tree = getNewTree();
	for (int i = 0;i < 10;i++)
	{
		int val = rand() % 100;
		insert(tree, val);
		outputTree(tree);
	}
	preorder(tree);
	inorder(tree);
	postorder(tree);
	clearTree(tree);

	return 0;
}