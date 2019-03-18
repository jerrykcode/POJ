# P1330 ���������ѧ
[ԭ���ַ](https://www.luogu.org/problemnew/show/P1330)

## ��Ŀ����

����һֻ��ˢ�ֵ��ϲܣ�����ڼ䣬��ÿ�춼������������ѧ��У԰��ˢ�֡���з��������Ĳ�

���е���ˬ����з�������������ѧ�����ò�ˢ�֡�

�����ѧ��У԰��һ����N���㹹�ɵ�����ͼ��N����֮����M����·���ӡ�ÿֻ��з���Զ�һ�����

�з�������ĳ���㱻������������������ĵ�·�ͱ������ˣ��ܾ��޷�������Щ��·��ˢ���ˡ�

�ǳ������һ���ǣ���з��һ�ֲ���г���������ֻ��з���������ڵ�������ʱ�����ǻᷢ����

ͻ��

ѯ�ʣ�������Ҫ����ֻ��з�����Է������е�·���Ҳ�������ͻ��

## ���������ʽ

### �����ʽ��

��һ�У���������N��M

������M�У�ÿ����������A��B����ʾ��A����B֮���е�·������

### �����ʽ��

��һ�У������з�޷��������е�·���������Impossible�����������һ����������ʾ������Ҫ

����ֻ��з��

### ��������#1�� 

3 3  
1 2  
1 3  
2 3  

### �������#1�� 

Impossible  


### ��������#2�� 

3 2  
1 2  
2 3  

### �������#2�� 

1  

## ˼·

�������е�·����һͷ�к�з������һͷû�к�з�������е�·�����������Ҳ�������ֻ��з���ڡ�����ֻҪ���������ͼ���������㼯�У�һ�����ϵ����ж�����к�з����һ�����ϵ����ж����û�к�з���ɡ���û�ж���ͼ�������"Impossible"��

��ĿҪ��������ٵĺ�з��������ͼ�ж�����Ŀ���ٵĶ��㼯�Ķ�������

BFS��������ɫ�Զ���ͼȾɫ����ʼʱ���ж�������ɫ����ÿһ����ͨ��������һ�����㿪ʼ������Ⱦ��һ����ɫ��Ȼ����ӡ����ڳ����еĶ��㣬�������ڽӵ���û����ɫ��Ⱦ�������෴����ɫ�����ڽӵ���Ⱦɫ����ɫ������ͬ�����޷����ɶ���ͼ��Ⱦ��ͬһ����ɫ�Ķ��㹹��һ�����ϡ���¼������ɫ�Ķ�����Ŀ��������ٵ�һ����


## ����

### C

```c
/*
��� P1330 ���������ѧ(https://www.luogu.org/problemnew/show/P1330)

�������ͼ���������ͼ�ж�����Ŀ���ٵĶ��㼯�Ķ���������û�ж���ͼ�����"Impossible"
*/

#include "stdio.h"
#include "stdlib.h"
#include <memory.h>

typedef unsigned char BYTE;
typedef BYTE Bool;
#define True 1
#define False 0

typedef BYTE Color; //����ͼȾɫʹ��
#define NO_COLOR 0 //û����ɫ
#define BLACK 1
#define WHITE 0xff

//ʵ�ֶ���
typedef struct QNode {
	int val;
	struct QNode *next;
} *QList;

typedef struct Queue {
	QList head;
	QList tail;
} *PQueue;

PQueue initQueue() {
	PQueue pQueue = (PQueue)malloc(sizeof(struct Queue));
	pQueue->head = NULL;
	pQueue->tail = NULL;
	return pQueue;
}

Bool qempty(PQueue pQueue) {
	return pQueue->head == NULL;
}

void qpush(PQueue pQueue, int val) {
	QList list = (QList)malloc(sizeof(struct QNode));
	list->val = val;
	list->next = NULL;
	if (qempty(pQueue)) {
		pQueue->head = pQueue->tail = list;
	}
	else {
		pQueue->tail->next = list;
		pQueue->tail = list;
	}
}

int qpop(PQueue pQueue) {
	if (qempty(pQueue)) return 0;
	int result = pQueue->head->val;
	QList head = pQueue->head;
	pQueue->head = head->next;
	free(head);
	return result;
}

/* BFS����ͼȾɫ��vertexΪ��㣬pMinSetVNumָ���ֵ��ʾ����ͼ�������㼯�ж�����Ŀ���ٵ�

��Ŀ��
�ɹ�����True���޷���������False��*/
Bool bfs(Bool **graph, Color *color, int n, int vertex, int *pMinSetVNum) {
	*pMinSetVNum = 0;
	int maxSetVNum = 0;
	PQueue pQueue = initQueue();
	color[vertex] = BLACK;
	qpush(pQueue, vertex);	
	(*pMinSetVNum)++; //����vertex���ڶ�����Ŀ���ٵĶ��㼯
	Bool flag = True;
	while (!qempty(pQueue)) {
		int v = qpop(pQueue);
		for (int w = 0; w < n; w++)
			if (graph[v][w]) {
				if (color[w] == NO_COLOR) {
					color[w] = color[v] == BLACK ? WHITE : BLACK; 

//wȾΪ��v�෴����ɫ
					color[w] == color[vertex] ? (*pMinSetVNum)++ : 

maxSetVNum++;
					qpush(pQueue, w);
				}
				else if (color[w] == color[v]) {
					flag = False;
					break;
				}
			}
	}
	while (!qempty(pQueue)) qpop(pQueue);
	if (flag && (*pMinSetVNum) > maxSetVNum) { //��pMinSetVNumָ����ٵ���Ŀ
		*pMinSetVNum = maxSetVNum;
	}
	return flag;
}

int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	Bool **graph = (Bool **)malloc(n * sizeof(Bool *));
	for (int i = 0; i < n; i++) {
		graph[i] = (Bool *)malloc(n * sizeof(Bool));
		memset(graph[i], False, n * sizeof(Bool));
	}
	int a, b;
	for (int i = 0; i < m; i++) {
		scanf("%d %d", &a, &b);
		a--;
		b--;
		graph[a][b] = graph[b][a] = True;
	}
	Color *color = (Color *)malloc(n * sizeof(Color));
	memset(color, NO_COLOR, n * sizeof(Color));
	int totalCrabs = 0;
	for (int i = 0; i < n; i++) 
		if (color[i] == NO_COLOR) { //��ÿ����ͨ����Ⱦɫ
			int crabs;
			if (bfs(graph, color, n, i, &crabs))
				totalCrabs += crabs; //�ڶ���ͼ�ж�����Ŀ���ٵĶ��㼯��

�����Ϸ��ú�з
			else {
				printf("Impossible\n");
				totalCrabs = -1;
				break;
			}
		}
	if (totalCrabs != -1) {
		printf("%d\n", totalCrabs);
	}
	free(color);
	for (int i = 0; i < n; i++)
		free(graph[i]);
	free(graph);
	return 0;
}
```

### C++

```cpp
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

	/* BFS����ͼȾɫ��vertexΪ��㣬pMinSetVNumָ���ֵ��ʾ����ͼ�������㼯�ж�����

Ŀ���ٵ���Ŀ��
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
				*pNumCrabs += crabs; //�ڶ���ͼ�ж�����Ŀ���ٵĶ��㼯��

�����Ϸ��ú�з
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
					color[w] = color[v] == BLACK ? WHITE : BLACK; 

//wȾΪ��v�෴����ɫ
					color[w] == color[vertex] ? (*pMinSetVNum)++ : 

maxSetVNum++;
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
```