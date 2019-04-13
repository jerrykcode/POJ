#include <cstdio>
#include <cstdlib>
#include <vector>
#include <queue>
using namespace std;

#define NO_VALUE -1
typedef long long LL;

class Escape {
public:
	Escape() {}
	~Escape() {}

	//main�е��õĺ���
	void escape();
private:
	//dijkstra�����ȶ���ʹ�õĽṹ��
	struct Node {
		int v;
		LL dist;
		Node(int v, LL dist) : v(v), dist(dist) {}
	};
	struct cmp {
		bool operator () (Node& a, Node& b) {
			return a.dist > b.dist;
		}
	};

	//private��Ա����
	void input(); //����
	void bfs(); //����Σ�ճ���
	LL dijkstra(); //�������·��
	void clear(); //�ͷ��ڴ�

	//�����
	int n, m, k, s;
	int p, q;
	int src, des;
	vector<int> *graph;
	int *cost_; //cost_[i]Ϊ����i�ķ��ã�����Ȩ
};

void Escape::escape() {
	input();
	bfs();
	printf("%lld", dijkstra());
	clear();
}

void Escape::input() {
	scanf("%d %d %d %d %d %d", &n, &m, &k, &s, &p, &q);
	src = 0, des = n - 1; //��Ϊ��0��ʼ���
	cost_ = new int[n];
	fill(cost_, cost_ + n, p);
	for (int i = 0, ci; i < k; i++) {
		scanf("%d", &ci);
		ci--; //��Ϊ��0��ʼ���
		cost_[ci] = NO_VALUE;
	}
	graph = new vector<int>[n];
	for (int i = 0, ai, bi; i < m; i++) {
		scanf("%d %d", &ai, &bi);
		ai--; bi--; //��Ϊ��0��ʼ���
		graph[ai].push_back(bi);
		graph[bi].push_back(ai);
	}
}

void Escape::bfs() {	
	//��ռ�������Χs���ڵĳ���ΪΣ�ճ���
	if (s <= 0) return;
	queue<int> que;
	bool *collected = new bool[n];
	fill(collected, collected + n, false);
	int last, tail; //lastΪ��ǰ���һ�������еģ�tailΪ��һ������һ��
	for (int i = 0; i < n; i++) 
		if (cost_[i] == NO_VALUE) {
			//�������б�ռ�����
			que.push(i);
			collected[i] = true;
			last = tail = i;
		}
	int level = 0; //��ǰ��Ϊ0��
	while (!que.empty()) {
		int v = que.front();
		que.pop();
		for (int adj_v : graph[v]) 
			if (!collected[adj_v]) {
				collected[adj_v] = true;				
				que.push(adj_v);
				cost_[adj_v] = q; //��ΪΣ�ճ���
				last = adj_v; //���������ӵĶ���
			}
		if (v == tail) { //����һ������һ���������ˣ�����һ�����
			if (++level >= s) { //��������
				while (!que.empty()) que.pop();
				break;
			}
			tail = last; //����tailΪ�������һ������last
		}
	}
	free(collected);
	cost_[src] = cost_[des] = 0;
}

LL Escape::dijkstra() {
	//dijkstra�������·��
	//����(a, b)�ķ��ü�Ϊb�ķ��ã�(b, a)�ķ��ü�Ϊa�ķ��ã���
	//(a, b)�ı�ȨΪb�ĵ�Ȩ��(b, a)�ı�ȨΪa�ĵ�Ȩ
	LL *dist = new LL[n];
	fill(dist, dist + n, NO_VALUE);
	bool *collected = new bool[n];
	fill(collected, collected + n, false);
	dist[src] = 0;
	priority_queue<Node, vector<Node>, cmp> que;
	que.push(Node(src, dist[src]));
	int min_v;
	LL tmp_dist;
	while (!que.empty()) {
		min_v = que.top().v;
		que.pop();
		if (collected[min_v]) continue;
		collected[min_v] = true;
		if (min_v == des) {
			while (!que.empty()) que.pop();
			break;
		}
		for (int adj_v : graph[min_v]) { //�����ڽӵ�
			if (!collected[adj_v] && cost_[adj_v] != NO_VALUE) {
				tmp_dist = dist[min_v] + cost_[adj_v]; //(min_v, adj_v) �ı�ȨΪ adj_v�ĵ�Ȩ��cost_[adj_v]
				if (tmp_dist < dist[adj_v] || dist[adj_v] == NO_VALUE) {
					dist[adj_v] = tmp_dist;
					que.push(Node(adj_v, tmp_dist));
				}
			}
		} //for adj_v
	} //while
	LL result = dist[des];
	free(dist);
	free(collected);
	return result;
}

void Escape::clear() {
	free(cost_);
	for (int i = 0; i < n; i++)
		vector<int>().swap(graph[i]);
}

int main() {
	Escape escape;
	escape.escape();
	return 0;
}