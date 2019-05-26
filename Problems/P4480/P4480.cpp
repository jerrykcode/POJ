#include <cstdio>
#include <cstdlib>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

typedef unsigned int uint;
#define INF 0xffffffff

//�ڽӵ�ṹ�� 
struct AdjNode {
	uint adj_v; //�ڽӵ㶥�� 
	uint adj_weight; //�ڽӱ�Ȩ��
	AdjNode(uint adj_v, uint adj_weight) : adj_v(adj_v), adj_weight(adj_weight) {}
};

//Dijkstra�� 
class Dijkstra {
public:

	/* 
	������̾���
	@param graph ͼ
	@param n_vertices ������
	@src Դ
	@dist ����ÿ���������̾���
	*/
	void dijkstra(vector<AdjNode> * graph, uint n_vertices, uint src, uint * dist);
private:
	//���ȶ���ʹ�õĽṹ��
	struct PriorityNode {
		uint v;
		uint dist;
		PriorityNode(uint v, uint dist) : v(v), dist(dist) {}
	};

	struct cmp {
		bool operator() (PriorityNode& a, PriorityNode& b) {
			return a.dist > b.dist;
		}
	};
};

void Dijkstra::dijkstra(vector<AdjNode>* graph, uint n_vertices, uint src, uint * dist) {
	fill(dist, dist + n_vertices, INF);
	bool * collected = new bool[n_vertices];
	fill(collected, collected + n_vertices, false);
	dist[src] = 0;
	priority_queue<PriorityNode, vector<PriorityNode>, cmp> pq;
	pq.push(PriorityNode(src, 0));
	uint top_v, adj_v;
	uint tmp_dist;
	while (!pq.empty()) {
		top_v = pq.top().v;
		pq.pop();
		if (collected[top_v]) continue;
		collected[top_v] = true;
		for (auto it = graph[top_v].begin(); it != graph[top_v].end(); it++) {
			adj_v = it->adj_v;
			if (!collected[adj_v]) {
				tmp_dist = dist[top_v] + it->adj_weight;
				if (tmp_dist < dist[adj_v]) {
					dist[adj_v] = tmp_dist;
					pq.push(PriorityNode(adj_v, tmp_dist));
				}
			}
		} //for
	} //while
	free(collected);
}

//czx��ʱ��������λ��
struct Czx {
	uint time;
	uint v;	
};

bool compare(Czx a, Czx b) {
	return a.time < b.time;
}

int main() {
	uint n, m, b, e;
	scanf("%u %u %u %u", &n, &m, &b, &e);
	b--; e--; //�����Ϊ��0��ʼ���
	vector<AdjNode> * graph = new vector<AdjNode>[n];
	uint x, y, z;
	for (size_t i = 0; i < m; i++) {
		scanf("%u %u %u", &x, &y, &z);
		x--; y--; //�����Ϊ��0��ʼ���
		graph[x].push_back(AdjNode(y, z));
		graph[y].push_back(AdjNode(x, z));
	}
	Dijkstra dijkstra;
	uint * dist = new uint[n];
	dijkstra.dijkstra(graph, n, b, dist);
	for (size_t i = 0; i < n; i++)
		vector<AdjNode>().swap(graph[i]);
	uint t, ai, xi;
	scanf("%u", &t);
	Czx * czx = new Czx[t + 1];
	czx[0].time = 0; //czx�ĳ�ʼʱ��
	czx[0].v = e; //czx�ĳ�ʼλ��
	for (size_t i = 1; i < t + 1; i++) {
		scanf("%u %u", &ai, &xi);
		xi--; //�����Ϊ��0��ʼ���
		czx[i].time = ai;
		czx[i].v = xi;
	}
	sort(czx + 1, czx + t + 1, compare); //����
	uint result = INF;
	for (size_t i = 0; i < t; i++) {
		if (dist[czx[i].v] < czx[i + 1].time) { //����czx[i].v��ʱ��С��czx�ƶ�����һλ�õ�ʱ�̣�����ץ��czx
			result = min(result, max(dist[czx[i].v], czx[i].time));
		}
	}
	result = min(result, max(dist[czx[t].v], czx[t].time)); //czx[t]Ϊczx��󵽴��λ�ã�czx�������ƶ���һ������ץ��czx
	free(czx);
	printf("%u", result);
	return 0;
}