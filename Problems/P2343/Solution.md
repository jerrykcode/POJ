# P2343 ��ʯ����ϵͳ
[ԭ���ַ](https://www.luogu.org/problem/P2343)

## ��Ŀ����
GY��������һ����ʯ�Ž��˲ֿ⡣��һ��GY����Ѫ��������Ҫ������ı�ʯ�����ǰ�m����ʯ��ȡ�����Ž��˱�ʯ����ϵͳ��ÿ����ʯi����һ�����ֵvi��
��ϣ�����ܱ�д������ҵ��Ӵ�С��n���ı�ʯ�����������������ˣ����ǳ���С�ĵ�����һЩ��ʯ�ڲֿ����棬�п���Ҫ�����е�ϵͳ����ӱ�ʯ��
��Щ��ʯ�ĸ����Ƚ��١�����ʾ�ǳ���Ǹ�����ǻ���ϣ�����ϵͳ�������á�

## �����ʽ

��һ��һ������m��q����ʾ�Ѿ�ȡ�����ı�ʯ�����Լ��������Ĳ�ѯ��������������

�ڶ���m����������ʾ��m����ʯ�����ֵ��

����q�У�ÿ����������c��n,

��c=1����ѯ�ʣ����������ǰ��n���ı�ʯ��

��c=2�������룩������ϵͳ�в������ֵΪn�ı�ʯ��

## �����ʽ

����ÿ��c=1��ѯ�ʣ�,�����ǰ��n���ı�ʯ�����ֵvi��

## �����������

### ���� #1 
> 5 3  
> 1 3 2 5 6  
> 1 3  
> 2 4  
> 1 6  
### ��� #1
> 3  
> 1  
## ˵��/��ʾ
����50%�����ݣ�û��c=2�������

����100%�����ݣ�m<=100000��c=2�����������10000��q<=30000

## ˼·

ʹ�����ݽ������ƽ���SBT����
* ���ڲ�����������½�����SBT����
* ���ڲ�ѯ����������Ϊn����n - 1��Ԫ�ش��������ú���``` int rank(Tree tree, int n) ```��ѯtree����n����������Ľ�� ��
	��ô```rank(n - 1)```���ǲ�ѯ�Ĵ𰸡�
	rank������ʵ�֣�����SBT����ÿ������¼���Ըý��Ϊ�������Ľ������(size)���Ӹ����tree��ʼ�ݹ飺
	��`tree����������size`Ϊ`rightSize`
	* ��n == rightSize����������n������tree����ôtree���ǲ�ѯ�Ľ�㡣
	* ��n < rightSize����ݹ�```rank(tree->right, n)```
	* ��n > rightSize����ݹ�```rank(tree->left, n - rightSize - 1)```

## ����

### C

```c
#include "stdio.h"
#include "stdlib.h"

typedef struct TNode {
	int key;
	size_t size;
	struct TNode * left;
	struct TNode * right;
} *Tree;

#define SIZE(tree) (tree ? tree->size : 0)

Tree newTNode(int key) {
	Tree tree = (Tree)malloc(sizeof(struct TNode));
	tree->key = key;
	tree->size = 1;
	tree->left = tree->right = NULL;
	return tree;
}

Tree leftRotate(Tree tree);
Tree rightRotate(Tree tree);

Tree maintain(Tree tree);
Tree maintainLeft(Tree tree);
Tree maintainRight(Tree tree);

Tree insert(Tree tree, int key);
int rank(Tree tree, int n);

void deleteTree(Tree tree);

Tree leftRotate(Tree tree) {
	Tree k = tree->right;
	tree->right = k->left;
	k->left = tree;
	tree->size = SIZE(tree->left) + SIZE(tree->right) + 1;
	k->size = tree->size + SIZE(k->right) + 1;
	return k;
}

Tree rightRotate(Tree tree) {
	Tree k = tree->left;
	tree->left = k -> right;
	k->right = tree;
	tree->size = SIZE(tree->left) + SIZE(tree->right) + 1;
	k->size = SIZE(k->left) + tree->size + 1;
	return k;
}

Tree maintain(Tree tree) {
	tree = maintainLeft(tree);
	tree = maintainRight(tree);
	return tree;
}

Tree maintainLeft(Tree tree) {
	if (tree == NULL) return tree;
	if (tree->left == NULL) return tree;
	if (tree->left->left && tree->left->left->size > SIZE(tree->right)) {
		tree = rightRotate(tree);
		tree->right = maintain(tree->right);
		tree = maintain(tree);
	}
	if (tree->left->right && tree->left->right->size > SIZE(tree->right)) {
		tree->left = leftRotate(tree->left);
		tree = rightRotate(tree);
		tree->left = maintain(tree->left);
		tree->right = maintain(tree->right);
		tree = maintain(tree);
	}
	return tree;
}

Tree maintainRight(Tree tree) {
	if (tree == NULL) return tree;
	if (tree->right == NULL) return tree;
	if (tree->right->right && tree->right->right->size > SIZE(tree->left)) {
		tree = leftRotate(tree);
		tree->left = maintain(tree->left);
		tree = maintain(tree);
	}
	if (tree->right->left && tree->right->left->size > SIZE(tree->left)) {
		tree->right = rightRotate(tree->right);
		tree = leftRotate(tree);
		tree->left = maintain(tree->left);
		tree->right = maintain(tree->right);
		tree = maintain(tree);
	}
	return tree;
}

Tree insert(Tree tree, int key) {
	if (tree == NULL) {
		return newTNode(key);
	}
	tree->size++;
	if (key < tree->key) {
		tree->left = insert(tree->left, key);
		tree = maintainLeft(tree);
	}
	else {
		tree->right = insert(tree->right, key);
		tree = maintainRight(tree);
	}	
	return tree;
}

int rank(Tree tree, int n) {
	int right_size = SIZE(tree->right);
	if (n == right_size) {
		return tree->key;
	}
	else if (n < right_size) {
		return rank(tree->right, n);
	}
	else {
		return rank(tree->left, n - right_size - 1);
	}
}

void deleteTree(Tree tree) {
	if (tree == NULL) return;
	if (tree->left) deleteTree(tree->left);
	if (tree->right) deleteTree(tree->right);
	free(tree);
}

int main() {
	Tree tree = NULL;
	int m, q;
	scanf("%d %d", &m, &q);
	int c, n;
	for (int i = 0; i < m; i++) {
		scanf("%d", &n);
		tree = insert(tree, n);
	}	
	for (int i = 0; i < q; i++) {
		scanf("%d %d", &c, &n);
		if (c == 1) {
			printf("%d\n", rank(tree, n - 1));
		}
		else {
			tree = insert(tree, n);			
		}
	}
	deleteTree(tree);
	return 0;
}
```