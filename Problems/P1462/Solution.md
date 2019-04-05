# P1462 ͨ���¸�����ĵ�·
[ԭ���ַ](https://www.luogu.org/problemnew/show/P1462)

## ��Ŀ����

�ڰ�����˹��½����һλ��������Ŷ��������ʿ�����ǲ�����м�����

��һ�������������Լ���Ȼ�������˵����Ǳ����

�ڱ��ڶ����˵�ʿ���������������ӻ��Լ��ļ���¸�����

## ��Ŀ����

�ڰ�����˹����n�����С����Ϊ1,2,3,...,n��

����֮����m��˫��Ĺ�·���������������У���ĳ�����е���һ�����У����⵽���˵Ĺ�����������ʧһ����Ѫ����

ÿ�ξ���һ�����У����ᱻ��ȡһ���Ĺ�·�ѣ����������յ㣩��·�ϲ�û���շ�վ��

����1Ϊ����ǣ�nΪ�¸����꣬������Ѫ�����Ϊb������ʱ����Ѫ�������ġ�

����Ŷ��ϣ�����ܶ�Ǯ������֪�����ڿ��Ե���¸����������£��������������г���������һ����ȡ�ķ��õ���Сֵ�Ƕ��١�

## ���������ʽ

### �����ʽ��

��һ��3����������n��m��b���ֱ��ʾ��n�����У�m����·������Ŷ��Ѫ��Ϊb��

��������n�У�ÿ��1����������fi����ʾ��������i����Ҫ����fiԪ��

�ٽ�������m�У�ÿ��3����������ai��bi��ci(1<=ai��bi<=n)����ʾ����ai�ͳ���bi֮����һ����·������ӳ���ai������bi�����ߴӳ���bi������ai������ʧci��Ѫ����

### �����ʽ��

��һ����������ʾ����Ŷ��������һ�ε���Сֵ��

������޷�����¸����꣬���AFK��

## �����������

### ��������#1�� 

> 4 4 8  
> 8  
> 5  
> 6  
> 10  
> 2 1 2  
> 2 4 1  
> 1 3 4  
> 3 4 3  

### �������#1�� 

> 10  


## ˵��

* ����60%�����ݣ�����n <= 200��m <= 10000��b <= 200

* ����100%�����ݣ�����n <= 10000��m <= 50000��b <= 1000000000

* ����100%�����ݣ�����ci <= 1000000000��fi <= 1000000000����������������������ͬ�ĳ��С�

## ˼·

[�ο�](https://www.luogu.org/problemnew/solution/P1462)

����һ��Դ���յ��·����·������С��b��ͬʱҪ��·���ϵĶ�������Ȩ��ԽСԽ�á������������С�ĵ�Ȩ����������һ��Ȩ��f�����Լ���Դ���յ�����·��(·���ϵĶ������Ȩ�ز�����f)����Դ���Ե����յ㣬��������·��С��b����ôf���Լ�����С��������Ҫ����f�����Զ���ȷ��f��ֵ��

����f��Ȼ���ڵ��������յ�ĵ�Ȩ�����Զ��ֵ����leftΪԴ���յ��Ȩ�صĽϴ�ֵ�����Ҷ�rightΪ���ж��������Ȩ����ԭ��Ȩ����Ϊf�������õ�f_sorted���飬��max(f[src], f[des])��f_sorted�е�λ�ü�Ϊleft��n - 1Ϊright����f_sorted���ּ��ɡ�

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
```