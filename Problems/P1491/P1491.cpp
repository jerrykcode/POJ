#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;
#define NO_VALUE -1
#define MAX_N 200

//����
struct Coordinate {
	float x;
	float y;
	float calculate_dist(Coordinate& c) {
		return sqrt((x - c.x) * (x - c.x) + (y - c.y)*(y - c.y));
	}
};

typedef unsigned char Vertex; //0~255
//�ڽӵ�
struct AdjNode {
	Vertex adj_v;
	float adj_weight;
	AdjNode(Vertex adj_v, float adj_weight) : adj_v(adj_v), adj_weight(adj_weight) {}
};

//�ζ�·��
class SecondShortestDist {
public:
	bool get_second_shortest_dist(vector<AdjNode> * graph, int nv, Vertex src, Vertex des, float *p_second_shortest_dist);
private:
	bool dijkstra(vector<AdjNode> * graph, int nv, Vertex src, Vertex des, float *dist);
	bool astar(vector<AdjNode> * graph, int nv, Vertex src, Vertex des, float *h, float *p_second_shortest_dist);

	//���ȶ���ʹ�õĽṹ��
	struct PriorityNode {
		Vertex v;
		float dist;
		PriorityNode() {}
		PriorityNode(Vertex v, float dist) : v(v), dist(dist) {	}
	};

	//A*���ȶ���ʹ�õĽṹ�壬�̳���PriorityNode
	struct AStarNode : PriorityNode {
		float g;
		//f = dist
		bool contain[MAX_N]; //·�����Ƿ����ĳ����
		AStarNode() {}
		AStarNode(Vertex v, float g, float f) : PriorityNode(v, f), g(g) {
			memset(contain, false, MAX_N * sizeof(bool));
			contain[v] = true;
		}

		//�˹��캯����node��չ�ڽӵ�ʱ����
		AStarNode(AStarNode& node, Vertex v, float g, float f) : PriorityNode(v, f), g(g) { 
			memcpy(contain, node.contain, MAX_N * sizeof(bool));
			contain[v] = true;
		}
	};

	//���ȶ������ڱȽϵĽṹ��
	struct cmp {
		bool operator() (PriorityNode& a, PriorityNode& b) {
			return a.dist > b.dist;
		}
	};
};

bool SecondShortestDist::get_second_shortest_dist(vector<AdjNode>* graph, int nv, Vertex src, Vertex des, float * p_second_shortest_dist) {
	float *h = new float[nv];
	bool result;
	if (dijkstra(graph, nv, des, src, h)) { //���㷴�����·����ΪA*�Ĺ��ۺ���
		result = astar(graph, nv, src, des, h, p_second_shortest_dist); //A*
	}
	else result = false;
	free(h);
	return result;
}

//�������·
bool SecondShortestDist::dijkstra(vector<AdjNode>* graph, int nv, Vertex src, Vertex des, float * dist) {
	fill(dist, dist + nv, NO_VALUE);
	bool *collected = new bool[nv];
	fill(collected, collected + nv, false);
	dist[src] = 0;
	priority_queue<PriorityNode, vector<PriorityNode>, cmp> q;
	q.push(PriorityNode(src, 0));
	Vertex top_v, adj_v;
	float tmp_dist;
	while (!q.empty()) {
		top_v = q.top().v;
		q.pop();
		if (collected[top_v]) continue;
		collected[top_v] = true;
		for (auto it = graph[top_v].begin(); it != graph[top_v].end(); it++) { //�����ڽӵ�
			adj_v = it->adj_v;
			if (!collected[adj_v]) {
				tmp_dist = dist[top_v] + it->adj_weight;
				if (tmp_dist < dist[adj_v] || dist[adj_v] == NO_VALUE) {
					dist[adj_v] = tmp_dist;
					q.push(PriorityNode(adj_v, tmp_dist));
				}
			}
		} //for
	} //while
	free(collected);
	return dist[des] != NO_VALUE;
}

//����ζ�·
bool SecondShortestDist::astar(vector<AdjNode>* graph, int nv, Vertex src, Vertex des, float * h, float * p_second_shortest_dist) {
	priority_queue<AStarNode, vector<AStarNode>, cmp> q;
	q.push(AStarNode(src, 0, h[src]));
	AStarNode top_node;
	Vertex top_v, adj_v;
	float top_g, tmp_g;
	int count = 0;	
	while (!q.empty()) {
		top_node = q.top();
		q.pop();
		top_v = top_node.v;
		top_g = top_node.g;
		if (top_v == des) {
			if (++count == 2) { //�ڶ��ε���des
				while (!q.empty()) q.pop();
				*p_second_shortest_dist = top_g;
				return true;
			}
		}
		for (auto it = graph[top_v].begin(); it != graph[top_v].end(); it++) { //�����ڽӵ�
			adj_v = it->adj_v;		
			if (!top_node.contain[adj_v]) {
				tmp_g = top_g + it->adj_weight;
				//��top_node��չ�ڽӵ�
				q.push(AStarNode(top_node, adj_v, tmp_g, tmp_g + h[adj_v]));
			}
		}
	}
	return false;
}

int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	Coordinate *coordinates = new Coordinate[n];
	float x, y;
	for (int i = 0; i < n; i++) {
		scanf("%f %f", &x, &y);		
		coordinates[i].x = x;
		coordinates[i].y = y;
	}
	vector<AdjNode> *graph = new vector<AdjNode>[n];
	float dist;
	for (int i = 0, p, q; i < m; i++) {
		scanf("%d %d", &p, &q);
		p--; q--;
		dist = coordinates[p].calculate_dist(coordinates[q]);
		graph[p].push_back(AdjNode(q, dist));
		graph[q].push_back(AdjNode(p, dist));
	}
	free(coordinates);
	SecondShortestDist ssd;
	float second_shortest_dist;
	if (ssd.get_second_shortest_dist(graph, n, 0, n - 1, &second_shortest_dist)) {
		printf("%.2f", second_shortest_dist);
	}
	else printf("-1");
	for (int i = 0; i < n; i++)
		vector<AdjNode>().swap(graph[i]);
	return 0;
}