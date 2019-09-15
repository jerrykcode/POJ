# P1428 С��ȿɰ�
[ԭ���ַ](https://www.luogu.org/problem/P1428)

## ��Ŀ����

�˱��ˣ������ˣ�����㣬�����㡣С������μ���һ�����ȿɰ����������ȵ���ÿֻ��Ŀɰ��̶ȡ��������㱻�������ų�һ�ţ�ͷ��������ߣ�Ȼ��ÿֻ���õ�һ��������ֵ����ʾ��ֻ��Ŀɰ��̶ȣ�����Ȼ����Խ�󣬱�ʾ��ֻ��Խ�ɰ�������������ֻ��Ŀɰ��̶�**����һ��**���������е���ͷ��������ߣ�����ÿֻ��ֻ�ܿ���������ߵ���Ŀɰ��̶ȣ��������ﶼ�ڼ��㣬���Լ���������Χ���ж���ֻ�㲻���Լ��ɰ��ء��������Щ�ɰ��������Բ����õ�С���Ǽ���һ�¡�

## �����ʽ

��һ������һ������n����ʾ�����Ŀ��

�ڶ���������n���������ÿո��������α�ʾ������ÿֻС��Ŀɰ��̶ȡ�

## �����ʽ

�������n���������ÿո��������α�ʾÿֻС�������ж���ֻ�㲻���Լ��ɰ���

## �����������

**���� #1**

> 6  
> 4 3 0 5 1 2

**��� #1**

> 0 0 0 3 1 2


## ˵��/��ʾ

n<=100

## ˼·

��ÿ�������������У�ͬʱ�����Ѳ����������ж�������С�ڸ�������

#### �򵥵�Ƕ��ѭ�����ɽ��������������С�������

### ��״����
����������a��size�㹻�󣬳�ʼ��Ϊ0�����ڲ����ÿ������val��a[val]++����ô����a����״����c��ÿ�β�������valʱ����ͨ����״����c����ԭ����a[0]~a[val - 1]֮�ͣ����ڲ���val֮ǰ������С��val������������Ȼ�󵥵������״���鼴�ɡ�
�����ڲ��������û���޶���Χ����ô��״����ĳߴ���Ҫ�ǳ�������������Ҫ��ɢ�����ݣ����������ݵ�����ԶС�����ݵķ�Χ�����Ը��������¸�ֵ��������䣬�����`1, 100, 1000, 10000000`�Ͳ���`1, 2, 3, 4`�Ա�����û��Ӱ�졣

```c
struct node {
	int val;
	int input_rank;
};

```
ʹ�ô˽ṹ������飬��¼ÿ�������������������Ĵ��򡣶���������valС������ǰ�棬val��ͬ��input_rank��ģ���`������`������ǰ�档Ȼ���������ÿ������"���µ�ֵ"��������ǰ��ĸ�ֵΪ1��֮��Ϊ2...

֮���ٴα�������������������ǵ�"��ֵ"ͨ����״������м��㡣

(ע������ʱval��ͬ����������ǰ�棬����������ʱ������ͬ����Ϊ���������Ҫ�����`С�ڵ���`val�������������Ӷ��������val����������������������Ҫ����`С��`val��������������)



### SBT��

����һ��С�������������ʹ��SBT����һ��ͨ���������ά��ƽ���ƽ������

���������:
```c
typedef struct TNode {
	int key;
	size_t size;
	struct TNode *left, *right;
} *SBT;

```
���У�keyΪ���������������������Ҳ����key����sizeΪ�����ӽ��(�����Լ�)��������

����ÿ������������SBTƽ�������ɣ�������������key >= tree->key����ݹ��������������tree->left�����н��С��key�����key > tree->key����ôС��key������������Ҫ��1��

������key�Ĺ����м����������С��key������������

## ����

### ��״����

```c
#include "stdio.h"
#include "stdlib.h"

int * c, n;

int lowbit(int x) {
	return x & -x;
}

void add(int x, int k) {
	for (; x <= n; x += lowbit(x)) {
		c[x] += k;
	}
}

int sum(int x) {
	int result = 0;
	for (; x > 0; x -= lowbit(x)) {
		result += c[x];
	}
	return result;
}

struct node {
	int val;
	int input_rank;
};

int compare(const void * a, const void * b) {
	return ((struct node *)a)->val != ((struct node *)b)->val ? ((struct node *)a)->val - ((struct node *)b)->val : 
		((struct node *)b)->input_rank - ((struct node *)a)->input_rank;
}

int main() {
	scanf("%d", &n);
	struct node * node_array = (struct node *)malloc(n * sizeof(struct node));
	int i = 0, val;
	for (; i < n; i++) {
		scanf("%d", &val);
		node_array[i].val = val;
		node_array[i].input_rank = i;
	}
	qsort(node_array, n, sizeof(struct node), compare);
	int * rank = (int *)malloc(n * sizeof(int));
	for (i = 0; i < n; i++) {
		rank[node_array[i].input_rank] = i + 1;
	}
	free(node_array);	
	c = (int *)malloc((n + 1) * sizeof(int));
	for (i = 1; i < n + 1; i++) c[i] = 0;
	for (i = 0; i < n; i++) {	
		if (i != 0) putchar(' ');
		printf("%d", sum(rank[i] - 1));
		add(rank[i], 1);
	}
	free(rank);
	free(c);
	return 0;
}
```

### SBT��

```c
#include "stdio.h"
#include "stdlib.h"

typedef struct TNode {
	int key;
	size_t size;
	struct TNode *left, *right;
} *SBT;

#define SIZE(tree) ((tree) ? (tree->size) : 0)

SBT newTNode(int key);
SBT leftRotate(SBT tree);
SBT rightRotate(SBT tree);
SBT maintain(SBT tree);
SBT maintainLeft(SBT tree);
SBT maintainRight(SBT tree);
SBT insert(SBT tree, int key);
void deleteTree(SBT tree);

SBT tree = NULL;
size_t smaller_num;

int main() {
	int n, key;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &key);
		smaller_num = 0;
		tree = insert(tree, key);
		if (i != 0) putchar(' ');
		printf("%d", smaller_num);
	}
	deleteTree(tree);
	return 0;
}

SBT newTNode(int key) {
	SBT tree = (SBT)malloc(sizeof(struct TNode));
	tree->key = key;
	tree->size = 1;
	tree->left = tree->right = NULL;
	return tree;
}

SBT leftRotate(SBT tree) {
	if (!tree || !tree->right) return tree;
	SBT k = tree->right;
	tree->right = k->left;
	k->left = tree;
	tree->size = SIZE(tree->left) + SIZE(tree->right) + 1;
	k->size = tree->size + SIZE(k->right) + 1;
	return k;
}

SBT rightRotate(SBT tree) {
	if (!tree || !tree->left) return tree;
	SBT k = tree->left;
	tree->left = k->right;
	k->right = tree;
	tree->size = SIZE(tree->left) + SIZE(tree->right) + 1;
	k->size = SIZE(k->left) + tree->size + 1;
	return k;
}

SBT maintain(SBT tree) {
	tree = maintainLeft(tree);
	return maintainRight(tree);
}

SBT maintainLeft(SBT tree) {
	if (!tree) return tree;
	if (!tree->left) return tree;
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

SBT maintainRight(SBT tree) {
	if (!tree) return tree;
	if (!tree->right) return tree;
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

SBT insert(SBT tree, int key) {
	if (tree == NULL) {
		return newTNode(key);
	}
	tree->size++;
	if (key < tree->key) {
		tree->left = insert(tree->left, key);
		tree = maintainLeft(tree);
	}
	else { //key >= tree->key
		smaller_num += SIZE(tree->left);
		if (key > tree->key) smaller_num++;
		tree->right = insert(tree->right, key);
		tree = maintainRight(tree);
	}
	return tree;
}

void deleteTree(SBT tree) {
	if (!tree) return;
	if (tree->left) deleteTree(tree->left);
	if (tree->right) deleteTree(tree->right);
	free(tree);
}
```

> Written with [StackEdit](https://stackedit.ioaa/).
