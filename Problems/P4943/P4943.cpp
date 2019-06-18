#include <cstdio>
#include <cstdlib>
#include <vector>
#include <queue>
using namespace std;

typedef unsigned short vertex_t; //��������(�����������50000)
typedef unsigned short weight_t; //ͼ�ı�Ȩ������(�����������1000)
typedef unsigned int dist_t; //��������(��Ȩ�����1000��������֮��ľ�����ܳ���65535)

//dist_t���ܵ����ֵ
#define DIST_T_INF 0xffffffff

//�ڽӵ�ṹ��
struct AdjNode {
	vertex_t adj_v; //�ڽӶ���
	weight_t adj_weight; //�ڽӱ�Ȩ��
	AdjNode(vertex_t adj_v, weight_t adj_weight) : adj_v(adj_v), adj_weight(adj_weight) {}
};

//Dijkstra
class Dijkstra {
public:
	/*
	������̾���
	@param graph ͼ
	@param n ��������������0~n-1
	@param src Դ
	@param des �յ�
	@param accessible ���飬��ʾһ�������Ƿ�ɴ�
	@return dist_t ����src��des֮�����̾���
	*/
	dist_t minDist(vector<AdjNode>* graph, size_t n, vertex_t src, vertex_t des, bool * accessible);

private:
	//���ȶ��д洢�Ľṹ��
	struct PriorityNode {
		vertex_t v; //����
		dist_t dist; //Դ��v�ľ���
		PriorityNode(vertex_t v, dist_t dist) : v(v), dist(dist) {}

		//���ȶ������ڱȽϵĽṹ��
		struct cmp {
			bool operator() (PriorityNode& a, PriorityNode& b) {				
				return a.dist > b.dist;
			}
		};
	};

private:
	//��Ա����
	dist_t * dist_; //dist_[v]Ϊ��ǰsrc��v����̾���
	bool * collected_; //collected_[v]��ʾ��ǰv�Ƿ���¼
	priority_queue<PriorityNode, vector<PriorityNode>, PriorityNode::cmp> pqueue_; //���ȶ���
};

dist_t Dijkstra::minDist(vector<AdjNode>* graph, size_t n, vertex_t src, vertex_t des, bool * accessible) {
	//dijkstra�㷨
	dist_ = new dist_t[n];
	fill(dist_, dist_ + n, DIST_T_INF); //��ʼ��
	collected_ = new bool[n];
	fill(collected_, collected_ + n, false); //��ʼ��
	dist_[src] = 0;
	pqueue_.push(PriorityNode(src, 0));
	vertex_t top_v, adj_v;
	dist_t tmp_dist;
	while (!pqueue_.empty()) {
		top_v = pqueue_.top().v; //��ǰ��src������С�Ķ��������
		pqueue_.pop();
		if (collected_[top_v]) continue;
		collected_[top_v] = true;
		if (top_v == des) {
			//�����յ�
			while (!pqueue_.empty()) pqueue_.pop();
			break;
		}
		for (auto it = graph[top_v].begin(); it != graph[top_v].end(); it++) { //�����ڽӵ�
			adj_v = it->adj_v; //�ڽӵ�
			if (!accessible[adj_v]) continue; //��adj_v���ɴ��continue
			if (!collected_[adj_v]) { 
				//��ʱadj_vû����¼����src��adj_v����̾��뻹δȷ��
				tmp_dist = dist_[top_v] + (dist_t)it->adj_weight; //tmp_dist = src��top_v�ľ��� + top_v��adj_v�ľ���
				if (tmp_dist < dist_[adj_v]) {
					//����
					dist_[adj_v] = tmp_dist;
					pqueue_.push(PriorityNode(adj_v, tmp_dist));
				}
			}
		} //for
	} //while
	//��src���ɴ�des����dist_[des]ΪDIST_T_INF
	dist_t result = dist_[des];
	//�ͷ��ڴ�
	free(dist_);
	free(collected_);
	return result;
}

int main() {
	int n, m, k;
	scanf("%d %d %d", &n, &m, &k);	
	bool * accessible = new bool[n];
	//��ʼ�����ж���ɴ�
	fill(accessible, accessible + n, true);
	size_t i;
	if (k) {
		int room;
		for (i = 0; i < k; i++) {
			scanf("%d", &room);
			//�ö���(����)��Harry�ɴ��Ron��˵���ɴ�
			//���붥����Ϊ 1~n����Ϊ0~n-1
			accessible[room - 1] = false;
		}
	}
	vector<AdjNode> * graph = new vector<AdjNode>[n];
	int a, b, c;
	for (i = 0; i < m; i++) {
		//�����
		scanf("%d %d %d", &a, &b, &c);
		a--; b--; //�����Ÿ�Ϊ��0��ʼ		
		graph[a].push_back(AdjNode((vertex_t)b, (weight_t)c));
		graph[b].push_back(AdjNode((vertex_t)a, (weight_t)c));
	}	
	scanf("%d %d", &a, &b);
	//des_x��des_yΪ��Ҫ���������Ŀ�ĵ�
	vertex_t des_x = a - 1, des_y = b - 1; //��Ÿ�Ϊ��0��ʼ
	Dijkstra dijkstra;
	//�ȼ���Ron����des_x��des_y����̾��룬��Ϊ��ʱaccessible��Ron���ɴ�Ķ����Ѿ����Ϊfalse��
	dist_t ron_x = dijkstra.minDist(graph, n, 0, des_x, accessible); //Ron����des_x����̾���(ʱ��)
	dist_t ron_y = dijkstra.minDist(graph, n, 0, des_y, accessible); //Ron����des_y����̾���(ʱ��)
	dist_t harry_x, harry_y, harry_x_y;
	if (k) { //������ֻ��Harry�ߵĶ���
		fill(accessible, accessible + n, true); //���ж���Harry���ɴ�
		harry_x = dijkstra.minDist(graph, n, 0, des_x, accessible); //Harry����des_x����̾���(ʱ��)
		harry_y = dijkstra.minDist(graph, n, 0, des_y, accessible); //Harry����des_y����̾���(ʱ��)
		harry_x_y = dijkstra.minDist(graph, n, des_x, des_y, accessible); //Harry��x�ߵ�y����̾���(ʱ��)
	}
	else { //��������ֻ��Harry�ߵĶ���
		//���ж���Harry��Ron���ɴHarry��������һ���������̾�����Ron����ö������̾�����ͬ
		harry_x = ron_x;
		harry_y = ron_y;
	}
	dist_t result = DIST_T_INF; //���
	result = min(result, max(harry_x, ron_y)); //Harryȥdes_x, Ronȥdes_y
	result = min(result, max(harry_y, ron_x)); //Harryȥdes_y, Ronȥdes_x
	if (k) {
		//des_x��des_y����Harryһ����ȥ��
		//(Harry�ȵ�des_x�ٵ�des_y�����ȵ�des_y�ٵ�des_x)
		//�ڴ���ֻ��Harry�ɴ�Ķ���ʱ�����ַ�ʽ�ſ��ܸ���
		result = min(result, min(harry_x + harry_x_y, harry_y + harry_x_y));
	}
	printf("%u", result);
	free(accessible);
	for (i = 0; i < n; i++)
		vector<AdjNode>().swap(graph[i]);
	return 0;
}