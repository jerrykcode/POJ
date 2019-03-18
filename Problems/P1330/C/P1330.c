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

/* BFS����ͼȾɫ��vertexΪ��㣬pMinSetVNumָ���ֵ��ʾ����ͼ�������㼯�ж�����Ŀ���ٵ���Ŀ��
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
					color[w] = color[v] == BLACK ? WHITE : BLACK; //wȾΪ��v�෴����ɫ
					color[w] == color[vertex] ? (*pMinSetVNum)++ : maxSetVNum++;
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
				totalCrabs += crabs; //�ڶ���ͼ�ж�����Ŀ���ٵĶ��㼯�Ķ����Ϸ��ú�з
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