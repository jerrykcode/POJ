# P2825 [HEOI2016/TJOI2016]��Ϸ
[ԭ���ַ](https://www.luogu.org/problem/P2825)

## ��Ŀ����
��2016�꣬��Ե���ϲ������һ����Ϸ�����������á��򵥵�˵�������Ϸ������һ�ŵ�ͼ�Ϸ������ɸ�ը�������Ƿ���ը�����֣����߶㿪���ֵ�ը����������Ϸ�Ĺ����У�СH�뵽������һ�����⣺������һ�ŵ�ͼ�������ŵ�ͼ������ܷ��϶��ٸ�ը����ʹ����������ը��֮�䲻�ụ��ը����ը����ը���ķ�Χ�Ǹ�ը�����ڵ�һ�к�һ�У�ը�����������Դ�͸��ʯͷ�����ǲ��ܴ�͸Ӳʯͷ������һ��n\*m�������ͼ:����\*����յأ�ը�����������Դ�͸�������ڿյ��Ϸ���һöը����x������ʯͷ��ը�����������Դ�͸�������ڴ˷���ը����\#����Ӳʯͷ��ը���������ǲ��ܴ�͸�ģ������ڴ˷���ը�������磺����1\*4�������ͼ\*xx\*�������ͼ�����ֻ�ܷ���һ��ը����������һ��1\*4�������ͼ\*x\#\*�������ͼ����ܷ�������ը��������СH�������һ��n\*m�������ͼ����������ܷ��ö���ը����

## �����ʽ

��һ����������������n,m,n��ʾ��ͼ��������m��ʾ��ͼ��������1��n,m��50������������n��m�и��ַ������������ͼ��\*�ĸ���������n\*m����

## �����ʽ

���һ������a����ʾ����ܷ���ը���ĸ���

## �����������

### ���� #1
4 4  
\#\*\*\*  
\*\#\*\*  
\*\*\#\*  
xxx\#

### ��� #1
5

## ˼·

### ����ͼƥ��

���û��Ӳʯͷ����ôֻ�轫�п����Ƕ���ͼ��һ�ߣ��п�����һ�ߣ�Ȼ����Է���ը���ĵط��������������������߼��ɡ�

����һ��ֻ�ܷ�һ��ը������Ӳʯͷ�ĳ��ֵ���һ�б���������������Ӳʯͷ������£����԰�һ�п��ɶ��С�

### �����к�������Ӳʯͷ��λ�÷ָ�ɶ��кͶ���

������ʾ��

\#\*\*\*  
\*\#\*\*  
\*\*\#\*  
xxx\#

ÿ���������ڵ���Ϊ:

\#000  
1\#11  
22\#2  
333\#

���ǵ�Ӳʯͷ����ÿ���������ڵ�"��"��Ϊ:

\#111  
2\#33  
44\#5  
666\#  
��ԭ����0�б�Ӳʯͷ�ָ���˵�1��(Ϊ�˱�̷��㣬����Ӳʯͷ��`�б��++`������������Ϊ��1�У������ǵ�0��)  
ԭ����1�б�Ӳʯͷ�ָ���˵�2�к͵�3��  
ԭ����2�б�Ӳʯͷ�ָ���˵�4�к͵�5��  
ԭ����3�б�Ӳʯͷ�ָ���˵�6��  
\#(Ӳʯͷ)���ڵĸ��Ӳ�������һ��

����ͬ������

��ʼÿ������������:

\#123  
0\#23  
01\#3  
012\#

���±�ź�ÿ������������:

\#246  
1\#46  
13\#6  
135\#  
��ԭ����0�б�Ӳʯͷ�ָ���˵�1��  
ԭ����1�б�Ӳʯͷ�ָ���˵�2�к͵�3��  
ԭ����2�б�Ӳʯͷ�ָ���˵�4�к͵�5��  
ԭ����3�б�Ӳʯͷ�ָ���˵�6��  
\#(Ӳʯͷ)���ڵĸ��Ӳ�������һ��  

������ʹ��
```cpp
struct Grid {
	char c;
	uint16_t row;
	uint16_t col;
};
```
��¼ÿ��������`�к��б����±�ź��`���к���

��Grid��ά����洢���и��ӣ�����ʱ����֪��```grids[i][j].c```��

����ʱ��`n_rows`��¼��ǰ��������ʼΪ0��һ���������ʱ`n_rows++`��������������'\#'ҲҪ`n_rows++`��
��ʱ��`n_rows`��ʾ�������Ѿ��Ǹ���Ӳʯͷ���±�ź�������ˡ�����ʱ```grids[i][j].row = n_rows```���ɡ�

֮��`���б���`��ά���飬ʹ��`n_cols`��¼��ǰ��������ʼΪ0��һ�б������ʱ`n_cols++`���ڱ���������'\#'ҲҪ
`n_cols++`����ʱ��`n_cols`��ʾ�������Ѿ��Ǹ���Ӳʯͷ���±�ź�������ˡ�����ʱ```girds[i][j].col = n_cols```���ɡ�

֮���ٴα�����ά���飬`��ʱÿ���������ڵ��������ڵ������߼��ɹ�������ͼ`��
ע���������ͼ`��߶����������n_rows`����������ʱ���һ�н�����`n_rows++`������`n_rows`��`�����±�ź������б��+1`��
`�ұ߶���������n_cols`�����ڱ���ʱ���һ�н�����`n_cols++`������`n_cols`��`�����±�ź������б��+1`��

����ͼƥ��Ͳ���˵�ˣ������õ����������㷨��BFSʵ�֡�Ϊʲô����DFS�ݹ�ʵ�ְ�����Ϊ���������̫����QWQ

(��

## ����

```cpp
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <queue>
#include "stdint.h"
#include <iostream>
using namespace std;

#define HARD '#'
#define SOFT 'x'
#define EMPTY '*'

//����
struct Grid {
	char c;
	uint16_t row;
	uint16_t col;
};

typedef uint16_t vertex;
#define NOT_A_VERTEX 0xffff

size_t hungarian(vector<vertex> * graph, size_t left_num, size_t right_num) {
	//����ͼƥ�� �������㷨(BFSʵ��) 
	size_t result = 0;
	vertex * left_matching = new vertex[left_num];
	fill(left_matching, left_matching + left_num, NOT_A_VERTEX);
	vertex * right_matching = new vertex[right_num];
	fill(right_matching, right_matching + right_num, NOT_A_VERTEX);
	vertex * pre = new vertex[left_num];
	fill(pre, pre + left_num, NOT_A_VERTEX);
	bool * visited = new bool[right_num];
	queue<vertex> vq;
	vertex front_v, adj_v, from, to, tmp;
	for (vertex v = 0; v < left_num; v++) {
		fill(visited, visited + right_num, false);
		vq.push(v);
		while (!vq.empty()) {
			front_v = vq.front();
			vq.pop();
			for (auto it = graph[front_v].begin(); it != graph[front_v].end(); it++) {
				adj_v = *it;
				if (!visited[adj_v]) {
					visited[adj_v] = true;
					if (right_matching[adj_v] != NOT_A_VERTEX) {
						vq.push(right_matching[adj_v]);
						pre[right_matching[adj_v]] = front_v;
					}
					else {
						from = front_v;
						to = adj_v;
						while (from != NOT_A_VERTEX) {
							tmp = left_matching[from];
							left_matching[from] = to;
							right_matching[to] = from;
							from = pre[from];
							to = tmp;
						}
						while (!vq.empty()) vq.pop();
						goto NEXT;
					}
				}
			} //for auto
		} //while
	NEXT:
		if (left_matching[v] != NOT_A_VERTEX) result++;
	} //for (vertex v = 0; v < left_num; v++)
	free(left_matching);
	free(right_matching);
	free(pre);
	free(visited);
	queue<vertex>().swap(vq);
	return result;
}

int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	Grid ** grids = new Grid*[n];
	size_t i, j;
	uint16_t n_rows = 0, n_cols = 0;
	for (i = 0; i < n; i++) {
		grids[i] = new Grid[m];
		for (j = 0; j < m; j++) {
			cin >> (grids[i][j].c); //����ø���ַ�
			if (grids[i][j].c == HARD) 
				n_rows++; //������Ӳʯͷ����ø�����¼��������������Ӳʯͷ֮��ʣ�µĸ��Ӽ�Ϊ��һ��
			else grids[i][j].row = n_rows; //��¼������
		}
		n_rows++; //������һ��
	}
	for (j = 0; j < m; j++) {  //���б���
		for (i = 0; i < n; i++) {
			if (grids[i][j].c == HARD)
				n_cols++; //������Ӳʯͷ����ø�����¼��������������Ӳʯͷ֮��ʣ�µĸ��Ӽ�Ϊ��һ��
			else grids[i][j].col = n_cols; //��¼������
		}
		n_cols++; //������һ��
	}
	//��������ͼ��������Ϊ��߶��㣬����Ϊ�ұ߶���
	vector<vertex> * graph = new vector<vertex>[n_rows]; //ע����n_rows����n
	for (i = 0; i < n; i++) {
		for (j = 0; j < m; j++) 
			if (grids[i][j].c == EMPTY) graph[grids[i][j].row].push_back(grids[i][j].col);	 //������������������	
		free(grids[i]);
	}
	free(grids);
	printf("%u", hungarian(graph, n_rows, n_cols)); //�������ͼƥ����
	for (i = 0; i < n_rows; i++)
		vector<vertex>().swap(graph[i]);
	return 0;
}
```

~END