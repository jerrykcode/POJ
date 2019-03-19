# P1342 ���

[ԭ���ַ](https://www.luogu.org/problemnew/show/P1342)

## ��Ŀ����
�ڵ�(shou)��(ji)ʱ��,û�ж����˹ۿ�Ϸ����ݡ�Malidinesia�Ŷ�ϲ����Ա��ʶ����һ��ʵ��������������Ժ,�����ǹ�ɫ�����ϲ��Ƭ�������Ѿ���ӡ���������б�Ҫ����Ϣ�ͼƻ������ѧ���������ַ���Щ���ÿ��ѧ��־Ը�߱�ָ��һ��ȷ�еĹ�������վ������������������һ����,�������ǲ��롣

����Ĺ���ϵͳ�Ƿǳ������:���е���·���ǵ���ģ���������վ�㡣���������뿪��ʼ�㣬����Ŀ�ĵ�֮���ֿճ�������ʼ�㡣ѧ��ÿ�����ϴ��ܲ��������˹�������һ��Ԥ����վ������˿͡�ÿ��վ�㶼��������һ��ѧ������һ�������ʱ��,���е�ѧ�����ص��ܲ���������Ҫ֪�����ǣ�ѧ������Ĺ������õ��ܺ���С�Ƕ��١�

## ���������ʽ

### �����ʽ��

��1������������n��m(1<=n,m<=1000000)��n��վ��ĸ�����m����·�ĸ�����

Ȼ����m�У�ÿ������һ����·������3����������ʼ�㣬Ŀ�ĵغͼ۸�

�ܲ��ڵ�1��վ�㣬��Ǯ������������С��1000000000��

### �����ʽ��

���һ�У���ʾ��С���á�

## �����������

### ��������#1�� 

> 4 6  
> 1 2 10  
> 2 1 60  
> 1 3 20  
> 3 4 10  
> 2 4 5  
> 4 1 50  

### �������#1�� 

> 210  


## ˵��
��ע�⡿

�������ݹ�ģ�ϴ���Ҫʹ�ý�Ϊ��Ч���㷨�����ⲻ��С��ģ���ݷ�����

## ˼·

���Ż�dijkstra���ܲ�������վ������·����Ȼ��Է���ͼҲ��һ���ܲ�������վ������·����


## ����

```cpp
#include <iostream>
#include <vector>
#include <queue>
#include <cstdlib>
#include <cstdio>
using namespace std;

#define NO_VALUE -1

typedef long long Cost; //����
typedef int Vertex; //����

struct AdjNode { //�ڽӵ�ṹ��
	Vertex v; //�ڽӶ���
	int weight; //�ڽӱ�Ȩ
	AdjNode(Vertex v, int weight) : v(v), weight(weight) {}
};

//���ȶ�����Ҫ�Ľṹ��
struct Node {
	Vertex v;
	Cost dist;
	Node(Vertex v, Cost dist) : v(v), dist(dist) {}
};

struct cmp {
	bool operator() (Node& a, Node& b) {
		return a.dist > b.dist;
	}
};

Cost dijkstra(vector<AdjNode>* graph, int n, Vertex src) {
	Cost totalCost = 0;
	Cost *dist = new Cost[n];
	fill(dist, dist + n, NO_VALUE);
	bool *collected = new bool[n];
	fill(collected, collected + n, false);
	dist[src] = 0;
	priority_queue<Node, vector<Node>, cmp> q;
	q.push(Node(src, 0));
	while (!q.empty()) {
		Node minNode = q.top();
		Vertex minV = minNode.v;
		q.pop();
		if (collected[minV]) continue;
		collected[minV] = true;
		totalCost += dist[minV];
	//	for (AdjNode adjNode : graph[minV]) { //��ȱ������range-based ��for�� loops only available with -std=c++11 or -std=gnu++11
	//		Vertex adjVertex = adjNode.v;
	//		Cost adjWeight = adjNode.weight;
		for (vector<AdjNode>::iterator it = graph[minV].begin(); it != graph[minV].end(); it++) { //autoҲ�������:(
			Vertex adjVertex = it->v;
			int adjWeight = it->weight;
			if (!collected[adjVertex])
				if (dist[minV] + adjWeight < dist[adjVertex] || dist[adjVertex] == NO_VALUE) {
					dist[adjVertex] = dist[minV] + adjWeight;
					q.push(Node(adjVertex, dist[adjVertex]));
				}
		}
	}//while
	free(dist);
	free(collected);
	return totalCost;
}

void clearGraph(vector<AdjNode> *graph, int n) {
	for (int i = 0; i < n; i++) {
		graph[i].clear();
		vector<AdjNode>().swap(graph[i]);
	}
	//free(graph);
}

int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	vector<AdjNode> *graph = new vector<AdjNode>[n];
	int src, des, cost;
	for (int i = 0; i < m; i++) {
		scanf("%d %d %d", &src, &des, &cost);
		graph[src - 1].push_back(AdjNode(des - 1, cost));
	}
	Cost totalCost = dijkstra(graph, n, 0);
	//��������ͼ
	vector<AdjNode> *inverseGraph = new vector<AdjNode>[n];
	for (Vertex v = 0; v < n; v++) 
		//for (AdjNode adjNode : graph[v]) {
		for (vector<AdjNode>::iterator it = graph[v].begin(); it != graph[v].end(); it++) {
			//inverseGraph[adjNode.v].push_back(AdjNode(v, adjNode.weight));
			inverseGraph[it->v].push_back(AdjNode(v, it->weight));
		}
	clearGraph(graph, n);
	totalCost += dijkstra(inverseGraph, n, 0);
	clearGraph(inverseGraph, n);
	printf("%lld\n", totalCost);
	return 0;
}
```