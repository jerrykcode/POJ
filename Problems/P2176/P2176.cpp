#include <cstdio>
#include <cstdlib>
#include <vector>
#include <queue>
using namespace std;

#define NO_VALUE -1

typedef unsigned char Vertex; //����

//�ڽӵ�ṹ��
struct AdjNode {
	Vertex v; //�ڽӶ���
	int weight; //�ڽӱ�Ȩ��
	AdjNode(Vertex v, int weight) : v(v), weight(weight) {}
};

//Dijkstra��
class Dijkstra {
public :
	Dijkstra() : pre_memory_alloc_(false) {}
	~Dijkstra() { if (pre_memory_alloc_) free(pre_); }

	/* ����Դ(0)���յ�(nv - 1)�����·������p_min_distָ�봫����nvΪ����������record_path��ʾ�Ƿ��¼·����*/
	bool dijkstra(vector<AdjNode> *graph, int nv, bool record_path, int *p_min_dist);

	/* ���εõ����һ�ε���dijkstra����¼·��ʱ�����·���ϵıߣ���p_from��p_toָ�봫����
	   ��һ�ε��ñ������õ����·���ϵ����һ���ߣ�֮��ÿ�ε��õõ��ϴε��õ�ǰһ���ߡ�*/
	bool getMinPath(Vertex *p_from, Vertex *p_to);
private:
	//���ȶ���ʹ�õĽṹ��
	struct Node {
		Vertex v;
		int dist;
		Node(Vertex v, int dist) : v(v), dist(dist) {}
	};
	struct cmp {
		bool operator() (Node& a, Node& b) {
			return a.dist > b.dist;
		}
	};

	//�����
	int nv_;
	Vertex src_, des_; //nv_, src_, des_ ��getMinPath�����ڼ�¼

	int *dist_;
	bool *collected_;
	Vertex *pre_;
	bool pre_memory_alloc_; //pre_����������ڴ���Ϊtrue
};

bool Dijkstra::dijkstra(vector<AdjNode>* graph, int nv, bool record_path, int * p_min_dist) {	
	dist_ = new int[nv];
	fill(dist_, dist_ + nv, NO_VALUE);
	collected_ = new bool[nv];
	fill(collected_, collected_ + nv, false);
	Vertex src = 0, des = nv - 1;
	if (record_path) { //��Ҫ��¼·��
		//����nv_��src_��des_
		nv_ = nv;
		src_ = src;
		des_ = des;
		if (pre_memory_alloc_) free(pre_);
		pre_ = new Vertex[nv];
		pre_memory_alloc_ = true;
	}	
	dist_[(size_t)src] = 0;
	priority_queue<Node, vector<Node>, cmp> q;
	q.push(Node(src, dist_[(size_t)src]));
	while (!q.empty()) {
		Vertex min_vertex = q.top().v;
		q.pop();
		if (collected_[(size_t)min_vertex]) continue;
		collected_[(size_t)min_vertex] = true;
		if (min_vertex == des) {
			while (!q.empty()) q.pop();
			break;
		}
		int min_dist = dist_[(size_t)min_vertex];
		for (AdjNode adjNode : graph[min_vertex]) {
			Vertex adj_vertex = adjNode.v;
			int adj_weight = adjNode.weight;
			if (!collected_[(size_t)adj_vertex]) {
				if (min_dist + adj_weight < dist_[(size_t)adj_vertex] || dist_[(size_t)adj_vertex] == NO_VALUE) {
					dist_[(size_t)adj_vertex] = min_dist + adj_weight;
					q.push(Node(adj_vertex, dist_[(size_t)adj_vertex]));
					if (record_path) pre_[(size_t)adj_vertex] = min_vertex; //��¼·��
				}
			}
		}
	}//while
	bool result = collected_[(size_t)des];
	*p_min_dist = dist_[(size_t)des];
	free(dist_);
	free(collected_);
	return result;
}

bool Dijkstra::getMinPath(Vertex * p_from, Vertex * p_to) {	
	if (des_ == src_) return false;
	*p_from = pre_[(size_t)des_];
	*p_to = des_;
	des_ = *p_from;
	return true;
}

int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	vector<AdjNode> *graph = new vector<AdjNode>[n];
	int a_i, b_i, l_i;
	for (int i = 0; i < m; i++) {
		scanf("%d %d %d", &a_i, &b_i, &l_i);
		a_i--; b_i--;
		graph[a_i].push_back(AdjNode(b_i, l_i));
		graph[b_i].push_back(AdjNode(a_i, l_i));
	}
	Dijkstra dijkstra;
	int min_dist, tmp_dist, result = 0;
	dijkstra.dijkstra(graph, n, true, &min_dist);
	Vertex from, to;	
	while (dijkstra.getMinPath(&from, &to)) { //�������·���ϵ����б�
		auto it = graph[(size_t)from].begin();
		for (; it != graph[(size_t)from].end(); it++)
			if (it->v == to) {
				it->weight *= 2; //����
				break;
			}
		if (dijkstra.dijkstra(graph, n, false, &tmp_dist))
			if (tmp_dist - min_dist > result) result = tmp_dist - min_dist;
		it->weight /= 2; //��ԭ
	}
	printf("%d", result);
	for (int i = 0; i < n; i++)
		vector<AdjNode>().swap(graph[i]);
	return 0;
}