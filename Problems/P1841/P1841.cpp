#include <cstdio>
#include <cstdlib>
#include <vector>
#include <queue>
using namespace std;

typedef unsigned char vertex_t; //��������(���붥�������200)
typedef unsigned short weight_t; //��Ȩ������(�����Ȩ���10000)
typedef unsigned int dist_t; //��������(�����Ȩ���10000, ����������֮��ľ�����ܳ���65535)

//���Ϳ��Դ洢�����ֵ
#define VERTEX_T_INF 0xff
#define DIST_T_INF 0xffffffff

//�ڽӵ�ṹ��
struct AdjNode {
	vertex_t adj_v; //�ڽӶ���
	weight_t adj_weight; //�ڽӱ�Ȩ��
	AdjNode(vertex_t adj_v, weight_t adj_weight) : adj_v(adj_v), adj_weight(adj_weight) {}
};

//��Ҫ������
class ImportantCities {
public:
	/* ��ǳ���Ҫ���� 
	 @param graph ͼ
	 @param n ͼ��������
	 @param is_important_city ����(����)����Ƕ����Ƿ�Ϊ��Ҫ����
	 @retrun void
	 */
	void importantCities(vector<AdjNode> * graph, size_t n, bool * is_important_city);
private:
	//dijkstra�����ȶ���ʹ�õĽṹ��
	struct PriorityNode {
		vertex_t v;
		dist_t dist;
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
	dist_t * dist_; //��̾���
	vertex_t * pre_; //ǰ������
	bool * collected_; //��Ƕ����Ƿ���¼
	priority_queue<PriorityNode, vector<PriorityNode>, PriorityNode::cmp> pq_; //���ȶ���
private:
	static const vertex_t multi_previous = VERTEX_T_INF; //��ʾ�ж��ǰ��
};

void ImportantCities::importantCities(vector<AdjNode>* graph, size_t n, bool * is_important_city) {
	fill(is_important_city, is_important_city + n, false); //��ʼ��
	dist_ = new dist_t[n];
	pre_ = new vertex_t[n];
	collected_ = new bool[n];
	vertex_t src;	
	for (size_t i = 0; i < n; i++) { //��������
		src = (vertex_t)i; //�Զ��� i ��ΪԴ����dijkstra
		fill(dist_, dist_ + n, DIST_T_INF); //��ʼ��
		fill(collected_, collected_ + n, false); //��ʼ��
		dist_[src] = 0;
		pq_.push(PriorityNode(src, 0));
		vertex_t top_v, adj_v;
		dist_t tmp_dist;
		while (!pq_.empty()) {
			top_v = pq_.top().v; //top_v�����У��ǵ�ǰ��src����̾�������С��
			pq_.pop();
			if (collected_[top_v]) continue;
			collected_[top_v] = true;
			for (auto it = graph[top_v].begin(); it != graph[top_v].end(); it++) { //�����ڽӵ�
				adj_v = it->adj_v; //�ڽӶ���
				if (!collected_[adj_v]) {
					tmp_dist = dist_[top_v] + (dist_t)it->adj_weight; //����top_v����adj_v�ľ���
					if (tmp_dist < dist_[adj_v]) { //������top_v����adj_v���Լ�С����
						dist_[adj_v] = tmp_dist; //����
						pre_[adj_v] = top_v; //����top_vΪadj_v��ǰ������ʱsrc����top_v����adj_v��src��adj_v�����·��������top_v��adj_v��Ψһ��ǰ��
						pq_.push(PriorityNode(adj_v, tmp_dist));
					}
					else if (tmp_dist == dist_[adj_v]) { //������top_v����adj_v��֮ǰ����adj_v����̾�����ͬ
						//��ʱ��src����adj_v�����·���ж��������Ծ���top_vҲ����ʹ��������·�������Դ�ʱadj_v��ǰ����Ψһ���ʼ�¼pre_[adj_v]Ϊmulti_previous
						pre_[adj_v] = multi_previous; //multi_previous��ʾadj_v��ǰ���ж��
					}
				}
			} //for
		} //while (dijkstra)
		for (size_t j = 0; j < n; j++)
			if (j != i && pre_[j] != multi_previous && pre_[j] != src) {
				//��j��ǰ��Ψһ������������Ψһǰ������ɾ����src��j����̾���һ�����󣬹�����Ψһǰ��Ϊ��Ҫ����
				//ע��j��Ψһǰ��Ϊsrc������£�src������Ҫ���У���Ϊ��ɾ��src��src��j����̾�����������
				is_important_city[pre_[j]] = true; //���jΪ��Ҫ����
			}
	} //for
	//�ͷ��ڴ�
	free(dist_);
	free(pre_);
	free(collected_);
}

int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	vector<AdjNode> * graph = new vector<AdjNode>[n];
	int v, w, c;
	//�����
	for (size_t i = 0; i < m; i++) {
		scanf("%d %d %d", &v, &w, &c);
		v--; w--; //�����Ϊ��0���
		graph[v].push_back(AdjNode((vertex_t)w, (weight_t)c));
		graph[w].push_back(AdjNode((vertex_t)v, (weight_t)c));
	}
	ImportantCities important_cities;
	bool * is_important_city = new bool[n];
	important_cities.importantCities(graph, n, is_important_city);
	bool flag = true;
	for (size_t i = 0; i < n; i++) 
		if (is_important_city[i]) { //������Ҫ����
			flag = false;
			printf("%d ", i + 1);
		}	
	if (flag) printf("No important cities.");
	for (size_t i = 0; i < n; i++)
		vector<AdjNode>().swap(graph[i]);
	free(is_important_city);
	return 0;
}