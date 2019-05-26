#include <cstdio>
#include <cstdlib>
#include <vector>
#include <queue>
using namespace std;

typedef unsigned short word;
#define WORD_MAX 0xffff

#ifdef INT_MAX
#undef INT_MAX
#endif

#define INT_MAX 0x7fffffff

//�ڽӵ�ṹ��
struct AdjNode {
	word adj_v; //�ڽӶ���
	int adj_weight; //�ڽӱ�Ȩ
	AdjNode(word adj_v, int adj_weight) : adj_v(adj_v), adj_weight(adj_weight) {}
};

//Dinic��
class Dinic {
public:
	/*
	���ش�src��des���������
	@param graph ͼ
	@param nv ������
	@param src Դ
	@param des �յ㣬��
	@return int ��src��des�������
	*/
	int getMaxFlow(vector<AdjNode> * graph, int nv, word src, word des);
private:
	
	/* bfs�����src����ÿ���ɴﶥ�����̾���(��Ȩͼ)����des���ɴ��򷵻�false��*/
	bool bfs(vector<AdjNode> * graph, int nv, word src, word des);

	/* dfsѰ�Ҵ�src��des������·��������·���ϵ���С������*/
	int dfs(vector<AdjNode> * graph, int nv, word src, word des, int min_flow);

	word * dist_;
	queue<word> vqueue_;
};

int Dinic::getMaxFlow(vector<AdjNode>* graph, int nv, word src, word des) {
	dist_ = new word[nv];
	int max_flow = 0, flow;
	while (bfs(graph, nv, src, des)) {
		while (flow = dfs(graph, nv, src, des, INT_MAX)) {
			max_flow += flow;
		}
	}
	free(dist_);
	return max_flow;
}

bool Dinic::bfs(vector<AdjNode>* graph, int nv, word src, word des) {
	fill(dist_, dist_ + nv, WORD_MAX);
	dist_[src] = 0;
	vqueue_.push(src);
	word front_v, adj_v;
	while (!vqueue_.empty()) {
		front_v = vqueue_.front();
		vqueue_.pop();
		for (auto it = graph[front_v].begin(); it != graph[front_v].end(); it++) {
			adj_v = it->adj_v;
			if (dist_[adj_v] == WORD_MAX && it->adj_weight != 0) { //��adj_vû�е��������front_v��adj_v�ı�Ȩ(����)��Ϊ0
				dist_[adj_v] = dist_[front_v] + 1;
				vqueue_.push(adj_v);
			}
		} //for
	} //while
	return dist_[des] != WORD_MAX;
}

int Dinic::dfs(vector<AdjNode>* graph, int nv, word src, word des, int min_flow) {
	if (src == des) {
		return min_flow;
	}
	word adj_v;
	int adj_weight;
	int tmp_flow;
	bool flag;
	for (auto adj_it = graph[src].begin(); adj_it != graph[src].end(); adj_it++) {
		adj_v = adj_it->adj_v;
		adj_weight = adj_it->adj_weight;
		if (adj_weight != 0 && dist_[adj_v] == dist_[src] + 1) { //��src��adj_v�ı�Ȩ(����)��Ϊ0��adj_v��ǰһ��������src
			if (tmp_flow = dfs(graph, nv, adj_v, des, min(min_flow, adj_weight))) { //�ݹ飬�����Ե���des��������:
				min_flow = tmp_flow; //����·���ϵ���С����
				adj_it->adj_weight -= min_flow;
				flag = true;
				for (auto inverse_it = graph[adj_v].begin(); inverse_it != graph[adj_v].end(); inverse_it++) //Ѱ�ҷ���
					if (inverse_it->adj_v == src) {
						inverse_it->adj_weight += min_flow;
						flag = false;
						break;
					}
				if (flag) { //�����ڷ���
					graph[adj_v].push_back(AdjNode(src, min_flow));
				}
				return min_flow; //������С����
			}
		}
	} //for
	return 0; //�Ҳ�������·����
}

int main() {
	int n, m, w;
	word s, t, u, v;
	scanf("%d %d %hd %hd", &n, &m, &s, &t);
	s--; t--;
	vector<AdjNode> * graph = new vector<AdjNode>[n];
	for (size_t i = 0; i < m; i++) {
		scanf("%hd %hd %d", &u, &v, &w);
		u--; v--;
		graph[u].push_back(AdjNode(v, w));
	}
	Dinic dinic;
	int max_flow = dinic.getMaxFlow(graph, n, s, t);
	printf("%d", max_flow);
	for (size_t i = 0; i < n; i++)
		vector<AdjNode>().swap(graph[i]);
	return 0;
}