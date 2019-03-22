#include <cstdio>
#include <cstdlib>
#include <vector>
#include <queue>
using namespace std;

#define NO_VALUE -1

//�ڽӵ�ṹ��
struct AdjNode {
	int v; //�ڽӶ���
	int weight; //�ڽӱ�Ȩ��
	bool inUse; //true��˱�δ��ɾ��
	AdjNode(int v, int weight) : v(v), weight(weight), inUse(true) {}
};

//Dijkstra��
class Dijkstra {
public:
	Dijkstra() {}
	~Dijkstra() {}

	/* �����Դ(n - 1)���յ�(0)����̾��룬��findPathΪtrue����Ҫ��¼·����*/
	int dijkstra(vector<AdjNode> *graph, int n, bool findPath);
	
	/* �õ�·����*/
	void getPath(int **pPath);

	/* �ͷ�·�������ڴ档*/
	void clearPath() { free(path_); }
private:
	//���ȶ���ʹ�õĽṹ��
	struct Node {
		int v;
		int dist;
		Node(int v, int dist) : v(v), dist(dist) {}
	};

	struct cmp {
		bool operator() (Node& a, Node& b) {
			return a.dist > b.dist;
		}
	};

	//�����
	//dist_��collected_��dijkstra������������ڴ��ں�������ǰ�ͷ�
	int *dist_;
	bool *collected_;

	//path_��dijkstra������������ڴ���Ҫ����clearPath�������ͷ�
	int *path_;
};

int Dijkstra::dijkstra(vector<AdjNode>* graph, int n, bool findPath) {
	dist_ = new int[n];
	fill(dist_, dist_ + n, NO_VALUE);
	collected_ = new bool[n];
	fill(collected_, collected_ + n, false);
	if (findPath) {
		path_ = new int[n];
	}
	int src = n - 1, des = 0;
	dist_[src] = 0;
	priority_queue<Node, vector<Node>, cmp> q;
	q.push(Node(src, dist_[src]));
	while (!q.empty()) {
		int minV = q.top().v;
		q.pop();
		if (collected_[minV]) continue;
		collected_[minV] = true;
		if (minV == des) {
			break;
		}
		for (AdjNode adjNode : graph[minV]) {
			if (!adjNode.inUse) continue; //�ñ߱�ɾ��
			int adjVertex = adjNode.v;
			int adjWeight = adjNode.weight;
			if (!collected_[adjVertex]) {
				if (dist_[minV] + adjWeight < dist_[adjVertex] || dist_[adjVertex] == NO_VALUE) {
					dist_[adjVertex] = dist_[minV] + adjWeight;
					q.push(Node(adjVertex, dist_[adjVertex]));
					if (findPath) path_[adjVertex] = minV; //��¼·��
				}
			}
		}
	} //while
	int result = dist_[des];
	free(dist_);
	free(collected_);
	return result;
}

void Dijkstra::getPath(int ** pPath) {
	*pPath = path_;
}

int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	vector<AdjNode> *graph = new vector<AdjNode>[n];
	int a, b, dist;
	for (int i = 0; i < m; i++) {
		scanf("%d %d %d", &a, &b, &dist);
		a--; b--;
		graph[a].push_back(AdjNode(b, dist));
		graph[b].push_back(AdjNode(a, dist));
	}
	Dijkstra dijkstra;
	int result = dijkstra.dijkstra(graph, n, true);
	int *path;
	dijkstra.getPath(&path);
	for (int des = 0; des != n - 1; des = path[des]) {
		auto it = graph[path[des]].begin();
		for (; it != graph[path[des]].end(); it++)
			if (it->v == des) break;
		it->inUse = false; //ɾ����
		int minDist = dijkstra.dijkstra(graph, n, false);
		if (minDist > result) result = minDist;
		it->inUse = true; //��ɾ���ı߼ӻ���
	}
	dijkstra.clearPath();
	printf("%d", result);
	for (int i = 0; i < n; i++)
		vector<AdjNode>().swap(graph[i]);
	return 0;
}