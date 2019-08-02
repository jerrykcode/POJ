# P2161 [SHOI2009]�᳡ԤԼ
[ԭ���ַ](https://www.luogu.org/problem/P2161)

## ��Ŀ����

PP������һ��յ����ã�����Ϊ��ҵ���ߵ�λ�ṩ���鳡�ء���Щ�����еĴ��������Ҫ���������ʱ�䣨����Ŀ���ֻ��Ҫһ�죩����������ֻ��һ�������Բ�ͬ�Ļ����ʱ������
���ܹ���ͻ��Ҳ����˵��ǰһ������Ľ������ڱ����ں�һ������Ŀ�ʼ����֮ǰ�����ԣ����Ҫ����һ���µĳ���ԤԼ���룬�ͱ���ܾ���������������ͻ��ԤԼ�� һ����˵����
��PP���÷��������Ѿ�������һ���᳡ԤԼ�������10�յ�15�գ��Ͳ����ڽ�����֮���ͻ��ԤԼ�������12�յ�17�ա���������ʱ���ھ������棬PP���÷�����ʱ��Ϊ�˽���һ��
�µĻ᳡ԤԼ�����ܾ���һ����������֮ǰԤ����ԤԼ�� ���ǣ����ù���ԱQQ�ıʼǱ��ϱʼǱ��Ͼ�����¼����������Ϣ�� ������Ϊ������������е����ڶ���һ��������ʾ�����磬
���һ��Ϊ��10��Ļ����"90��"��ʼ��"99��"����ô��һ����������ֻ����"100��"��ʼ�� ��������ҵ��Ĺ��������վ��������õĹ���ԱQQϣ���μ�SHTSC�����������һ��
�����ϵͳ���������Ĺ��������ϵͳӦ����ִ���������������� A��������һ���µ�ԤԼ�Ǵ�"start��"��"end��"�����Ҿܾ��������������ͻ��ԤԼ��ִ�����������ʱ�����ϵ
ͳӦ������Ϊ�������ԤԼ���ܾ�����ԤԼ�������Է���QQ���Լ��ļ�¼��У�ԡ� B�����������ϵͳ���ص�ǰ����Ȼ��Ч��ԤԼ��������

## �����ʽ

�����ļ��ĵ�һ����һ������n����ʾ���ϵͳ�����ܵĲ��������� 
����ȥn��ÿ�б�ʾһ��������ÿһ�еĸ�ʽΪ��������֮һ�� 

* "A start end"��ʾһ��A������ 
* "B"��ʾһ��B������

## �����ʽ

����ļ���n�У�ÿ��һ�ζ�Ӧһ�����롣��ʾ���ϵͳ���ڸò����ķ���ֵ��

## �����������

### ���� #1

> 6  
> A 10 15  
> A 17 19  
> A 12 17  
> A 90 99  
> A 11 12  
> B  

## ��� #1

> 0  
> 0  
> 2  
> 0  
> 1  
> 2  

### ˵��/��ʾ

N< = 200000

1< = Start End < = 100000

## ˼·

### ����������

�����洢start��end����ʾһ��ԤԼ
```c
typedef struct TNode {
	int start, end;
	struct TNode * left;
	struct TNode * right;
} * Tree;
```

��ÿ������㣺

* start < end
* �����������н���start��end��С��start
* �����������н���start��end������end

�������еĽ���(start, end)���������ص����֣��������ڳ�ͻ��ԤԼ

### A����

��������:
```c
Tree insert(Tree tree, int start, int end);
```
��tree�в���һ�����(start, end)���������н������ص�����ɾ�����н�㡣���ز���������

�Զ���������������΢���ļ��ɣ�

* ��treeΪNULL���½���㲢����
* ��end < tree->start���ݹ����������
* ��start > tree->end, �ݹ����������
* ����������(start, end)��(tree->start, tree->end)���ص���`(tree->start, tree->end)��ʾ��ԤԼ���ܾ�`��ע���ʱ`tree�������п���Ҳ������(start, end)�ص��Ľ��`������
	* `start < tree->start`�������������н���start��end��С��tree->start������start < tree->start��
	��tree���������п��ܴ��ڽ��subtree��ʹsubtree->end > start����subtree->end < tree->start < end����`start < subtree->end < end`����subtree��(start, end)�ص���
	����```tree->left = leftOverlap(tree->left, start);```����tree���������е��ص���`leftOverlap`���������ġ�
	*  `end > tree->end`�������������н���start��end������tree->end������end > tree->end��
	��tree���������п��ܴ��ڽ��subtree��ʹsubtree->start < end����subtree->start > tree->end > start����`start < subtree->start < end`����subtree��(start, end)�ص���
	����```tree->right = rightOverlap(tree->right, end);```����tree���������е��ص���`rightOverlap`���������ġ�
  
  ���������������ͬʱ������`���ʹ��(start, end)�滻(tree->start, tree->end)������������ԤԼͬʱ�ܾ����г�ͻ��ԤԼ`

* leftOverlap����
```c
Tree leftOverlap(Tree tree, int start);
```
��tree�����н��subtree����subtree->end > start����ɾ���˽�㣬���ܾ��˳�ͻ��ԤԼ�����ظ��º����

* ��treeΪNULL�������ڳ�ͻ��ԤԼ������ NULL
* ��tree->end < start����tree���洢��ԤԼ����ͻ����tree�������������н��Ҳһ������ͻ���ݹ���������
* ��tree->end >= start����tree���洢��ԤԼ��ͻ����tree�������������н��Ҳһ����ͻ��ɾ�������������н�㣬��left�洢tree����������Ȼ��ɾ��tree��㱾��
   ��leftȡ��tree����ʱ��Ҫ�ݹ�left����Ϊleft�п��ܻ����ڳ�ͻ�Ľ�㡣

* rightOverlap����

��leftOverlap�Գơ�

#### ������ʹ��ȫ�ֱ���tree_size��ʾ���Ľ������removed_node_num��ʾ������ɾ���ĳ�ͻ�������
#### main�н�tree_size��ʼ��Ϊ0��ÿ��A�����а�removed_node_num��ʼ��Ϊ0��Ȼ�����insert������
#### �½����ʱ tree_size++��ɾ�����ʱtree_size--��removed_node_num++���滻���ʱremoved_node_num++(�滻�����Ľ�������䣬�����滻�Ľ��Ҫ�������ܾ��Ľ��)
#### A����������removed_node_num��

### B����  ���tree_size����

## ���� 

### C

```c
#include "stdio.h"
#include "stdlib.h"

int tree_size;
int removed_node_num;

typedef struct TNode {
	int start, end;
	struct TNode * left;
	struct TNode * right;
} * Tree;

Tree newTNode(int start, int end) {
	Tree t = (Tree)malloc(sizeof(struct TNode));
	t->start = start;
	t->end = end;
	t->left = t->right = NULL;
	return t;
}

Tree insert(Tree tree, int start, int end);
Tree leftOverlap(Tree tree, int start);
Tree rightOverlap(Tree tree, int end);
void deleteTree(Tree tree);

Tree insert(Tree tree, int start, int end) {
	if (tree == NULL) {
		tree_size++;	
		return newTNode(start, end);
	}
	if (end < tree->start) {
		tree->left = insert(tree->left, start, end);
	}
	else if (start > tree->end) {
		tree->right = insert(tree->right, start, end);
	}
	else {
		if (start < tree->start) {
			tree->left = leftOverlap(tree->left, start);
		}
		if (end > tree->end) {
			tree->right = rightOverlap(tree->right, end);
		}
		tree->start = start;
		tree->end = end;
		removed_node_num++;
	}
	return tree;
}

Tree leftOverlap(Tree tree, int start) {
	if (tree == NULL) return NULL;
	if (tree->end < start) {
		tree->right = leftOverlap(tree->right, start);
		return tree;
	}
	else {
		deleteTree(tree->right);
		tree->right = NULL;
		Tree left = tree->left;
		free(tree);
		removed_node_num++;
		tree_size--;
		return leftOverlap(left, start);
	}
}

Tree rightOverlap(Tree tree, int end) {
	if (tree == NULL) return NULL;
	if (tree->start > end) {
		tree->left = rightOverlap(tree->left, end);
		return tree;
	}
	else {
		deleteTree(tree->left);
		tree->left = NULL;
		Tree right = tree->right;
		free(tree);
		removed_node_num++;
		tree_size--;
		return rightOverlap(right, end);
	}
}

void deleteTree(Tree tree) {
	if (tree == NULL) return;
	if (tree->left) deleteTree(tree->left);
	if (tree->right) deleteTree(tree->right);
	free(tree);
	removed_node_num++;
	tree_size--;
}

int main() {
	Tree tree = NULL;
	tree_size = 0;
	int n ,start, end;
	scanf("%d", &n);
	char cmd;	
	for (int i = 0; i < n; i++) {
		scanf(" %c", &cmd);
		if (cmd == 'A') {
			scanf("%d %d", &start, &end);
			removed_node_num = 0;
			tree = insert(tree, start, end);
			printf("%d\n", removed_node_num);
		}
		else {
			printf("%d\n", tree_size);
		}
	}
	deleteTree(tree);
	return 0;
}
```