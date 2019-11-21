# P2574 XOR������
[ԭ���ַ](https://www.luogu.org/problem/P2574)

## ��Ŀ����

AKN���õ�һ��̫ˮ�ˣ���м��д��һ�⣬���������������µ���Ϸ������Ϸ�У������֣������Ϸ���˺�������һ�����ɣ���������

1�� ӵ��һ���˺���Ϊ����Ϊn��01����

2�� ����һ����Χ[l,r]���˺�Ϊ�˺����������Χ����1�ĸ���

3�� �ᱻ����޸��˺����е���ֵ���޸ĵķ����ǰ�[l,r]�е�������xor��1

AKN��֪��һЩʱ�̵��˺�������������������˺�

## �����ʽ

��һ��������n,m,��ʾ����Ϊn��01������m��ʱ��

�ڶ���һ������Ϊn��01����Ϊ��ʼ�˺���

�����п�ʼm�У�ÿ��������p,l,r

��pΪ0�����ʾ��ǰʱ�̸ı�[l,r]���˺������ı��������

��pΪ1�����ʾ��ǰʱ��AKN��֪��[l,r]���˺�

## �����ʽ

����ÿ��ѯ���˺������һ����ֵ�˺���ÿ��ѯ�����һ��

## �����������
### ���� #1
> 10 6  
1011101001  
0 2 4  
1 1 5  
0 3 7  
1 1 10  
0 1 4  
1 2 6


### ��� #1
> 3  
6  
1

### ˵��/��ʾ

�������ͣ�

1011101001

1100101001

ѯ��[1,5]���3

1111010001

ѯ��[1,10]���6

0000010001

ѯ��[2,6]���1

���ݷ�Χ��

10%����2��n,m��10

����30%����2��n,m��2000

100%����2��n,m��2*10^5

By:worcher

## ˼·
���߶���ά�������ƴ���  
һ������¼һ�ζ����ƴ�֮�͡�  
�������˺�����������һ����1�ĸ�������ô���߶�����ͼ��ɡ�  
���ڸ��²�������1 xor ʵ�����ǰ�һ�ζ����ƴ���0��Ϊ1��1��Ϊ0��  
��ô`���º�1�ĸ���֮�;��Ǹ���ǰ0�ĸ���֮��`  
������һ�εĺ͸���Ϊ`��һ�εĳ��ȼ�ȥԭ���ĺͼ���`��  
�����Ϊһ��bool��true��ʾ����������Ҫxor��false��ʾ����Ҫ��  
��ʼʱ���н�������Ǿ�Ϊfalse��  
����ʱ�����xor֮�������Ҫȡ����Ҳ����������ǰ�����Ϊfalse�����º������Ϊtrue��  
������ǰ�����Ϊtrue�����ʾ����ǰ��������Ҫһ��xor����ô���º�������Ҫ�ٴ�xor������xor��������������Ǹ���Ϊfalse��  
����������´���ʱ�������������Ҳ��ȡ������������롣  

## ����

```c
#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"

typedef struct TNode {
	int start, end;
	int sum;
	bool lazy_tag;
	struct TNode *left, *right;
} *SegmentTree;

SegmentTree build(int start, int end, char * binary_str);
void update(int start, int end, SegmentTree st);
int sum(int start, int end, SegmentTree st);
void tagDown(SegmentTree st);
void xor(SegmentTree st);
int len(SegmentTree st);
bool contain(int start, int end, SegmentTree st);
bool cross(int start, int end, SegmentTree st);
void deleteTree(SegmentTree st);

int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	char * binary_str = (char *)malloc(n * sizeof(char)), ch;
	for (int i = 0; i < n; i++) {
		do {
			ch = getchar();
		} while (ch != '0' && ch != '1');
		binary_str[i] = ch;
	}
	SegmentTree st = build(0, n - 1, binary_str);
	free(binary_str);
	int p, l, r;
	for (int i = 0; i < m; i++) {
		scanf("%d %d %d", &p, &l, &r);
		l--; r--;
		if (p) {
			printf("%d\n", sum(l, r, st));
		}
		else {
			update(l, r, st);
		}
	}
	deleteTree(st);
	return 0;
}

SegmentTree build(int start, int end, char * binary_str) {
	if (start > end) return NULL;
	SegmentTree st = (SegmentTree)malloc(sizeof(struct TNode));
	st->start = start;
	st->end = end;
	st->lazy_tag = false;
	if (start == end) {
		st->left = st->right = NULL;
		st->sum = (int)(binary_str[start] - '0');
	}
	else {
		int mid = (start + end) >> 1;
		st->left = build(start, mid, binary_str);
		st->right = build(mid + 1, end, binary_str);
		st->sum = st->left->sum + st->right->sum;
	}
	return st;
}

void update(int start, int end, SegmentTree st) {
	if (contain(start, end, st)) {
		xor (st);
		st->lazy_tag = !st->lazy_tag;
		return;
	}
	tagDown(st);
	if (cross(start, end, st->left)) {
		update(start, end, st->left);
	}
	if (cross(start, end, st->right)) {
		update(start, end, st->right);
	}
	st->sum = st->left->sum + st->right->sum;
}

int sum(int start, int end, SegmentTree st) {
	if (contain(start, end, st)) {
		return st->sum;
	}
	tagDown(st);
	int result = 0;
	if (cross(start, end, st->left)) {
		result += sum(start, end, st->left);
	}
	if (cross(start, end, st->right)) {
		result += sum(start, end, st->right);
	}
	return result;
}

void tagDown(SegmentTree st) {
	if (st->lazy_tag) {
		xor (st->left);
		st->left->lazy_tag = !st->left->lazy_tag;
		xor (st->right);
		st->right->lazy_tag = !st->right->lazy_tag;
		st->lazy_tag = false;
	}
}

void xor(SegmentTree st) {
	st->sum = len(st) - st->sum;
}

int len(SegmentTree st) {
	return st->end - st->start + 1;
}

bool contain(int start, int end, SegmentTree st) {
	return start <= st->start && st->end <= end;
}

bool cross(int start, int end, SegmentTree st) {
	return start <= st->end && st->start <= end;
}

void deleteTree(SegmentTree st) {
	if (st == NULL) return;
	deleteTree(st->left);
	deleteTree(st->right);
	free(st);
}
```