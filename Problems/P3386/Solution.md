# P3386 ��ģ�塿����ͼƥ��

[ԭ���ַ](https://www.luogu.org/problemnew/show/P3386)

����ͼ���ƥ�䣬�������㷨��ʹ��DFS��BFSʵ�֣��ο�https://www.renfei.org/blog/bipartite-matching.html

��main�����

``` Hungarian * hungarian;```

��һ��ʹ��

```hungarian = new DFS();```

����

```hungarian = new BFS();```

���л��㷨(strategyģʽ��HungarianΪ���崿�麯���ĳ����࣬DFS��BFSΪ����)��

```cpp
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <queue>
using namespace std;

typedef unsigned int Vertex;
#define NO_VERTEX 0xffffffff

class Hungarian {
public:
    /*
    ���ض���ͼ���ƥ��
    @param graph ͼ��ֻ��¼��߶��㵽�ұ߶���ı�
    @param left_num ��߶�����������߶����� 0 ~ left_num - 1
    @param right_num  �ұ߶����������ұ߶����� 0 ~ right_num - 1
    @return size_t ���ƥ������
    */
    virtual size_t maxMatching(vector<Vertex> * graph, size_t left_num, size_t right_num) = 0;

    virtual ~Hungarian() {
    
    }
};

//DFSʵ��
class DFS : public Hungarian {
public:
    virtual size_t maxMatching(vector<Vertex> * graph, size_t left_num, size_t right_num);
private:
    bool dfs(Vertex v);

    vector<Vertex> * graph_;
    Vertex * matching_;
    bool * visited_;
    size_t match_num_;
};

size_t DFS::maxMatching(vector<Vertex>* graph, size_t left_num, size_t right_num) {
    graph_ = graph;
    matching_ = new Vertex[right_num]; //matching_���ұ߶���ƥ�����߶��㣬�����СΪright_num
    fill(matching_, matching_ + right_num, NO_VERTEX);
    visited_ = new bool[right_num]; //visited_����ұ߶���
    match_num_ = 0;
    for (size_t i = 0; i < left_num; i++) {
        fill(visited_, visited_ + right_num, false);
        if (dfs(i)) {
            match_num_++;
        }
    }
    free(matching_);
    free(visited_);
    return match_num_;
}

bool DFS::dfs(Vertex v) {
    Vertex adj_v;
    for (auto it = graph_[v].begin(); it != graph_[v].end(); it++) {
        adj_v = *it;
        if (!visited_[adj_v]) {
            visited_[adj_v] = true;
            if (matching_[adj_v] == NO_VERTEX || dfs(matching_[adj_v])) { //adj_vû��ƥ�����adj_v��ƥ������ҵ�����ƥ��
                matching_[adj_v] = v;
                return true;
            }
        }
    }
    return false;
}

//BFSʵ��
class BFS : public Hungarian {
public:
    virtual size_t maxMatching(vector<Vertex> * graph, size_t left_num, size_t right_num);
private:

    Vertex * left_matching_;
    Vertex * right_matching_;

    queue<Vertex> vqueue_;
    Vertex * pre_;
    bool * visited_;
};

size_t BFS::maxMatching(vector<Vertex>* graph, size_t left_num, size_t right_num) {
    left_matching_ = new Vertex[left_num]; //��߶���ƥ��Ķ���
    fill(left_matching_, left_matching_ + left_num, NO_VERTEX);
    right_matching_ = new Vertex[right_num]; //�ұ߶���ƥ��Ķ���
    fill(right_matching_, right_matching_ + right_num, NO_VERTEX);
    pre_ = new Vertex[left_num]; //BFS����߶����ǰ��
    visited_ = new bool[right_num]; //�ұ߶����Ƿ���ʹ�
    size_t result = 0;
    for (Vertex i = 0; i < left_num; i++) { //������߶���
        fill(visited_, visited_ + right_num, false); //��ʼ���ұ����ж���û�з��ʹ�		
        vqueue_.push(i);
        pre_[i] = NO_VERTEX; // i û��ǰ��
        Vertex front_v, adj_v;
        while (!vqueue_.empty()) {
            front_v = vqueue_.front(); //���ӵĶ���
            vqueue_.pop();
            for (auto it = graph[front_v].begin(); it != graph[front_v].end(); it++) { //�����ڽӵ�
                adj_v = *it; //�ڽӵ�(�ұ߶���)
                if (!visited_[adj_v]) {
                    visited_[adj_v] = true;
                    if (right_matching_[adj_v] != NO_VERTEX) { //adj_v�Ѿ�ƥ��
                        vqueue_.push(right_matching_[adj_v]); //adj_vƥ�䵽�Ķ���(���)���
                        pre_[right_matching_[adj_v]] = front_v; //��¼ǰ��������right_matching_[adj_v]�����ҵ�����ƥ�䣬��front_v��adj_vƥ��
                    }
                    else { //adj_vû��ƥ��
                        Vertex from = front_v, to = adj_v, tmp;
                        while (from != NO_VERTEX) {
                            tmp = left_matching_[from]; //fromԭ����ƥ��(�ұ߶���)
                            left_matching_[from] = to; //from �� to ƥ��
                            right_matching_[to] = from; //from �� to ƥ��
                            //from�ҵ�ƥ�䣬��pre_[from]��fromԭ����ƥ�伴tmpƥ�䣬����from��to�����´�ѭ��,            \
                            ��from֮ǰ��û��ƥ�䣬��pre_[from]ΪNO_VERTEX����һ��ѭ���ͻ��˳�
                            from = pre_[from]; 
                            to = tmp;
                        }
                        while (!vqueue_.empty()) vqueue_.pop(); //��ն���
                        goto NEXT;
                    } //else
                } //if
            } //for
        } //while
    NEXT:
        if (left_matching_[i] != NO_VERTEX) result++;
    } //for
    free(left_matching_);
    free(right_matching_);
    free(pre_);
    free(visited_);
    return result;
}

int main() {
    unsigned int n, m, e;
    scanf("%u %u %u", &n, &m, &e);
    vector<Vertex> * graph = new vector<Vertex>[n];
    Vertex u, v;
    for (size_t i = 0; i < e; i++) {
        scanf("%u %u", &u, &v);
        if (u > n || v > m) continue;
        u--; v--;
        graph[u].push_back(v);
    }
    Hungarian * hungarian;
    //hungarian = new DFS();
    hungarian = new BFS();
    unsigned int max_matching = hungarian->maxMatching(graph, n, m);
    printf("%u", max_matching);
    for (size_t i = 0; i < n; i++)
        vector<Vertex>().swap(graph[i]);
    delete hungarian;
    return 0;
}
```


