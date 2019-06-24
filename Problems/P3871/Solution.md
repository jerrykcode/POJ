# P3871 [TJOI2010]��λ��

[ԭ���ַ](https://www.luogu.org/problemnew/show/P3871)

## ��Ŀ����

����һ����N��Ԫ����ɵ��������У����������ֲ�����

1 add a

�ڸ����е�������һ������a����ɳ���ΪN + 1����������

2 mid �����ǰ���е���λ��

��λ����ָ��һ�����а��մ�С������������м�λ�õ������������г���Ϊż������ָ�����м�λ�õ��������н�С���Ǹ���

��1��1 2 13 14 15 16 ��λ��Ϊ13

��2��1 3 5 7 10 11 17 ��λ��Ϊ7

��3��1 1 1 2 3 ��λ��Ϊ1

## ���������ʽ

### �����ʽ��
��һ��Ϊ��ʼ���г���N���ڶ���ΪN����������ʾ�������У�����֮���ÿո�ָ���������Ϊ������M����Ҫ����M�β���������ΪM�У�ÿ�������ʽ������������

### �����ʽ��
����ÿ��mid���������λ����ֵ

## �����������

### ��������#1�� 

> 6  
> 1 2 13 14 15 16  
> 5  
> add 5  
> add 3  
> mid  
> add 20  
> mid

### �������#1�� 

> 5  
> 13

## ˵��

����30%�����ݣ�1 �� N �� 10,000��0 �� M �� 1,000

����100%�����ݣ�1 �� N �� 100,000��0 �� M �� 10,000

�����������ľ���ֵ������1,000,000,000�������е����������ظ�

ÿ�����Ե�ʱ��1��

## ˼·

SBT��

���ʼ�����n�����ּ�֮��add�����ֶ�����SBT�С�����mid����SBT�е���������Ϊsize����sizeΪ����������size/2����С�ڵ�����λ������sizeΪż����
����size/2 - 1����С�ڵ�����λ������mid��Ҫһ������``` rank(SBT tree, size_t size) ```�����ڷ���SBT�е�һ��������SBT����size����С�ڵ�������

����SBT������������

* ����

* ����һ��������size����С�ڵ��������Ӹ���㿪ʼ��
	* ����������size���õ���size��������洢����������
	* ����������size����size����ݹ飬��ʱ������������size����С�ڵ�������
	* ����������sizeС��size����ݹ飬����������Ѱ�������������������Ľ���Ѿ����ڵ���������������㣬���Դ�ʱ������������(size - ��������size - 1)����С�ڵ�����


## ����

```cpp
#include <cstdio>
#include <cstdlib>
using namespace std;

template<typename T>
class MidNum {
public:
	MidNum();
	~MidNum();

	void add(T num);
	T mid();

private:

	typedef struct SBTNode {
		T num;
		struct SBTNode * left;
		struct SBTNode * right;
		size_t size;
		SBTNode(T num) : num(num), left(NULL), right(NULL), size(1) {}
	} * SBT;

	SBT left_rotate(SBT tree);
	SBT right_rotate(SBT tree);

	SBT maintain(SBT tree);
	SBT insert(SBT tree, T num);
	T rank(SBT tree, size_t size);
	
	void delete_tree(SBT tree);

private:
	SBT tree;
};

template<typename T>
MidNum<T>::MidNum() {
	tree = NULL;
}

template<typename T>
MidNum<T>::~MidNum() {
	delete_tree(tree);
}

template<typename T>
void MidNum<T>::add(T num) {
	tree = insert(tree, num);
}

template<typename T>
T MidNum<T>::mid() {
	size_t n = tree->size / 2;
	if (tree->size % 2) { //sizeΪ����
		return rank(tree, n); //n��������λ��С
	}
	else { //sizeΪż��
		return rank(tree, n - 1); //n - 1��������λ��С
	}
}

template<typename T>
typename MidNum<T>::SBT MidNum<T>::left_rotate(SBT tree) {
	SBT k = tree->right;
	tree->right = k->left;
	k->left = tree;
	k->size = tree->size;
	size_t left_size = tree->left ? tree->left->size : 0; //�������п���ΪNULL
	size_t right_size = tree->right ? tree->right->size : 0; //�������п���ΪNULL
	tree->size = left_size + right_size + 1;
	return k;
}

template<typename T>
typename MidNum<T>::SBT MidNum<T>::right_rotate(SBT tree) {
	SBT k = tree->left;
	tree->left = k->right;
	k->right = tree;
	k->size = tree->size;
	size_t left_size = tree->left ? tree->left->size : 0; //�������п���ΪNULL
	size_t right_size = tree->right ? tree->right->size : 0; //�������п���ΪNULL
	tree->size = left_size + right_size + 1;
	return k;
}

template<typename T>
typename MidNum<T>::SBT MidNum<T>::maintain(SBT tree) {
	if (tree == NULL) return NULL;
	SBT left = tree->left, right = tree->right;
	size_t left_size = left ? left->size : 0;
	size_t right_size = right ? right->size : 0;
	if (left && left->left && left->left->size > right_size) { //������������������������
		tree = right_rotate(tree);
		tree->right = maintain(tree->right);
		tree = maintain(tree);
	}
	else if (left && left->right && left->right->size > right_size) { //������������������������
		tree->left = left_rotate(tree->left);
		tree = right_rotate(tree);
		tree->left = maintain(tree->left);
		tree->right = maintain(tree->right);
		tree = maintain(tree);
	}
	else if (right && right->right && right->right->size > left_size) { //������������������������
		tree = left_rotate(tree);
		tree->left = maintain(tree->left);
		tree = maintain(tree);
	}
	else if (right && right->left && right->left->size > left_size) { //������������������������
		tree->right = right_rotate(tree->right);
		tree = left_rotate(tree);
		tree->left = maintain(tree->left);
		tree->right = maintain(tree->right);
		tree = maintain(tree);
	}
	return tree;
}

template<typename T>
typename MidNum<T>::SBT MidNum<T>::insert(SBT tree, T num) {
	if (tree == NULL) return new SBTNode(num);
	tree->size++;
	if (num < tree->num) {
		tree->left = insert(tree->left, num);
	}
	else {
		tree->right = insert(tree->right, num);
	}
	tree = maintain(tree); //ά��ƽ��
	return tree;
}

template<typename T>
T MidNum<T>::rank(SBT tree, size_t size) {
	if (tree == NULL) return 0;
	size_t left_size = tree->left ? tree->left->size : 0;
	if (left_size == size) {
		return tree->num;
	}
	else if (left_size > size) {
		return rank(tree->left, size);
	}
	else {		
		return rank(tree->right, size - left_size - 1);
	}
}

template<typename T>
void MidNum<T>::delete_tree(SBT tree) {
	if (tree == NULL) return;
	delete_tree(tree->left);
	delete_tree(tree->right);
	delete tree;
}

int main() {
	int n, m, num;
	scanf("%d", &n);
	MidNum<int> mid_num;
	size_t i;
	for (i = 0; i < n; i++) {
		scanf("%d", &num);
		mid_num.add(num);
	}
	scanf("%d", &m);
	char cmd[3];
	for (i = 0; i < m; i++) {
		scanf("%s", cmd);
		if (cmd[0] == 'a') {
			scanf("%d", &num);
			mid_num.add(num);
		}
		else {
			printf("%d\n", mid_num.mid());
		}
	}
	return 0;
}
```