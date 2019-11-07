#include "stdio.h"
#include "stdlib.h"

typedef struct TNode {
	int key;
	size_t key_num, num_size, node_size;
	struct TNode *left, *right;
} *Tree;

size_t getKeyNum(Tree t) { return t ? t->key_num : 0; }
size_t getNumSize(Tree t) { return t ? t->num_size : 0; }
size_t getNodeSize(Tree t) { return t ? t->node_size : 0; }

Tree newTNode(int key); //�����½��
Tree leftRotate(Tree t); //����
Tree rightRotate(Tree t); //����
Tree maintain(Tree t); //ά��ƽ��
Tree maintainLeft(Tree t); //ά��ƽ��--�ж��Ƿ���ڲ�������������������node_size������������node_size�����
Tree maintainRight(Tree t);  //ά��ƽ��--�ж��Ƿ���ڲ�������������������node_size������������node_size�����

Tree insert(Tree t, int key); //����key
int greater_num_; //global���������ڼ����ж��������ڴ�������
void deleteTree(Tree t); //ɾ���ڴ�

int main() {
	int n, key;
	scanf("%d", &n);
	long long result = 0;
	Tree t = NULL;
	for (int i = 0; i < n; i++) {
		scanf("%d", &key);
		greater_num_ = 0;
		t = insert(t, key);
		result += greater_num_;
	}
	printf("%lld", result);
	deleteTree(t);
	return 0;
}

Tree newTNode(int key) {
	Tree t = (Tree)malloc(sizeof(struct TNode));
	t->key = key;
	t->key_num = 1;
	t->num_size = 1;
	t->node_size = 1;
	t->left = NULL;
	t->right = NULL;
	return t;
}

Tree leftRotate(Tree t) {
	Tree k = t->right;
	t->right = k->left;
	k->left = t;
	k->num_size = t->num_size;
	k->node_size = t->node_size;
	t->num_size = getNumSize(t->left) + getNumSize(t->right) + t->key_num;
	t->node_size = getNodeSize(t->left) + getNodeSize(t->right) + 1;
	return k;
}

Tree rightRotate(Tree t) {
	Tree k = t->left;
	t->left = k->right;
	k->right = t;
	k->num_size = t->num_size;
	k->node_size = t->node_size;
	t->num_size = getNumSize(t->left) + getNumSize(t->right) + t->key_num;
	t->node_size = getNodeSize(t->left) + getNodeSize(t->right) + 1;
	return k;
}

Tree maintain(Tree t) {
	t = maintainLeft(t);
	return maintainRight(t);
}

Tree maintainLeft(Tree t) {
	//ά��ƽ��--�ж��Ƿ���ڲ�������������������node_size������������node_size�����
	if (t == NULL || t->left == NULL) return t;
	if (t->left->left && t->left->left->node_size > getNodeSize(t->right)) {
		t = rightRotate(t);
		t->right = maintain(t->right);
		t = maintain(t);
	}
	if (t->left->right && t->left->right->node_size > getNodeSize(t->right)) {
		t->left = leftRotate(t->left);
		t = rightRotate(t);
		t->left = maintain(t->left);
		t->right = maintain(t->right);
		t = maintain(t);
	}
	return t;
}

Tree maintainRight(Tree t) {
	//ά��ƽ��--�ж��Ƿ���ڲ�������������������node_size������������node_size�����
	if (t == NULL || t->right == NULL) return t;
	if (t->right->right && t->right->right->node_size > getNodeSize(t->left)) {
		t = leftRotate(t);
		t->left = maintain(t->left);
		t = maintain(t);
	}
	if (t->right->left && t->right->left->node_size > getNodeSize(t->left)) {
		t->right = rightRotate(t->right);
		t = leftRotate(t);
		t->left = maintain(t->left);
		t->right = maintain(t->right);
		t = maintain(t);
	}
	return t;
}

Tree insert(Tree t, int key) {
	if (t == NULL) {
		return newTNode(key);
	}
	t->num_size++; //�����������1
	if (key == t->key) {
		t->key_num++; //�ظ�����
		greater_num_ += getNumSize(t->right); //�ұ����н��������������key
	}
	else if (key < t->key) {
	 	//�ұ����н���������Լ�t���������������key
		greater_num_ += getNumSize(t->right) + t->key_num;
		size_t tmp_size = getNodeSize(t->left); //��������node_size
		t->left = insert(t->left, key); //�ݹ����������
		if (getNodeSize(t->left) > tmp_size) { //����������node_size�仯�����������в������½��
			t->node_size++;
			t = maintainLeft(t); //�������в������½�㣬��Ҫά��ƽ��
		}
		//����������û�в����½�㣬�����Ľṹ���䣬�����ƻ�ƽ��
	}
	else {
		size_t tmp_size = getNodeSize(t->right); //��������node_size
		t->right = insert(t->right, key); //�ݹ����������
		if (getNodeSize(t->right) > tmp_size) { //����������node_size�仯�����������в������½��
			t->node_size++;
			t = maintainRight(t); //�������в������½�㣬��Ҫά��ƽ��
		}
		//����������û�в����½�㣬�����Ľṹ���䣬�����ƻ�ƽ��
	}
	return t;
}

void deleteTree(Tree t) {
	if (t == NULL) return;
	deleteTree(t->left);
	deleteTree(t->right);
	free(t);
}