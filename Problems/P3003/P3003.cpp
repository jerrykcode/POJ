#include <cstdio>
#include <cstdlib>
#include <vector>
#include <queue>
using namespace std;

//AdjNodeΪ�ڽӵ�ṹ�� 
//��vector<AdjNode> * ��ʾͼ
//��ͼ��һ���洢vector�����飬��ÿ��������һ��vector�洢���ڽӵ���Ϣ
//�����ڽӵ�������ڽӵ�֮��ߵ�Ȩ��
struct AdjNode {
	int adj_vertex; //�ڽӶ���
	int adj_weight; //�ڽӱ�Ȩ��
	AdjNode(int adj_vertex, int adj_weight) : adj_vertex(adj_vertex), adj_weight(adj_weight) {}
};

//Dijkstra��
class Dijkstra {
public:
	/*
	������̾���
	@param graph ͼ
	@param n ������
	@param src Դ
	@param des �յ�
	@return int src��des����̾���
	*/
	int dijkstra(vector<AdjNode> * graph, int n, int src, int des);
private:

	const int inf = 0x7fffffff;

	//���ȶ���ʹ�õĽṹ��
	struct PriorityNode {
		int vertex;
		int dist;
		PriorityNode(int vertex, int dist) : vertex(vertex), dist(dist) {}
	};

	//�Ƚ�PriorityNode
	struct cmp {
		bool operator() (PriorityNode& a, PriorityNode& b) {
			return a.dist > b.dist;
		}
	};

private:
	//��private��Ա����
	int *dist_;
	bool *collected_;
	priority_queue<PriorityNode, vector<PriorityNode>, cmp> pq_;
};

int Dijkstra::dijkstra(vector<AdjNode>* graph, int n, int src, int des) {
	//dijkstraģ��
	dist_ = new int[n];
	fill(dist_, dist_ + n, inf); //��ʼ����̾���
	collected_ = new bool[n];
	fill(collected_, collected_ + n, false); //��ʼ��
	dist_[src] = 0;
	pq_.push(PriorityNode(src, 0));
	int top_vertex, adj_vertex;
	int adj_weight, tmp_dist;
	while (!pq_.empty()) {
		top_vertex = pq_.top().vertex; //��ǰsrc��top_vertex����̾�����С
		pq_.pop();
		if (collected_[top_vertex]) continue;
		collected_[top_vertex] = true;
		if (top_vertex == des) {
			//src��des����̾�����ȷ��
			while (!pq_.empty()) {
				//��ն���
				pq_.pop();
			}
			break;
		}
		for (auto it = graph[top_vertex].begin(); it != graph[top_vertex].end(); it++) {
			//����top_vertex���ڽӵ�
			adj_vertex = it->adj_vertex; //�ڽӵ�
			if (!collected_[adj_vertex]) {
				adj_weight = it->adj_weight; //top_vertex��adj_vertex֮��ı�Ȩ��
				tmp_dist = dist_[top_vertex] + adj_weight; //����top_vertex����adj_vertex�ľ���
				if (tmp_dist < dist_[adj_vertex]) {
					dist_[adj_vertex] = tmp_dist;
					pq_.push(PriorityNode(adj_vertex, tmp_dist));
				}
			}
		} //for
	} //while
	int result = dist_[des];
	//ɾ���ڴ�
	free(dist_);
	free(collected_);
	return result;
}

int main() {
	int c, p, pb, pa1, pa2;
	scanf("%d %d %d %d %d", &c, &p, &pb, &pa1, &pa2);
	pb--;
	pa1--;
	pa2--;
	vector<AdjNode> * graph = new vector<AdjNode>[p];
	int p1, p2, d;
	for (int i = 0; i < c; i++) {
		scanf("%d %d %d", &p1, &p2, &d);
		p1-- ; 
		p2--;
		graph[p1].push_back(AdjNode(p2, d));
		graph[p2].push_back(AdjNode(p1, d));
	}
	Dijkstra dijkstra;
	int dist_pb_pa1 = dijkstra.dijkstra(graph, p, pb, pa1);
	int dist_pb_pa2 = dijkstra.dijkstra(graph, p, pb, pa2);
	int dist_pa1_pa2 = dijkstra.dijkstra(graph, p, pa1, pa2);
	//pb��pa1�ٵ�pa2������pb�ȵ�pa2�ٵ�pa1����������С�ļ���
	int result = min(dist_pb_pa1 + dist_pa1_pa2, dist_pb_pa2 + dist_pa1_pa2);
	printf("%d\n", result);
	for (int i = 0; i < p; i++)
		vector<AdjNode>().swap(graph[i]);
	return 0;
}