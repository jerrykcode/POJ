# P1908 �����
[ԭ���ַ](https://www.luogu.org/problem/P1908)  
## ��Ŀ����
èèTOM��С����JERRY����ֽ������ˣ����ǱϾ����ǳ����ˣ������Ѿ���ϲ������������׷�Ҹϵ���Ϸ����������ϲ����ͳ�ơ������TOM��è���ĵ�һ�������֮Ϊ������ԡ��Ķ������ⶫ������������ģ����ڸ�����һ�����������У�����Ծ���������ai>aj��i<j������ԡ�֪�����������Ǿͱ���˭�����������һ������������������Ե���Ŀ��
Update:�����Ѽ�ǿ��  
## �����ʽ
��һ�У�һ����n����ʾ��������n������  
�ڶ���n��������ʾ���������С�������ÿ�����ֲ�����10^9  
## �����ʽ
��������������Ե���Ŀ��  
## �����������
### ���� #1
>6  
5 4 2 6 3 1  

### ��� #1
>11  

### ˵��/��ʾ
����25%�����ݣ�n <= 2500  
����50%�����ݣ�n <= 4 \* 10^4  
�����������ݣ�n <= 5 \* 10^5  
��ʹ�ýϿ���������  
Ӧ�ò���n����50��� by chen_zhe  
## ˼·
�������  
����ÿ����ʱ������������Ĵ�������������������������ԡ�  
����ֻҪ������ÿ����ʱ��������������������ж����������������������������Եĸ�����  
�����ж��ֽⷨ  
### ��״����
1)��ɢ��  
����������int��Χ�ģ���ɢ������С�����ݱ���Ϊ1����θ�Ϊ2��������ݱ���Ϊn�������ݷ�Χ����С��[1, n]�����Ⲣ��Ӱ��������ԵĽ������rank[i]��ʾ��i����������ݴ�С���������(��1��ʼ)����`rank[i]�ǵ�i��������ɢ�������ֵ`��  
��ɢ��ͨ����������������ʵ�֡���������롣  
2)��״����  
��һ������Ϊn + 1�����飬��Ϊarr��ÿ��Ԫ�س�ʼ��Ϊ0��֮�󣬶���ÿ����ɢ�������������rank[i]����arr[rank[i]]����Ϊ1����ô�ڸ���֮ǰ��arr[1]��arr[rank[i] - 1]֮�;���������������С�ڵ���rank[i]�����ݵĸ�������ô��`i`(����ʱ����������оݸ���)����ȥ��������͵õ���������������д���rank[i]�����ݵĸ�����  
����һ�����������α�֤arr[1]��arr[rank[i] - 1]֮����������������`С�ڵ���`rank[i]�����ݵĸ���������`С��`��  
������֮ǰ��ɢ������ʱ��������ͬ�����ݣ�`�������Ҫ����ǰ��`��������ɢ��������������ݸĳɵ������ݻ�С�ں�����ģ�����������ĵ�i�͵�j��������ͬ(i < j)����ôrank[i] < rank[j]����ô�ȸ���arr[rank[i]]Ϊ1��֮�����arr[rank[j]]ʱ����;ͻ��arr[rank[i]]�����1�����ȥ��Ҳ����˵`С�ڵ���`��j�����ݵ����ݶ��������ˡ�  
OK  
����������˵����״������  
��״�����������:  
* �������
* �������  

����ֻ��Ҫά��arr��`��״����`bit�Ϳ�������  
����rank[i]��ͨ��bit����arr������[1, rank[i] - 1]����֮�ͣ���i��ȥ����ͣ��ټӵ���������Ե������ϡ�Ȼ����ͨ��bit����arr[rank[i]]Ϊ1�Ϳ����ˡ����в������ǻ�����״����bit�ģ�arr����ֻ��Ϊ����⣬�����в������������֡�  
### ����(��״����)

```c
#include "stdio.h"
#include "stdlib.h"

int lowbit(int x) {
	return x & -x;
}

void update(int * bit, int len, int idx, int val) {
	for (; idx < len; idx += lowbit(idx)) {
		bit[idx] += val;
	}
}

int sum(int * bit, int idx) {
	int result = 0;
	for (; idx > 0; idx -= lowbit(idx)) {
		result += bit[idx];
	}
	return result;
}

//������ɢ��
struct node {
	int val; //ֵ
	int input_rank; //�������
};

//������ɢ������
int compare(const void * a, const void * b) {
	//��val��ͬ����valС������ǰ��
	//����input_rankС�ģ���������ģ�����ǰ��
	return ((struct node *)a)->val != ((struct node *)b)->val ? ((struct node *)a)->val - ((struct node *)b)->val :
		((struct node *)a)->input_rank - ((struct node *)b)->input_rank;
}

int main() {
	int n;
	scanf("%d", &n);
	struct node * node_array = (struct node *)malloc(n * sizeof(struct node));
	for (int i = 0; i < n; i++) {
		scanf("%d", &node_array[i].val); //��������ֵ
		node_array[i].input_rank = i; //��¼�������
	}
	qsort(node_array, n, sizeof(struct node), compare); //����
	int * rank = (int *)malloc(n * sizeof(int)); 
	for (int i = 0; i < n; i++) {
		//���������е�iС������ֵΪnode_array[i].val
		//���ǵ�node_array[i].input_rank�����������
		//��ɢ�������ֵΪi + 1
		//+1����Ϊ��ֵ��1��ʼ�ۼ�
		rank[node_array[i].input_rank] = i + 1; 
	}
	free(node_array);
	int len = n + 1;
	int * bit = (int *)malloc(len * sizeof(int)); //��״����
	for (int i = 1; i < len; i++) bit[i] = 0; //��ʼ��
	long long result = 0; //���������
	for (int i = 0; i < n; i++) {
		result += (i - sum(bit, rank[i] - 1));
		update(bit, len, rank[i], 1);
	}
	printf("%lld", result);
	free(rank);
	free(bit);
	return 0;
}
```  
### SBT��  
SBT��ͨ���������ά��ƽ�⡣  
����SBT����¼��ÿ������size��size��`�ý�㱾�����������������`��  
��ô��ÿ�����������ֻ�轫�����SBT�С������в������������ͬ����ôÿ���������������ݹ����ʱ��������������������н������ڴ�������������������size+1�����ڴ����������ȵ�������������ʱ�����Ѿ��������������������������ˡ�  
����������ܴ�����ͬ����������Ľ�������ǰ�`��ͬ������ͬһ����������`�����������������Ҫʹ��`key_num`���Լ�¼key���ֹ����Σ�����ʱ`n�������������������ܴ���n��`����������㻹��Ҫ����һ��`num_size`���ԣ�������¼����㱾�������ӽ��`ʵ�ʴ����˶��ٸ���`������ͨSBT���е�`size`�����������Ϊ`node_size`���ԣ�����ʾ�ý�㱾�������������������ƽ������������ά��ƽ�⡣
����㶨������  
```c
typedef struct TNode {
	int key;
	size_t key_num, num_size, node_size;
	struct TNode *left, *right;
} *Tree;
```
������ת��ά��ƽ����㷨����ͨSBT���ƣ�ֻ����ת��ע�����`key_num`��`num_size`��`node_size`�������Ե�ֵ��ά��ƽ��ʱͨ��node_size�ж��Ƿ��ƻ���ƽ�⡣  
����ʱ��Ҫ���������ж��������ڴ���������ע��num_size�Ǵ����������������������롣  

### ����(SBT��)

```c
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
```