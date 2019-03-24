/*
���P2169
https://www.luogu.org/problemnew/show/P2169
*/

#include <cstdio>
#include <cstdlib>
#include <vector>
#include <stack>
#include <queue>
using namespace std;

#define NO_VALUE -1

typedef long long LL;

//�ڽӵ�ṹ��
struct AdjNode {
	int v; //�ڽӵ㶥��
	int weight; //�ڽӱ�Ȩ��
	AdjNode(int v, int weight) : v(v), weight(weight) {}
};

//ͼ�ṹ��
typedef struct Graph {

	vector<AdjNode> *list; //�ڽӱ�
	int nv; //������

	/* ���캯�� */
	Graph(int nv) : nv(nv) {
		list = new vector<AdjNode>[nv];
	}

	/* ����� */
	void insertEdge(int v, int w, int weight) {
		list[v].push_back(AdjNode(w, weight));
	}

	/* ɾ���ڽӱ�vector */
	void clear() {
		for (int i = 0; i < nv; i++)
			vector<AdjNode>().swap(list[i]);
	}
} *PGraph;

//Tarjan��
class Tarjan {
public:
	Tarjan() {}
	~Tarjan() {}

	/* �������ͼָ��pGraph����ǿ��ͨ��֧����color���ÿ��������������ͨ������*/
	int tarjan(PGraph pGraph, int *color);
private:
	/* dfs��*/
	void dfs(PGraph pGraph, int v, int *color);

	//�����
	int *dfn_;
	int *low_;
	stack<int> vstack_;
	int vcount_; //����dfs���򣬴�1��ʼ����
	int color_count_; //��ͨ������������0��ʼ
};

int Tarjan::tarjan(PGraph pGraph, int * color) {
	int nv = pGraph->nv;
	dfn_ = new int[nv];
	low_ = new int[nv];
	fill(dfn_, dfn_ + nv, 0);
	fill(color, color + nv, NO_VALUE);
	vcount_ = 0;
	color_count_ = 0;
	for (int i = 0; i < nv; i++)
		if (!dfn_[i]) {
			dfs(pGraph, i, color);
		}
	free(dfn_);
	free(low_);
	return color_count_;
}

void Tarjan::dfs(PGraph pGraph, int v, int * color) {
	dfn_[v] = low_[v] = ++vcount_;
	vstack_.push(v);
	for (AdjNode adjNode : pGraph->list[v]) {
		int adjVertex = adjNode.v;
		if (!dfn_[adjVertex]) {
			dfs(pGraph, adjVertex, color);
			if (low_[adjVertex] < low_[v]) low_[v] = low_[adjVertex];
		}
		else if (color[adjVertex] == NO_VALUE) {
			if (dfn_[adjVertex] < low_[v]) low_[v] = dfn_[adjVertex];
		}
	}
	if (dfn_[v] == low_[v]) {
		while (vstack_.top() != v) {
			color[vstack_.top()] = color_count_;
			vstack_.pop();
		}
		color[vstack_.top()] = color_count_++;
		vstack_.pop();
	}
}

//Dijkstra��
class Dijkstra {
public:
	Dijkstra() {}
	~Dijkstra() {}

	LL dijkstra(PGraph pGraph, int src, int des);
private:
	//���ȶ���ʹ�õĽṹ��
	struct Node {
		int v;
		LL dist;
		Node(int v, LL dist) : v(v), dist(dist) {}
	};

	struct cmp {
		bool operator() (Node& a, Node& b) {
			return a.dist > b.dist;
		}
	};

	//�����
	LL *dist_;
	bool *collected_;
};

LL Dijkstra::dijkstra(PGraph pGraph, int src, int des) {
	int nv = pGraph->nv;
	dist_ = new LL[nv];
	fill(dist_, dist_ + nv, NO_VALUE);
	collected_ = new bool[nv];
	fill(collected_, collected_ + nv, false);
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
		for (AdjNode adjNode : pGraph->list[minV]) {
			int adjVertex = adjNode.v;
			int adjWeight = adjNode.weight;
			if (!collected_[adjVertex]) {
				if (dist_[minV] + adjWeight < dist_[adjVertex] || dist_[adjVertex] == NO_VALUE) {
					dist_[adjVertex] = dist_[minV] + adjWeight;
					q.push(Node(adjVertex, dist_[adjVertex]));
				}
			}
		}
	} //while
	LL result = dist_[des];
	free(dist_);
	free(collected_);
	return result;
}

int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	PGraph pGraph = new Graph(n);	
	for (int i = 0; i < m; i++) {
		int v, w, time;
		scanf("%d %d %d", &v, &w, &time);
		pGraph->insertEdge(v - 1, w - 1, time);
	}
	int *color = new int[n];
	Tarjan tarjan;
	int nComponents = tarjan.tarjan(pGraph, color);
	//����ǿ��ͨ�����ٴ���һ��ͼ������Ϊ��ͨ����
	PGraph pComGraph = new Graph(nComponents);
	int *edge = new int[nComponents];
	for (int i = 0; i < n; i++) {
		int v = color[i];
		fill(edge, edge + nComponents, NO_VALUE);
		for (AdjNode adjNode : pGraph->list[i])
			if (v != color[adjNode.v]) {
				//i��adjNode.v����һ����ͨ������
				int w = color[adjNode.v];
				if (edge[w] == NO_VALUE || edge[w] > adjNode.weight)
					edge[w] = adjNode.weight;
			}
		for (int j = 0; j < nComponents; j++)
			if (edge[j] != NO_VALUE)
				pComGraph->insertEdge(v, j, edge[j]);
	}
	pGraph->clear();
	Dijkstra dijkstra;
	LL result = dijkstra.dijkstra(pComGraph, color[0], color[n - 1]);
	printf("%d", result);
	pComGraph->clear();
	return 0;
}