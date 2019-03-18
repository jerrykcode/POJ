/*
��� P1330 ���������ѧ(https://www.luogu.org/problemnew/show/P1330)

�������ͼ���������ͼ�ж�����Ŀ���ٵĶ��㼯�Ķ���������û�ж���ͼ�����"Impossible"
*/

#include <iostream>
#include <stdlib.h>
#include "stdio.h"
using namespace std;

typedef unsigned char BYTE;
typedef BYTE Color; //����ͼȾɫʹ��
#define NO_COLOR 0 //û����ɫ
#define BLACK 1
#define WHITE 0xff

//ʵ�ֶ���
typedef struct QNode {
	int val;
	struct QNode *next;
	QNode(int val) : val(val), next(NULL) {}
} *QList;

class Queue {
public:
	Queue() :head(NULL), tail(NULL)  {}
	~Queue() { clear(); }

	void push(int val);
	int pop();
	bool empty();
	void clear();
private:
	QList head, tail;
};

void Queue::push(int val) {
	QList list = new QNode(val);
	if (empty()) {
		head = tail = list;
	}
	else {
		tail->next = list;
		tail = list;
	}
}

int Queue::pop() {
	if (empty()) return 0;
	int result = head->val;
	QList tmp = head;
	head = head->next;
	delete tmp;
	return result;
}

bool Queue::empty() {
	return head == NULL;
}

void Queue::clear() {
	while (!empty()) pop();
}

//��Ҫ��
class Crab {
public:
	Crab() {}
	~Crab() {}

	/* ��ͼ���з�����graphΪͼ��nΪ��������pNumCrabsָ���ֵ��ʾ������Ҫ�ĺ�з����
	�ɹ�����true���޷���������false��*/
	bool block(bool **graph, int n, int *pNumCrabs);

private:

	/* BFS����ͼȾɫ��vertexΪ��㣬pMinSetVNumָ���ֵ��ʾ����ͼ�������㼯�ж�����Ŀ���ٵ���Ŀ��
	�ɹ�����true���޷���������false��*/
	bool bfs(bool **graph, Color *color, int n, int vertex, int *pMinSetVNum);
};

bool Crab::block(bool ** graph, int n, int * pNumCrabs) {
	Color *color = new Color[n];
	fill(color, color + n, NO_COLOR);
	*pNumCrabs = 0;
	bool flag = true;
	for (int i = 0; i < n; i++)
		if (color[i] == NO_COLOR) { //��ÿ����ͨ����Ⱦɫ
			int crabs = 0;
			if (bfs(graph, color, n, i, &crabs)) {
				*pNumCrabs += crabs; //�ڶ���ͼ�ж�����Ŀ���ٵĶ��㼯�Ķ����Ϸ��ú�з
			}
			else {
				flag = false;
				break;
			}
		}
	free(color);
	return flag;
}

bool Crab::bfs(bool ** graph, Color * color, int n, int vertex, int * pMinSetVNum) {
	*pMinSetVNum = 0;
	int maxSetVNum = 0;
	Queue q;
	color[vertex] = BLACK;
	q.push(vertex);	
	(*pMinSetVNum)++; //����vertex���ڶ�����Ŀ���ٵĶ��㼯
	bool flag = true;
	while (!q.empty()) {
		int v = q.pop();
		for (int w = 0; w < n; w++)
			if (graph[v][w]) {
				if (color[w] == NO_COLOR) {
					color[w] = color[v] == BLACK ? WHITE : BLACK; //wȾΪ��v�෴����ɫ
					color[w] == color[vertex] ? (*pMinSetVNum)++ : maxSetVNum++;
					q.push(w);
				}
				else if (color[w] == color[v]) {
					flag = false;
					break;
				}
			}
	}
	q.clear();
	if (flag && (*pMinSetVNum) > maxSetVNum) { //��pMinSetVNumָ����ٵ���Ŀ
		*pMinSetVNum = maxSetVNum;
	}
	return flag;
}

int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	bool **graph = new bool*[n];
	for (int i = 0; i < n; i++) {
		graph[i] = new bool[n];
		fill(graph[i], graph[i] + n, false);
	}
	int a, b;
	for (int i = 0; i < m; i++) {
		scanf("%d %d", &a, &b);
		a--;
		b--;
		graph[a][b] = graph[b][a] = true;
	}
	Crab crab;
	int nCrabs;
	if (crab.block(graph, n, &nCrabs)) {
		printf("%d\n", nCrabs);
	}
	else {
		printf("Impossible\n");
	}
	for (int i = 0; i < n; i++)
		free(graph[i]);
	free(graph);
	return 0;
}