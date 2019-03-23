#include "stdio.h"
#include "stdlib.h"
#include "memory.h"

/* ���Գƶ��������Ľ���� */
int max_subtree_nodes = 0;

typedef struct TNode {
	int val;
	struct TNode *left, *right;
} *Tree;

/* �Ƚ����Ŷ������Ƿ���ͬ����ͬ����1�����򷵻�0������ͬ����£���p_nodesָ�봫�������������Ŀ��*/
int cmp_tree(Tree a, Tree b, int *p_nodes) {
	if (a == NULL && b == NULL) {
		*p_nodes = 0;
		return 1;
	}
	if (a == NULL || b == NULL) {
		return 0;
	}
	int left_nodes, right_nodes;
	if (a->val == b->val && cmp_tree(a->left, b->left, &left_nodes) && cmp_tree(a->right, b->right, &right_nodes)) {
		*p_nodes = left_nodes + right_nodes + 1; /*�����������Ŀ+�����������Ŀ+1*/
		return 1;
	}
	return 0;
}

/* ����original_tree���������ݹ齻���������*/
Tree swap_tree(Tree original_tree) {
	if (original_tree == NULL) return NULL;
	Tree tree = (Tree)malloc(sizeof(struct TNode));
	tree->val = original_tree->val;
	tree->left = swap_tree(original_tree->right); /* original_tree�������������󸳸�tree�������� */
	tree->right = swap_tree(original_tree->left); /* original_tree�������������󸳸�tree�������� */
	int nodes;
	if (cmp_tree(tree, original_tree, &nodes)) { 
		/* tree��original_tree��ͬ����tree�Գ� */
		if (nodes > max_subtree_nodes) max_subtree_nodes = nodes;
	}
	return tree;
}

/* �ݹ�ɾ���� */
void delete_tree(Tree tree) {
	if (tree == NULL) return;
	delete_tree(tree->left);
	delete_tree(tree->right);
	free(tree);
}

int main() {
	int n;
	scanf("%d", &n);
	Tree *tree_list = (Tree *)malloc(n * sizeof(Tree));
	for (int i = 0; i < n; i++) {
		tree_list[i] = (Tree)malloc(sizeof(struct TNode));
		scanf("%d", &(tree_list[i]->val));
	}
	int left_idx, right_idx;
	for (int i = 0; i < n; i++) {
		scanf("%d %d", &left_idx, &right_idx);
		tree_list[i]->left = (left_idx != -1 ? tree_list[left_idx - 1] : NULL);
		tree_list[i]->right = (right_idx != -1 ? tree_list[right_idx - 1] : NULL);
	}
	Tree root = tree_list[0];
	free(tree_list);
	Tree tree = swap_tree(root);
	printf("%d", max_subtree_nodes);
	delete_tree(root);
	delete_tree(tree);
	return 0;
}