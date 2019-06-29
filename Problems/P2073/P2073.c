#include "stdio.h"
#include "stdlib.h"

#ifndef max
#define max(a,b) (((a) > (b)) ? (a) : (b))
#endif

typedef struct AVLTreeNode {
	int w;
	int c; //
	struct AVLTreeNode * left;
	struct AVLTreeNode * right;
	int height;
} *AVLTree;

#define HEIGHT(tree) (tree ? tree->height : 0)

//"���캯��"
AVLTree newAVLTreeNode(int w, int c) {
	AVLTree tree = (AVLTree)malloc(sizeof(struct AVLTreeNode));
	tree->w = w;
	tree->c = c;
	tree->left = NULL;
	tree->right = NULL;
	tree->height = 1;
	return tree;
}

//����
AVLTree leftRotate(AVLTree tree) {
	AVLTree k = tree->right;
	tree->right = k->left;
	k->left = tree;
	tree->height = max(HEIGHT(tree->left), HEIGHT(tree->right)) + 1;
	k->height = max(HEIGHT(tree), HEIGHT(k->right)) + 1;
	return k;
}

//����
AVLTree rightRotate(AVLTree tree) {
	AVLTree k = tree->left;
	tree->left = k->right;
	k->right = tree;
	tree->height = max(HEIGHT(tree->left), HEIGHT(tree->right)) + 1;
	k->height = max(HEIGHT(k->left), HEIGHT(tree)) + 1;
	return k;
}

AVLTree insert(AVLTree tree, int w, int c) {
	if (tree == NULL) {
		tree = newAVLTreeNode(w, c); //�����½��
		return tree;
	}
	if (c == tree->c) return tree; //��ֵΪc�Ľ���Ѵ��ڣ�ֱ�ӷ���tree
	else if (c < tree->c) { //����������
		tree->left = insert(tree->left, w, c); //�ݹ�������
		tree->height = max(HEIGHT(tree->left), HEIGHT(tree->right)) + 1;
		if (HEIGHT(tree->left) - HEIGHT(tree->right) == 2) { 
			if (c > tree->left->c) {
				//������������������
				tree->left = leftRotate(tree->left);
			}
			tree = rightRotate(tree);
		}
	}
	else { //������������Գ�
		tree->right = insert(tree->right, w, c);
		tree->height = max(HEIGHT(tree->left), HEIGHT(tree->right)) + 1;
		if (HEIGHT(tree->right) - HEIGHT(tree->left) == 2) {
			if (c < tree->right->c) {
				tree->right = rightRotate(tree->right);
			}
			tree = leftRotate(tree);
		}
	}
	return tree;
}

AVLTree deleteMin(AVLTree tree) {
	if (tree == NULL) return NULL;
	if (tree->left == NULL) { //û����������, tree����С��
		AVLTree tmp = tree;
		tree = tree->right; //����������tree����û����������tree����ΪNULL
		free(tmp);
		return tree;
	}
	tree->left = deleteMin(tree->left);
	tree->height = max(HEIGHT(tree->left), HEIGHT(tree->right)) + 1;
	if (HEIGHT(tree->right) - HEIGHT(tree->left) == 2) {
		if (HEIGHT(tree->right->left) > HEIGHT(tree->right->right)) {
			//�൱�ڲ��뺯���У������������������������
			tree->right = rightRotate(tree->right);
		}
		tree = leftRotate(tree);
	}
	return tree;
}

AVLTree deleteMax(AVLTree tree) {
	//��deleteMin�Գ�
	if (tree == NULL) return NULL;
	if (tree->right == NULL) {				
		AVLTree tmp = tree;
		tree = tree->left;
		free(tmp);
		return tree;
	}
	tree->right = deleteMax(tree->right);
	tree->height = max(HEIGHT(tree->left), HEIGHT(tree->right)) + 1;
	if (HEIGHT(tree->left) - HEIGHT(tree->right) == 2) {
		if (HEIGHT(tree->left->right) > HEIGHT(tree->left->left)) {
			//�൱�ڲ����������������������
			tree->left = leftRotate(tree->left);
		}
		tree = rightRotate(tree);
	}
	return tree;
}

int total_w = 0, total_c = 0;
void dfs(AVLTree tree) {
	if (tree == NULL) return;
	total_w += tree->w;
	total_c += tree->c;
	dfs(tree->left);
	dfs(tree->right);
}

void deleteTree(AVLTree tree) {
	if (tree == NULL) return;
	deleteTree(tree->left);
	deleteTree(tree->right);
	free(tree);
}

int main() {
	AVLTree tree = NULL;
	int cmd, w, c;
	while (1) {
		scanf("%d", &cmd);
		if (cmd == -1) {		
			dfs(tree);	
			printf("%d %d\n", total_w, total_c);
			break;
		}
		else if (cmd == 1) {
			scanf("%d %d", &w, &c);
			tree = insert(tree, w, c);
		}
		else if (cmd == 2) {
			tree = deleteMax(tree);
		}
		else if (cmd == 3) {
			tree = deleteMin(tree);
		}
	}
	deleteTree(tree);
	return 0;
}