#include <cstdio>
#include <cstdlib>
#include <vector>
#include <queue>
using namespace std;

#define NO_VALUE -1

//�ڽӵ�ṹ��
struct AdjNode {
	int v; //�ڽӶ���
	double weight; //�ڽӱ�Ȩ��
	AdjNode(int v, double weight) : v(v), weight(weight) {}
};

//������С������
class MinCost {
public:
	MinCost() {}
	~MinCost() {}

	/* ����src��Ҫ�õ�num��des������Ҫ���ٻ��ѡ�*/
	double minCost(vector<AdjNode> *graph, int nv, int src, int des, double num);
private:
	//���ȶ���ʹ�õĽṹ��
	struct Node {
		int v;
		double dist;
		Node(int v, double dist) : v(v), dist(dist) {}
	};
	struct cmp {
		bool operator() (Node& a, Node& b) {
			return a.dist > b.dist;
		}
	};

	//�����
	double *dist_;
	bool *collected_;
};

double MinCost::minCost(vector<AdjNode>* graph, int nv, int src, int des, double num) {
	//dijkstra
	dist_ = new double[nv];
	fill(dist_, dist_ + nv, NO_VALUE);
	collected_ = new bool[nv];
	fill(collected_, collected_ + nv, false);
	dist_[src] = num;
	priority_queue<Node, vector<Node>, cmp> q;
	q.push(Node(src, dist_[src]));
	int min_vertex, adj_vertex;
	double adj_weight, tmp_dist;
	while (!q.empty()) {
		min_vertex = q.top().v;
		q.pop();
		if (collected_[min_vertex]) continue;
		collected_[min_vertex] = true;
		if (min_vertex == des) {
			while (!q.empty()) q.pop();
			break;
		}
		for (AdjNode adj_node : graph[min_vertex]) { //�����ڽӵ�
			adj_vertex = adj_node.v;
			adj_weight = adj_node.weight;
			if (!collected_[adj_vertex]) {
				tmp_dist = dist_[min_vertex] / adj_weight; //adj_vertex����min_vertex����src�Ļ���
				if (tmp_dist < dist_[adj_vertex] || dist_[adj_vertex] == NO_VALUE) {
					//����
					dist_[adj_vertex] = tmp_dist;
					q.push(Node(adj_vertex, dist_[adj_vertex]));
				}
			}
		}
	} //while
	double result = dist_[des];
	free(dist_);
	free(collected_);
	return result;
}

int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	vector<AdjNode> *graph = new vector<AdjNode>[n];
	int x, y, z, a, b;
	for (int i = 0; i < m; i++) {
		scanf("%d %d %d", &x, &y, &z);
		//��Ϊ��0��ʼ���
		x--; y--;
		graph[x].push_back(AdjNode(y, ((double)(1.0) - (double)(0.01) * z)));
		graph[y].push_back(AdjNode(x, ((double)(1.0) - (double)(0.01) * z)));
	}
	scanf("%d %d", &a, &b);
	a--; b--;
	MinCost min_cost;
	printf("%.8lf", min_cost.minCost(graph, n, b, a, (double)(100.0)));
	for (int i = 0; i < n; i++)
		vector<AdjNode>().swap(graph[i]);
	return 0;
}