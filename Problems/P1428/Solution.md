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

#### ֮ǰSBT��������ȻAC������ʵ����bug�ģ�
>����һ��С�������������ʹ��SBT����һ��ͨ���������ά��ƽ���ƽ������
>
>���������:
>```c
>typedef struct TNode {
>	int key;
>	size_t size;
>	struct TNode *left, *right;
>} *SBT;
>
>```
>���У�keyΪ���������������������Ҳ����key����sizeΪ�����ӽ��(�����Լ�)��������
>
>����ÿ������������SBTƽ�������ɣ�������������key >= tree->key����ݹ��������������tree->left�����н��С��key�����key > tree->key����ôС��key������������Ҫ��1��
>
>������key�Ĺ����м����������С��key������������

�ڲ�����ͬ��ʱ������bug������һ������(input1)
10
1 1 1 1 1 1 1 1 1 1
��ȷӦ���ȫ0����֮ǰ��SBT������� 0 0 0 1 1 2 3 4 4 5

#### BUG
���������������������<��<�ұߣ�����key == t->keyʱ��keyӦ�õݹ���������������������أ�֮ǰ�Ĵ����ǲ���������������ô���ǲ���10��1����������������γ�һ����������ά��ƽ������������������н���������������н���Լ�������keyȫ����1����ʱ�����Ѿ����Ƕ����������ˣ�����

#### ����
�����ظ����������һ����ȷ��������`����ͬ������ͬһ������¼`��  
��ô��Ȼ�������Ҫ����һ��`key_num`����������¼key�����˶��ٴΣ�������ͬ��keyʱ��key_num++���ɡ�  
`size`���Ա�Ϊ`node_size`����ʾ���ж��ٽ�㣬����ά��ƽ�⣬  
ע���ʱһ�������ܴ������������Ի�Ҫ��`num_size`���Լ�¼���в����˶��ٸ�������������м����ж��ٸ���С�ڴ������������ǻ���`num_size`���Եġ�
```c
typedef struct TNode {
	int key;
	size_t key_num;
	size_t num_size;
	size_t node_size;
	struct TNode *left, *right;
} *Tree;
```



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

�����Ǹ�����Ĵ���SBT/P1428.c��֮ǰ�Ĵ��������SBT/P1428_bug.c��

```c
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
```

> Written with [StackEdit](https://stackedit.ioaa/).
