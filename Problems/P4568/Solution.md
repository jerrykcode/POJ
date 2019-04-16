# P4568 [JLOI2011]����·��
[ԭ���ַ](https://www.luogu.org/problemnew/show/P4568)

��Ŀ����
----

Alice��Bob����Ҫ�˷ɻ����У�����ѡ����һ����Ա��˵ĺ��չ�˾���ú��չ�˾һ����nn����������ҵ������Щ���зֱ���Ϊ00��n-1n-1��һ����mm�ֺ��ߣ�ÿ�ֺ��������������У����Һ�����һ���ļ۸�

Alice��Bob����Ҫ��һ���������ź��ߵ�����һ�����У�;�п��Խ���ת�������չ�˾�������������Ҳ�Ƴ��Żݣ����ǿ�����������kk�ֺ����ϴ�˷ɻ�����ôAlice��Bob��γ������ٻ��Ѷ��٣�

���������ʽ
------

�����ʽ��

���ݵĵ�һ��������������n,m,kn,m,k���ֱ��ʾ������������������ѳ���������\
�ڶ���������������s,ts,t���ֱ��ʾ���ǳ��е������б�ź��յ���б�š�\
��������m�У�ÿ������������a,b,ca,b,c����ʾ����һ�ֺ��ߣ��ܴӳ���aa�������bb����ӳ���bb�������aa���۸�Ϊcc��

�����ʽ��

ֻ��һ�У�����һ��������Ϊ���ٻ��ѡ�

�����������
------

��������#1��?����

5 6 1
0 4
0 1 5
1 2 5
2 3 5
3 4 5
2 3 3
0 2 100

�������#1��?����

8

˵��
--

����30%������,2 \le n \le 50,1 \le m \le 300,k=02��n��50,1��m��300,k=0;\
����50%������,2 \le n \le 600,1 \le m \le 6000,0 \le k \le 12��n��600,1��m��6000,0��k��1;\
����100%������,2 \le n \le 10000,1 \le m \le 50000,0 \le k \le 102��n��10000,1��m��50000,0��k��10,0 \le s,t<n,0 \le a,b<n,a\neq b,0 \le c \le 10000��s,t<n,0��a,b<n,a��b,0��c��1000

2018.12.10 ����һ�� hack ����


## ˼·

�ֲ�ͼ���·ģ��

## ����

```cpp
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <queue>
using namespace std;

#define NO_VALUE -1

//�ڽӵ�ṹ��
struct AdjNode {
    int v; //�ڽӵ�
    int weight; //�ڽӱ�Ȩ��
    AdjNode(int v, int weight) : v(v), weight(weight) {}
};

//Dijkstra��
class Dijkstra {
public:
    /* �������·��
     @param graph �ڽӱ��ʾ��ͼ
     @param nv ������
     @param src Դ
     @param des �յ�
     @param max_free_time �����Ѵ�������ҪС��ͼ�ı���
     @return Դ���յ㲻����max_free_time����ѵ���̾���
     */
    int dijkstra(vector<AdjNode>* graph, int nv, int src, int des, int max_free_time);
private:
    //���ȶ���ʹ�õĽṹ��
    struct PriorityNode {
        int v;
        int dist;
        int free_time; //����vʱʹ����ѵĴ��������ֲ�ͼ�еĲ�
        PriorityNode(int v, int dist, int free_time) : v(v), dist(dist), free_time(free_time) {}
    };
    struct cmp {
        bool operator () (PriorityNode& a, PriorityNode& b) {
            return a.dist > b.dist;
        }
    };

    //�����
    int **dist_; //dist_[i][j]Ϊ��src��i������j����ѵ���̾���
    bool **collected_; // collected_[i][j]Ϊtrue��src��i������j����ѵ���;�����ȷ��
    priority_queue<PriorityNode, vector<PriorityNode>, cmp> queue_;
};

int Dijkstra::dijkstra(vector<AdjNode>* graph, int nv, int src, int des, int max_free_time) {
    dist_ = new int*[nv];
    collected_ = new bool*[nv];
    for (int i = 0; i < nv; i++) {
        //dist_[i][j]Ϊ��src��i������j����ѵ���̾���
        dist_[i] = new int[max_free_time + 1];
        fill(dist_[i], dist_[i] + max_free_time + 1, NO_VALUE);
        //collected_[i][j]Ϊtrue��src��i������j����ѵ���;�����ȷ��
        collected_[i] = new bool[max_free_time + 1];
        fill(collected_[i], collected_[i] + max_free_time + 1, false);
    }	
    dist_[src][0] = 0; //src��src��0����ѣ�����Ϊ0
    queue_.push(PriorityNode(src, 0, 0));
    int min_v, min_free_time, min_dist, adj_v, adj_weight, tmp_dist;
    while (!queue_.empty()) {
        //������dist��С�ĳ�����
        min_v = queue_.top().v; 
        min_dist = queue_.top().dist;
        min_free_time = queue_.top().free_time;
        queue_.pop();
        if (collected_[min_v][min_free_time]) continue;
        collected_[min_v][min_free_time] = true;
        if (min_v == des && min_free_time == max_free_time) {
            while (!queue_.empty()) queue_.pop();
            break;
        }
        for (auto it = graph[min_v].begin(); it != graph[min_v].end(); it++) { 
            //�����ڽӵ�
            adj_v = it->v;
            adj_weight = it->weight;			
            if (!collected_[adj_v][min_free_time]) {
                tmp_dist = min_dist + adj_weight; //��min_v��adj_v�����
                if (tmp_dist < dist_[adj_v][min_free_time] || dist_[adj_v][min_free_time] == NO_VALUE) {
                    dist_[adj_v][min_free_time] = tmp_dist;
                    queue_.push(PriorityNode(adj_v, tmp_dist, min_free_time));
                }
            }
            if (min_free_time < max_free_time && !collected_[adj_v][min_free_time + 1]) {
                tmp_dist = min_dist; //��min_v��adj_v���
                if (tmp_dist < dist_[adj_v][min_free_time + 1] || dist_[adj_v][min_free_time + 1] == NO_VALUE) { //��Ѵ�����1
                    dist_[adj_v][min_free_time + 1] = tmp_dist;
                    queue_.push(PriorityNode(adj_v, tmp_dist, min_free_time + 1));
                }
            }
        } //for
    } //while
    int result = dist_[des][max_free_time];
    for (int i = 0; i < nv; i++) {
        free(dist_[i]);
        free(collected_[i]);
    }
    free(dist_);
    free(collected_);
    return result;
}

int main() {
    int n, m, k, s, t;
    scanf("%d %d %d", &n, &m, &k);
    scanf("%d %d", &s, &t);
    vector<AdjNode> *graph = new vector<AdjNode>[n];
    int a, b, c;
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &a, &b, &c);
        graph[a].push_back(AdjNode(b, c));
        graph[b].push_back(AdjNode(a, c));
    }
    Dijkstra dijkstra;
    printf("%d", dijkstra.dijkstra(graph, n, s, t, min(m, k))); //ע��m < k�����
    for (int i = 0; i < n; i++)
        vector<AdjNode>().swap(graph[i]);
    return 0;
}
```