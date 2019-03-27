#include <cstdio>
#include <cstdlib>
#include <vector>
#include <queue>
using namespace std;

#define NO_VALUE -1

//�ڽӵ�ṹ��
struct AdjNode {
	int v; //�ڽӵ�
	int weight; //�ڽӱ�Ȩ��
	AdjNode(int v, int weight) : v(v), weight(weight) {}
};

class Dijkstra {
public :
	Dijkstra() {}
	~Dijkstra() {}

	/* �����Դ(0)���յ�(n - 1)�����·�������·���������޷�����n - 1�򷵻�false��*/
	bool dijkstra(vector<AdjNode> *graph, int n, int *pMinDist, int *pPathCount);
private:
	//���ȶ���ʹ�õĽṹ��
	struct Node {
		int v;
		int dist;
		Node(int v, int dist) : v(v), dist(dist) {}
	};
	struct cmp {
		bool operator () (Node& a, Node& b) {
			return a.dist > b.dist;
		}
	};
};

bool Dijkstra::dijkstra(vector<AdjNode>* graph, int n, int * pMinDist, int * pPathCount) {
	int *dist = new int[n];
	fill(dist, dist + n, NO_VALUE);
	bool *collected = new bool[n];
	fill(collected, collected + n, false);
	int *count = new int[n];
	int src = 0, des = n - 1;
	dist[src] = 0;
	count[src] = 1; //src��src�����·����1��
	priority_queue<Node, vector<Node>, cmp> q;
	q.push(Node(src, dist[src]));
	while (!q.empty()) {
		int minV = q.top().v;
		q.pop();
		if (collected[minV]) continue;
		collected[minV] = true;
		if (minV == des) {
			break;
		}
		for (AdjNode adjNode : graph[minV]) {
			int adjVertex = adjNode.v;
			int adjWeight = adjNode.weight;
			if (!collected[adjVertex]) {
				int tmpDist = dist[minV] + adjWeight;
				if (tmpDist < dist[adjVertex] || dist[adjVertex] == NO_VALUE) {
					dist[adjVertex] = tmpDist;
					q.push(Node(adjVertex, dist[adjVertex]));
					count[adjVertex] = count[minV]; //����Ϊsrc��minV�����·����
				}
				else if (tmpDist == dist[adjVertex]) {
					count[adjVertex] += count[minV]; //Ҳ����ͨ��minV����adjVertex���ʼ���minV�����·����
				}
			}
		}
	}//while
	bool result = collected[des];
	if (result) {
		*pMinDist = dist[des];
		*pPathCount = count[des];
	}
	free(dist);
	free(collected);
	free(count);
	return result;
}

int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	int **mgraph = new int*[n];
	for (int i = 0; i < n; i++) {
		mgraph[i] = new int[n];
		fill(mgraph[i], mgraph[i] + n, NO_VALUE);
	}
	int v, w, dist;
	for (int i = 0; i < m; i++) {
		scanf("%d %d %d", &v, &w, &dist);
		v--; w--;
		if (dist < mgraph[v][w] || mgraph[v][w] == NO_VALUE) mgraph[v][w] = dist;
	}
	vector<AdjNode> *graph = new vector<AdjNode>[n];	
	for (int v = 0; v < n; v++)
		for (int w = 0; w < n; w++) {
			if (mgraph[v][w] != NO_VALUE) graph[v].push_back(AdjNode(w, mgraph[v][w]));
		}
	for (int i = 0; i < n; i++)
		free(mgraph[i]);
	free(mgraph);
	Dijkstra dijkstra;
	int minDist, pathCount;
	if (dijkstra.dijkstra(graph, n, &minDist, &pathCount)) {
		printf("%d %d", minDist, pathCount);
	}
	else printf("No answer");
	for (int i = 0; i < n; i++)
		vector<AdjNode>().swap(graph[i]);
	return 0;
}