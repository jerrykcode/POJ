# P1951 �շ�վ_NOI����2009��ߣ�2��
[ԭ���ַ](https://www.luogu.org/problemnew/show/P1951)

## ��Ŀ����

��ĳ��ңԶ�Ĺ������n�����С����Ϊ1��2��3����,n��

������ҵ������޽���m��˫��Ĺ�·��ÿ����·�������������С�����ĳ����·��������һ�����е���һ�����У���Ҫ����һ�������͡�

����ÿ����һ�����У����ᱻ��ȡһ���ķ��ã����������յ���У������е��շ�վ���ڳ����У��ڳ��м�Ĺ�·��û���κε��շ�վ��

С������Ҫ�����ӳ���u������v��1<=u,v<=n�������ĳ�������װ��s�������͡��ڳ�����ʱ�򣬳������������ģ���������·�ϲ�����͡�

��·�ϣ�ÿ����һ�����У�����Ҫ��һ���ķ��á����ĳ�ν��ķ��ñȽ϶࣬��������ͻ��ú��㡣��������֪���������ܵ���Ŀ�ĵص�ǰ���£������ķ���������һ�������Ƕ��١���������������˵̫���ˣ��������ҵ��˴������㣬���ܰ������

## ���������ʽ

### �����ʽ��

��һ��5����������n��m��u��v��s���ֱ��ʾ��n�����У�m����·���ӳ���u������v���������������Ϊs����

����������n�У�ÿ��1��������fi��ʾ��������i����Ҫ����fiԪ��

�ٽ�������m�У�ÿ��3����������ai��bi��ci��1<=ai,bi<=n��,��ʾ����ai�ͳ���bi֮����һ����·������ӳ���ai������bi�����ߴӳ���bi������ai����Ҫci�������͡�

### �����ʽ��

��һ����������ʾС�콻������һ�ε���Сֵ��

������޷��������v�����-1.

## �����������

### ��������#1�� 

> 4 4 2 3 8  
> 8  
> 5  
> 6  
> 10  
> 2 1 2  
> 2 4 1  
> 1 3 4  
> 3 4 3  

### �������#1�� 

> 8  

## ˵��

�����ݹ�ģ��

* ����60%�����ݣ�����n<=200,m<=10000,s<=200

* ����100%�����ݣ�����n<=10000,m<=50000,s<=1000000000

* ����100%�����ݣ�����ci<=1000000000,fi<=1000000000,��������������������ͬ�ĳ��С�

## ˼·

��[P1462 ͨ���¸�����ĵ�·-Solution](https://github.com/jerrykcode/luogu/blob/master/Problems/P1462/Solution.md)

## ����

```cpp
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
    int v; //�ڽӵ㶥��
    int weight; //�ڽӱ�Ȩ��
    AdjNode(int v, int weight) : v(v), weight(weight) {}
};

//Dijkstra��
class Dijkstra {
public:
    Dijkstra() {}
    ~Dijkstra() {}

    /*
        ����src��des�����·����
        @param graph ͼ
        @param nv ������
        @param src ���(Դ)
        @param des �յ�
        @param f ��Ȩ���飬f[i]Ϊi�ĵ�Ȩ
        @param max_f ���·���ϵĶ��㲻�ܳ���������Ȩ
        @param P_min_dist ָ�룬���ڴ�����̾���
        @return ���ڵ�Ȩ������max_f������£�src�ɵ���des�򷵻�true�����򷵻�false
    */
    bool dijkstra(vector<AdjNode> *graph, int nv, int src, int des, int *f, int max_f, int *p_min_dist);
private:
    //���ȶ���ʹ�õĽṹ��
    struct Node {
        int v;
        LL dist;
        Node(int v, LL dist) : v(v), dist(dist) {}
    };
    struct cmp {
        bool operator() (Node& a, Node& b) {
            return a.dist > b.dist;
        }
    };

    //�����
    LL *dist_;
    bool *collected_;
    priority_queue<Node, vector<Node>, cmp> queue_;
};

bool Dijkstra::dijkstra(vector<AdjNode>* graph, int nv, int src, int des, int *f, int max_f, int * p_min_dist) {
    if (f[src] > max_f || f[des] > max_f) return false;
    dist_ = new LL[nv];
    fill(dist_, dist_ + nv, NO_VALUE);
    collected_ = new bool[nv];
    fill(collected_, collected_ + nv, false);
    dist_[src] = 0;
    queue_.push(Node(src, dist_[src]));
    int min_vertex, adj_vertex, adj_weight;
    LL tmp_dist;
    while (!queue_.empty()) {
        min_vertex = queue_.top().v;
        queue_.pop();
        if (collected_[min_vertex]) continue;
        collected_[min_vertex] = true;
        if (min_vertex == des) {
            while (!queue_.empty()) queue_.pop();
            break;
        }
        for (AdjNode adj_node : graph[min_vertex]) { //�����ڽӵ�
            adj_vertex = adj_node.v;
            adj_weight = adj_node.weight;
            if (!collected_[adj_vertex] && f[adj_vertex] <= max_f) {
                tmp_dist = dist_[min_vertex] + adj_weight;
                if (tmp_dist < dist_[adj_vertex] || dist_[adj_vertex] == NO_VALUE) {
                    dist_[adj_vertex] = tmp_dist;
                    queue_.push(Node(adj_vertex, dist_[adj_vertex]));
                }
            }
        }
    } //while
    *p_min_dist = dist_[des];
    free(dist_);
    bool result = collected_[des];
    free(collected_);
    return result;
}

/* ���ֲ��ҡ�*/
int binarySearch(int *arr, int n, int val) {
    int left = 0, right = n - 1, mid;
    while (left <= right) {
        mid = (left + right) / 2;
        if (arr[mid] == val) return mid;
        else if (arr[mid] < val) left = mid + 1;
        else right = mid - 1;
    }
    return NO_VALUE;
}

int main() {
    int n, m, u, v, s;
    scanf("%d %d %d %d %d", &n, &m, &u, &v, &s);	
    u--; v--; //��Ϊ��0��ʼ���
    vector<AdjNode> *graph = new vector<AdjNode>[n];
    int *f = new int[n];
    for (int i = 0; i < n; i++)
        scanf("%d", f + i); //�����Ȩ
    int *f_sorted = new int[n];
    memcpy(f_sorted, f, n * sizeof(int));
    sort(f_sorted, f_sorted + n); //�����Ȩ
    int a, b, c;
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &a, &b, &c);
        a--; b--;
        graph[a].push_back(AdjNode(b, c));
        graph[b].push_back(AdjNode(a, c));
    }
    Dijkstra dijkstra;
    int min_dist;
    int left = max(binarySearch(f_sorted, n, f[u]), binarySearch(f_sorted, n, f[v])); //��Ȩһ�����ڵ���src��des�ĵ�Ȩ
    int right = n - 1, mid, last = NO_VALUE;
    //����
    while (left <= right) {
        mid = (left + right) / 2;
        if (dijkstra.dijkstra(graph, n, u, v, f, f_sorted[mid], &min_dist) && min_dist < s) {
            last = mid;
            right = mid - 1;
        }
        else left = mid + 1;
    }
    last == NO_VALUE ? printf("-1") : printf("%d", f_sorted[last]);
    free(f);
    free(f_sorted);
    for (int i = 0; i < n; i++)
        vector<AdjNode>().swap(graph[i]);
    return 0;
}
```