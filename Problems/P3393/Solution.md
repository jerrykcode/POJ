��Ŀ����
----

[ԭ���ַ](https://www.luogu.org/problemnew/show/P3393)

Сaס�Ĺ��ұ���ʬ�����ˣ�Сa�������뵽�ù�Ψһ�Ĺ��ʿո��ӳ�������ҡ�

�ù���N�����У�����֮���е�·������һ����M��˫���·����֤û���Ի����رߡ�

K�������Ѿ�����ʬ�����ˣ����óȻ����ͻᱻ��ȾTAT...���Բ��ܽ��롣������������о���������S����·�Ϳ��Ե���ı�ĳ��У�����Σ�ճ��С����仰˵ֻҪĳ��û�б�ռ���е�ĳ����ռ���в�����s���룬����Σ�ա�

Сaס��1�ų��У����ʿո���N�ų��У�����������û�б����ԡ�Сa��ÿһ�ε�·����һ������ֱ�ӵ�������һ�����У��û�һ�������죬��������Ҫס�õꡣ��ȫ�ĵĳ����ùݱȽϱ���ҪPԪ������Σ�յĳ��У��ù�Ҫ���а�����ʩ�����Ի���ΪQԪ������Σ�յĳ��е�ס�޼۸�һ������ȫ�ĳ���Ҳ�ǡ���1�ų��к�N���У�����Ҫס�ꡣ

Сa�ȽϿ��ţ�������ϣ��֪����1�ų��е�N�ų�������Ҫ����С���ѡ�

�������ݱ�֤����·�������Գɹ����롣�������ݱ�֤����������ɹ���

���������ʽ
------

**�����ʽ��**

��һ��4������(N,M,K,S)

�ڶ���2������(P,Q)

������K�У�ci����ʾ��ʬ��ռ�ĳ���

������M�У�ai,bi����ʾһ�������

**�����ʽ��**

һ��������ʾ��ͻ���

�����������
------

**��������#1��** 

13 21 1 1  
1000 6000  
7  
1 2  
3 7  
2 4  
5 8  
8 9  
2 5  
3 4  
4 7  
9 10  
10 11  
5 9  
7 12  
3 6  
4 5  
1 3  
11 12  
6 7  
8 11  
6 13  
7 8  
12 13  

**�������#1��** 

11000  

˵��
--

![](https://cdn.luogu.org/upload/pic/2681.png)

����20%���ݣ�N<=50

����100%���ݣ�2 �Q N �Q 100000, 1 �Q M �Q 200000, 0 �Q K �Q N - 2, 0 �Q S �Q 100000

1 �Q P �� Q �Q 100000


## ˼·

�������Ȩ������Ȩdijkstra����

### �����Ȩ

* ��ͨ���� ��ȨΪp

* Σ�ճ��� ��ȨΪq

* ��ռ����� ���ɴ�޵�Ȩ

* �����յ� ��ȨΪ0

�ؼ����ڼ������Щ��Σ�ճ��У�����ռ�������Χs���ڵĳ���

������Ҫ��ÿһ����ռ����н���һ��BFS��

���б�ռ������Ƚ����У���last��¼���һ�������еĶ��㣬tail��Ϊ��һ������һ������

�����б�ռ�����Ϊ��0�㣬���ǿ�ʼ������Χ��һ�㣬last��tail��ֵ��ͬ��Ϊ���б�ռ����������һ�������е�(lastΪ�������еĶ��㣬tailΪ��һ�㼴��0�����һ������)��while���в�����һ����������У����������չ���Ķ����Ϊ��һ��Ķ��㣬���Ƕ������У�����lastΪ�����е����һ��������ǰ�����еĶ���Ϊtail�����0��Ķ���չ��ϣ�׼����ʼ����һ��Ķ�������в���չ������tailΪlast����¼��������������sʱ����ѭ����


```
       6
       |
       |
       |
2---0---1---4---7---8---9
       |            |     |
       |            |     |
       |            |     |
      3           5   10
```

��ͼ����0��1��ռ�죬s=2���� 2 3 4 5 6 7 ΪΣ�ն���


||last|tail|����|Σ�ն���(��Σ�ն���ĵ�Ȩ��Ϊq)|����|			
|---|---|---|---|---|---|		
|0��1������|1|1|0 1|-|0|
|0�����У�2��3��6������|6|1|1 2 3 6|2 3 6|0|
|1�����У�4������|4|1|2 3 6 4|2 3 4 6|0|
|����1==tail������|4|4|2 3 6 4|2 3 4 6|1|
|2������|4|4|3 6 4|2 3 4 6|1|
|3������|4|4|6 4|2 3 4 6|1|
|6������|4|4|4|2 3 4 6|1|
|4�����У�5��7������|7|4|5 7|2 3 4 5 6 7|1|
|����4==tail������|7|7|5 7|2 3 4 5 6 7|2|
|�����2�㣬����|||||||


##### ע�� BFS�п�����չ�������յ㣬���������յ�ĵ�Ȩ��Ϊq��������������ǵĵ�ȨӦ��Ϊ0��[�ο�](https://www.luogu.org/discuss/show/27571)

### �������·

* ����Ȩ���㣬��(a, b)�ı�ȨΪb�ĵ�Ȩ��(b, a)�ı�ȨΪa�ĵ�Ȩ��

* ��¼ͼʱ������Ҫ��¼����ı�Ȩ��dijkstraʱ�������min_v��չ�ڽӵ㣬�ڽӵ���Ϊadj_v����min_v��adj_v�ı�Ȩ��adj_v�ĵ�Ȩ��

* ���ڱ�ռ��Ķ��㲻�ܱ���չ

�������ͨdijkstra������

## C++����

```cpp
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
```




