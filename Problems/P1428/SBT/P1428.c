#include "stdio.h"
#include "stdlib.h"

typedef struct TNode {
	int key;
	size_t key_num; //key���ִ���
	size_t num_size; //���в����˶��ٸ���
	size_t node_size; //���Ľ�����
	struct TNode *left, *right;
} *Tree;

size_t getKeyNum(Tree t) { return t ? t->key_num : 0; }
size_t getNumSize(Tree t) { return t ? t->num_size : 0; }
size_t getNodeSize(Tree t) { return t ? t->node_size : 0; }

Tree newTNode(int key); //�����½��

Tree leftRotate(Tree t); //����
Tree rightRotate(Tree t); //����

//ά��ƽ��
Tree maintain(Tree t);
Tree maintainLeft(Tree t);
Tree maintainRight(Tree t);

//����key
Tree insert(Tree t, int key);

//ɾ���ڴ�
void deleteTree(Tree t);

size_t smaller_num_; //��¼����������ж��ٸ���С�ڴ�������

int main() {
	int n, key;
	scanf("%d", &n);
	Tree t = NULL;
	for (int i = 0; i < n; i++) {
		scanf("%d", &key);
		smaller_num_ = 0;
		t = insert(t, key);
		if (i) putchar(' ');
		printf("%d", smaller_num_);
	}
	deleteTree(t);
	return 0;
}

Tree newTNode(int key) {
	Tree t = (Tree)malloc(sizeof(struct TNode));
	t->key = key;
	t->key_num = 1;
	t->num_size = 1;
	t->node_size = 1;
	t->left = t->right = NULL;
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
	//ά��ƽ�⣬��֤������������������node_sizeС����������node_size
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
	//ά��ƽ�⣬��֤������������������node_sizeС����������node_size
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
	t->num_size++; //ֻҪ��������num_size����1
	if (key == t->key) { //key֮ǰ�Ѳ����
		t->key_num++;
		smaller_num_ += getNumSize(t->left); //�����������н���keyС��key��ע��getNumSize����getNodeSize
	}
	else if (key < t->key) {		
		size_t tmp_size = getNodeSize(t->left); //��¼��������node_size
		t->left = insert(t->left, key); //�ݹ�������
		if (getNodeSize(t->left) > tmp_size) { //����������node_size�仯�������������½��˽��
			t->node_size++;
			t = maintainLeft(t); //ά��ƽ��
		}
	}
	else { //key > t->key
		smaller_num_ += getNumSize(t->left) + t->key_num; //�����������н���keyС��key����t�������ҲС��key
		size_t tmp_size = getNodeSize(t->right); //��¼��������node_size
		t->right = insert(t->right, key); //�ݹ����������
		if (getNodeSize(t->right) > tmp_size) { //����������node_size�仯�������������½��˽��
			t->node_size++;
			t = maintainRight(t); //ά��ƽ��
		}
	}
	return t;
}

void deleteTree(Tree t) {
	if (t == NULL) return;
	deleteTree(t->left);
	deleteTree(t->right);
	free(t);
}