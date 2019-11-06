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
����50%�����ݣ�n <= 4 * 10^4  
�����������ݣ�n <= 5 * 10^5  
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
