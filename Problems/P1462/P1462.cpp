#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

#define NO_VALUE -1

typedef long long LL;

//�ڽӵ�ṹ��
struct AdjNode {
	int v; //�ڽӵ� 
	int weight; //�ڽӱ�Ȩ��
	AdjNode(int v, int weight) : v(v), weight(weight) {}
};

//Dijkstra��
class Dijkstra {
public:
	Dijkstra() {}
	~Dijkstra() {}

	/* �����Դ(0)���յ�(nv - 1)�����·����·���ϵĶ���Ȩ�ز�����max_f��*/
	LL dijkstra(vector<AdjNode> *graph, int nv, int *f, int max_f);
private:
	//���ȶ���ʹ�õĽṹ��
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

	//�����
	LL *dist_;
	bool *collected_;
};

LL Dijkstra::dijkstra(vector<AdjNode>* graph, int nv, int * f, int max_f) {
	int src = 0, des = nv - 1;
	if (f[src] > max_f || f[des] > max_f) return NO_VALUE;
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
		for (AdjNode adjNode : graph[minV]) { //����minV���ڽӵ�
			int adjVertex = adjNode.v;
			int adjWeight = adjNode.weight;
			if (!collected_[adjVertex] && f[adjVertex] <= max_f) {
				if (dist_[minV] + adjWeight < dist_[adjVertex] || dist_[adjVertex] == NO_VALUE) {
					dist_[adjVertex] = dist_[minV] + adjWeight;
					q.push(Node(adjVertex, dist_[adjVertex]));
				}
			}
		}
	} //while
	//���޷�����des����dist_[des]��ֵΪNO_VALUE(-1)
	LL result = dist_[des];
	free(dist_);
	free(collected_);
	return result;
}

/* ���ֲ��ҡ�*/
int binary_search(int *arr, int n, int val) {
	int left = 0, right = n - 1;
	while (left <= right) {
		int mid = (left + right) / 2;
		if (arr[mid] == val) return mid;
		else if (arr[mid] < val) left = mid + 1;
		else right = mid - 1;
	}
	return -1;
}

int main() {
	int n, m, b;
	scanf("%d %d %d", &n, &m, &b);
	if (n == 0) {
		printf("0");
		return 0;
	}
	vector<AdjNode> *graph = new vector<AdjNode>[n];
	int *f = new int[n];
	for (int i = 0; i < n; i++)
		scanf("%d", f + i);
	int v, w, c;
	for (int i = 0; i < m; i++) {
		scanf("%d %d %d", &v, &w, &c);
		v--; w--;
		graph[v].push_back(AdjNode(w, c));
		graph[w].push_back(AdjNode(v, c));
	}
	int *f_sorted = new int[n];
	memcpy(f_sorted, f, n * sizeof(int));
	sort(f_sorted, f_sorted + n);
	int left = binary_search(f_sorted, n, max(f[0], f[n - 1])), right = n - 1; //������Ҫsrc��des��Ȩ��
	Dijkstra dijkstra;
	LL min_dist;
	int mid;
	//����
	int last = NO_VALUE;
	while (left <= right) {
		mid = (left + right) / 2;
		min_dist = dijkstra.dijkstra(graph, n, f, f_sorted[mid]);
		if (min_dist == NO_VALUE || min_dist >= b) left = mid + 1; //����Ȩ�ط�Χ
		else {
			last = mid;
			right = mid - 1; //��СȨ�ط�Χ
		}
	}
	last == NO_VALUE ? printf("AFK") : printf("%d", f_sorted[last]);
	free(f);
	free(f_sorted);
	for (int i = 0; i < n; i++)
		vector<AdjNode>().swap(graph[i]);
	return 0;
}