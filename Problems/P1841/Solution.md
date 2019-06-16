# P1841 [JSOI2007]��Ҫ�ĳ���
[ԭ���ַ](https://www.luogu.org/problemnew/show/P1841)

## ��Ŀ����

�μ�jsoi����Ӫ��ͬѧ������֣������Ϻ�У����·�ض���ԭ��ͨ��������ĵ�·������ȥ��·�̱�ԭ�������˽�һ�����ʳ����ǰʩ����ȻҲ�ض���ԭ��ͨ��������ĵ�·��ȴû��ʹ·�����ӣ���Ϊ�����ҵ�ͬ�����ȵ�·���������ʵ������Ĺؼ����ڣ�·�ضϵĵط��ǽ�ͨҪ�㡣

ͬ�������Ҳ�����ڳ��м�Ľ�ͨ�С�ĳЩ��������������⣬���ܻ����������ܶ���еĽ�ͨ���㡣��һЩ������Ӱ�첻����ĳ��еĽ�ͨ��jsoi����Ӫ��ͬѧ��������һ����Ȥ�����⣬���Ǿ����о�������⡣

������Ϊ�����ĳ�������Ҫ�ģ����һ������c���ƻ��󣬴���������ͬ�ĳ���a��b��a, b��������c����a��b����̾��������ˣ���ͨ���������c����Ҫ�ġ�

jsoi����Ӫ��ͬѧ�����һ�Ž����齻�����ǵĳ��м佻ͨͼ������ϣ�����ҳ�������Ҫ�ĳ��С����ھ����������������⡣

## ���������ʽ

### �����ʽ��

��һ����������N,M,NΪ��������MΪ��·��

������M�У�ÿ��������������ʾ��������֮�������ߣ��Լ�֮���·�ĳ���

### �����ʽ��

һ�У�����������������ɵ�������ʾ��Ҫ�ĳ��С�

## �����������

### ��������#1�� 

> 4 4  
> 1 2 1  
> 2 3 1  
> 4 1 2  
> 4 3 2  

### �������#1�� 

> 2  

## ˵��

30%�����ݣ�N <= 20��

60%�����ݣ�N <= 100��

100%�����ݣ�N <= 200��M <= N*(N - 1)/2��0 < c <= 10000��c��·�ĳ��ȡ�

��֤�������رߺ��Ի�

��л@����� ��@qq2477259579 �ṩ����

���û�е�Ļ���Ҫ���һ��

��No important cities.��

ȥ������


## ˼·

�Զ���src������ΪԴ����dijkstra�����ڳ�src������ⶥ��v�����Եõ�src��v����̾��룬�Լ�src��v�����·����v��ǰ������(�����·����v��ǰһ������)��Ҳ����֪��ǰ���Ƿ�Ψһ����ǰ��Ψһ�����ʾ����ǰ������v��src��v��Ψһ���·������ôֻҪɾ��ǰ�����㣬src��v����̾���һ������(����src�޷�����v)��Ҳ����˵v��Ψһǰ������Ҫ���С���src����v�����·����v��ǰ��(��һ������)��Ψһ������ɾ��v�Ŀ��ܵ�ǰ���е�һ����v������ͨ������ǰ�����������Щǰ����һ������Ҫ���С�

������src������ж��㣬����ǰ��Ψһ(�Ҳ���src)����ô��ǰ������Ҫ���С�

ע����v��Ψһǰ����src����ɾ��Ψһǰ��src��src�Ѳ����ڣ���ôsrc��v����̾����������壬����src���ܱ��ж�Ϊ��Ҫ���С�

��ÿһ������ֱ���Ϊsrc����dijkstra�����Եõ����е���Ҫ���С�

����dijkstra���ж�ǰ���Ƿ�Ψһ������¼Ψһǰ����

* �����ȶ����е����Ķ�����Ϊtop_v����ǰ����src�ľ�������С��

* top_v���ڽӵ���Ϊadj_v

* ��src��top_v�ľ������top_v��adj_v�ľ���`С��`֮ǰsrc��adj_v����̾��룬��

	* ����top_v����adj_vΪĿǰsrc����adj_v��Ψһ���·��������top_vΪadj_v��Ψһǰ��

* ��src��top_v�ľ������top_v��adj_v�ľ���`����`֮ǰsrc��adj_v����̾��룬��

	* adj_v���Ծ���top_v�����Ҳ������֮ǰ�����·������ʱadj_v�ж��ǰ��(����Ҫ��¼ǰ����ֻҪ��¼adj_v�ж��ǰ������)


## ����

```cpp
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
```
