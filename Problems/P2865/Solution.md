# P2865 [USACO06NOV]·��Roadblocks
[ԭ���ַ](https://www.luogu.org/problemnew/show/P2865)


��Ŀ����
----

Bessie has moved to a small farm and sometimes enjoys returning to visit one of her best friends. She does not want to get to her old home too quickly, because she likes the scenery along the way. She has decided to take the second-shortest rather than the shortest path. She knows there must be some second-shortest path.

The countryside consists of R (1 �� R �� 100,000) bidirectional roads, each linking two of the N (1 �� N �� 5000) intersections, conveniently numbered 1..N. Bessie starts at intersection 1, and her friend (the destination) is at intersection N.

The second-shortest path may share roads with any of the shortest paths, and it may backtrack i.e., use the same road or intersection more than once. The second-shortest path is the shortest path whose length is longer than the shortest path(s) (i.e., if two or more shortest paths exist, the second-shortest path is the one whose length is longer than those but no longer than any other path).

����ѼҰᵽ��һ��Сũ�������������ص�FJ��ũ��ȥ�ݷ��������ѡ������ϲ��·�ߵķ羰��������ô��ؽ���������;��������ÿ�λ�ũ��������ѡ��ڶ��̵�·����������������ϰ�ߵ�������ѡ�����·�� �������ڵ������R(1<=R<=100,000)��˫���·��ÿ��·�����������е�N(1<=N<=5000)��ũ���е�ĳ�����������ס��ũ��1�����������Ǿ�ס��ũ��N��������ÿ�����е�Ŀ�ĵأ��� ����ѡ��ĵڶ��̵�·���У����԰����κ�һ�������·�г��ֵĵ�·�����ң�һ��·�����ظ��߶�Ρ���Ȼ�����ڶ���·�ĳ��ȱ����ϸ�������·�������ж������ĳ��ȣ������ĳ��ȱ��벻�������г����·���·���ĳ��ȡ�

���������ʽ
------

�����ʽ��

Line 1: Two space-separated integers: N and R

Lines 2..R+1: Each line contains three space-separated integers: A, B, and D that describe a road that connects intersections A and B and has length D (1 �� D �� 5000)

�����ʽ��

Line 1: The length of the second shortest path between node 1 and node N

�����������
------

��������#1��?����

> 4 4  
> 1 2 100  
> 2 4 200  
> 2 3 250  
> 3 4 100  

�������#1��?����

> 450  

˵��
--

Two routes: 1 -> 2 -> 4 (length 100+200=300) and 1 -> 2 -> 3 -> 4 (length 100+250+100=450)

## ˼·

A*��ζ�·

## ����

```cpp
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <queue>
using namespace std;

#define NO_VALUE -1

typedef unsigned short Vertex; //����

//�ڽӵ�ṹ��
struct AdjNode {
    Vertex adj_v; //�ڽӵ�
    int adj_weight; //�ڽӱ�Ȩ��
    AdjNode(Vertex adj_v, int adj_weight) : adj_v(adj_v), adj_weight(adj_weight) {}
};

//����ζ�·����
class SecondShortestPath {
public:
    /* ����ζ�·��
        @param graph ͼ
        @param nv ������
        @param src Դ
        @param des �յ�
        @return int �ζ�·����
    */
    int getSecondShortestPath(vector<AdjNode> * graph, int nv, int src, int des);
private:
    /* ����Դ��ÿ���������̾��롣
        @param graph ͼ
        @param nv ������
        @param src Դ
        @param dist �洢��̾��������(����)
        @return void
    */
    void dijkstra(vector<AdjNode> * graph, int nv, int src, int *dist);

    /* A*����ζ�·��
        @param graph ͼ
        @param nv ������
        @param src Դ
        @param des �յ�
        @param h ��ֵ����
         @return int �ζ�·����
    */
    int astar(vector<AdjNode>* graph, int nv, int src, int des, int *h);

    //���ȶ���ʹ�õĽṹ��
    //dijkstra���ȶ���ʹ��
    struct PriorityNode {
        Vertex v;
        int dist;
        PriorityNode(Vertex v, int dist) : v(v), dist(dist) {}
    };

    //A*���ȶ���ʹ��
    struct AStarNode : PriorityNode {
        //PriorityNode::dist Ϊf
        int g;
        AStarNode(Vertex v, int g, int f) : PriorityNode(v, f), g(g) {}
    };

    struct cmp {
        bool operator () (PriorityNode& a, PriorityNode& b) {
            return a.dist > b.dist;
        }
    };	
};

int SecondShortestPath::getSecondShortestPath(vector<AdjNode>* graph, int nv, int src, int des) {
    int *h = new int[nv];
    //dijkstra����des��ÿ���������̾��룬��Ϊh
    dijkstra(graph, nv, des, h);
    //����ζ�·
    int result = astar(graph, nv, src, des, h);
    free(h);
    return result;
}

void SecondShortestPath::dijkstra(vector<AdjNode>* graph, int nv, int src, int *dist) {
    fill(dist, dist + nv, NO_VALUE);
    bool *collected = new bool[nv];
    fill(collected, collected + nv, false);
    dist[src] = 0;
    priority_queue<PriorityNode, vector<PriorityNode>, cmp> q;
    q.push(PriorityNode(src, 0));
    Vertex min_v, adj_v;
    int adj_weight, tmp_dist;
    while (!q.empty()) {
        min_v = q.top().v;
        q.pop();
        if (collected[min_v]) continue;
        collected[min_v] = true;
        for (auto it = graph[min_v].begin(); it != graph[min_v].end(); it++) { 
            //�����ڽӵ�
            adj_v = it->adj_v;
            if (!collected[adj_v]) {
                adj_weight = it->adj_weight;
                tmp_dist = dist[min_v] + adj_weight;
                if (tmp_dist < dist[adj_v] || dist[adj_v] == NO_VALUE) {
                    dist[adj_v] = tmp_dist;
                    q.push(PriorityNode(adj_v, tmp_dist));
                }
            }
        } //for
    } //while
    free(collected);
}

int SecondShortestPath::astar(vector<AdjNode>* graph, int nv, int src, int des, int *h) {
    priority_queue<AStarNode, vector<AStarNode>, cmp> q;
    q.push(AStarNode(src, 0, h[src]));
    Vertex min_v, adj_v;
    int min_g, tmp_g, count = 0;
    while (!q.empty()) {
        min_v = q.top().v;
        min_g = q.top().g;
        q.pop();
        if (min_v == des) {
            if (++count == 2) {
                //�ڶ��ε���des
                while (!q.empty()) q.pop();
                return min_g;
            }
        }
        for (auto it = graph[min_v].begin(); it != graph[min_v].end(); it++) {
            //�����ڽӵ�
            adj_v = it->adj_v;
            tmp_g = min_g + it->adj_weight;
            q.push(AStarNode(adj_v, tmp_g, tmp_g + h[adj_v]));
        }
    } //while
    return NO_VALUE;
}

int main() {
    int n, r;
    scanf("%d %d", &n, &r);
    vector<AdjNode> *graph = new vector<AdjNode>[n];
    for (int i = 0, a, b, d; i < r; i++) {
        scanf("%d %d %d", &a, &b, &d);
        a--; b--;
        graph[a].push_back(AdjNode(b, d));
        graph[b].push_back(AdjNode(a, d));
    }
    SecondShortestPath ssp;
    printf("%d", ssp.getSecondShortestPath(graph, n, 0, n - 1));
    for (int i = 0; i < n; i++)
        vector<AdjNode>().swap(graph[i]);
    return 0;
}
```