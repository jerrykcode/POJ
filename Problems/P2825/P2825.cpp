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