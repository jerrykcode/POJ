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