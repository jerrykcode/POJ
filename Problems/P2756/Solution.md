# P2756 ����Ա��Է�������

[ԭ���ַ](https://www.luogu.org/problemnew/show/P2756)

## ��Ŀ����

�ڶ��������սʱ��..

## ��Ŀ����

Ӣ���ʼҿվ������ݹ���ļ�˴����⼮����Ա���ɻʼҿվ��ɳ���ÿһ�ܷɻ�����Ҫ�䱸�ں��м��ܺ��������ܻ�����ϵ�2 ������Ա������1 ����Ӣ������Ա����1�����⼮����Ա�����ڶ�ķ���Ա�У�ÿһ���⼮����Ա������������������Ӣ������Ա�ܺõ���ϡ����ѡ����Է��еķ���Ա����ʹһ���ɳ����ķɻ������ڸ������⼮����Ա��Ӣ������Ա���������������һ���㷨�ҳ���ѷ���Ա��Է�����ʹ�ʼҿվ�һ�����ɳ����ķɻ���

���ڸ������⼮����Ա��Ӣ������Ա��������������ҳ�һ����ѷ���Ա��Է�����ʹ�ʼҿվ�һ�����ɳ����ķɻ���

## ���������ʽ

### �����ʽ��

�� 1 ���� 2 �������� m �� n��n �ǻʼҿվ��ķ���Ա����(n<100)��m ���⼮����Ա��(m<=n)���⼮����Ա���Ϊ 1~m��Ӣ������Ա���Ϊ m+1~n��

������ÿ���� 2 �������� i �� j����ʾ�⼮����Ա i ���Ժ�Ӣ������Ա j ��ϡ������ 2��-1 ������

### �����ʽ��

�� 1 ������ѷ���Ա��Է���һ�����ɳ������ķɻ��� M�������� M ������ѷ���Ա��Է�����ÿ���� 2�������� i �� j����ʾ����ѷ���Ա��Է����У�����Ա i �ͷ���Ա j ��ԡ�����������ѷ���Ա��Է��������ڣ��������No Solution!����

## �����������

### ��������#1�� 

> 5 10  
> 1 7  
> 1 8  
> 2 6  
> 2 9  
> 2 10  
> 3 7  
> 3 8  
> 4 7  
> 4 8  
> 5 10  
> -1 -1  

### �������#1�� 
> 4  
> 1 7  
> 2 9  
> 3 8  
> 5 10  

## ˼·

* ���ƥ�䣬�������㷨

����ͼ��Ϊ���������֣��⼮����Ա��Ϊ��ߣ�Ӣ������Ա��Ϊ�ұߣ����бߴ����ָ���ұߡ���������߶�����Ϊ 1 ~ m�������Ϊ0 ~ m - 1���ұ߶����� m + 1 ~ n�������Ϊ 0 ~ n - m - 1��ʹ���������㷨�������ƥ�䣬�ֱ���DFS��BFSʵ�֡�


## ����

```cpp
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <queue>
using namespace std;

typedef unsigned char byte; //1�ֽ�����
typedef byte Vertex; //��������100����ʹ��byte��ż���

#define BYTE_MAX 0xff
#define NO_VERTEX BYTE_MAX

typedef unsigned int uint;


//�������㷨
class Hungarian {
public:
    /* �������ƥ�� 
    @param graph (����)ͼ����Ϊ���������֣����бߴ���߶���ָ���ұ߶���
    @param left_num  ��߶�����������߶����� 0 ~ left_num - 1
    @param right_num �ұ߶����������ұ߶����� 0 ~ right_num - 1
    @return void �޷���
    */
    virtual void maxMatching(vector<Vertex> * graph, size_t left_num, size_t right_num) = 0;

    //����������
    virtual ~Hungarian() {

    }
};


//DFSʵ��
class DFS : public Hungarian {
public:
    virtual void maxMatching(vector<Vertex> * graph, size_t left_num, size_t right_num);
private:

    /* ����ߵĶ��� v Ѱ���ұߵĶ���ƥ�䣬���ҵ�����true��*/
    bool dfs(Vertex v);

    vector<Vertex> * graph_;
    bool * visited_; //�ұߵĶ����Ƿ���ʹ�
    Vertex * matching_; //�ұ߶���ƥ�䵽�Ķ���
};

void DFS::maxMatching(vector<Vertex>* graph, size_t left_num, size_t right_num) {
    graph_ = graph;
    visited_ = new bool[right_num]; //ע���СΪright_num
    matching_ = new Vertex[right_num]; //ע���СΪright_num
    fill(matching_, matching_ + right_num, NO_VERTEX); //��ʼ�����ұ߶��㶼û��ƥ�䵽����
    uint num = 0; //ƥ������
    for (size_t i = 0; i < left_num; i++) { //������߶���
        fill(visited_, visited_ + right_num, false);
        if (dfs(i)) {
            //i�ҵ�ƥ��
            num++;
        }
    }
    printf("%u\n", num);
    if (num > 0) {
        for (size_t i = 0; i < right_num; i++) //�����ұ߶���
            if (matching_[i] != NO_VERTEX) {
                //���ƥ�䣬matching_[i]Ϊ��߶��㣬iΪ�ұ߶��㣬�����Ż�ԭ���� + 1���� + left_num + 1
                printf("%d %d\n", (int)matching_[i] + 1, (int)i + left_num + 1);
            }		
    }
    else {
        printf("No Solution!\n");
    }
    //�ͷ��ڴ�
    free(visited_);
    free(matching_);	
}

bool DFS::dfs(Vertex v) {
    Vertex adj_v;
    for (auto it = graph_[v].begin(); it != graph_[v].end(); it++) { //�����ڽӵ�
        adj_v = *it; //�ڽӵ�(�ұ߶���)
        if (!visited_[adj_v]) { //��û�з��ʹ�
            visited_[adj_v] = true;
            if (matching_[adj_v] == NO_VERTEX || dfs(matching_[adj_v])) { //adj_vû��ƥ�䣬����adj_vƥ�䵽�Ķ�������ҵ�����ƥ��
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
    virtual void maxMatching(vector<Vertex> * graph, size_t left_num, size_t right_num);
private:
    Vertex * left_matching_; //��߶���ƥ�䵽�Ķ���
    Vertex * right_matching_; //�ұ߶���ƥ�䵽�Ķ���
    Vertex * pre_; //BFSʱ��߶����ǰ��
    bool * visited_; //�ұ߶����Ƿ���ʹ�
    queue<Vertex> vqueue_; //����
};

void BFS::maxMatching(vector<Vertex>* graph, size_t left_num, size_t right_num) {
    left_matching_ = new Vertex[left_num]; //��СΪleft_num
    fill(left_matching_, left_matching_ + left_num, NO_VERTEX);
    right_matching_ = new Vertex[right_num]; //��СΪright_num
    fill(right_matching_, right_matching_ + right_num, NO_VERTEX);
    pre_ = new Vertex[left_num]; //��СΪleft_num
    visited_ = new bool[right_num]; //��СΪright_num
    uint num = 0; //ƥ������
    for (size_t i = 0; i < left_num; i++) { //������߶���
        fill(visited_, visited_ + right_num, false);
        pre_[i] = NO_VERTEX; //iû��ǰ��
        //BFS�н����еĶ�����ߵĶ��㣬���ǵ��ڽӵ㶼���ұ߶���
        vqueue_.push((Vertex)i);
        Vertex front_v, adj_v;		
        while (!vqueue_.empty()) {
            front_v = vqueue_.front(); //�����еĶ���
            vqueue_.pop();
            for (auto it = graph[front_v].begin(); it != graph[front_v].end(); it++) { //�����ڽӵ�
                adj_v = *it; //�ڽӵ�(�ұ߶���)
                if (!visited_[adj_v]) {
                    visited_[adj_v] = true;
                    if (right_matching_[adj_v] != NO_VERTEX) { //adj_v��ƥ��
                        vqueue_.push(right_matching_[adj_v]); //adj_vƥ�䵽�Ķ���(��߶���)���
                        /*pre_����: pre_[v]��ʾv��ǰ��������v�ҵ��µ�ƥ�䣬��pre_[v]������vԭ����ƥ�䶥��ƥ�䡣*/
                        pre_[right_matching_[adj_v]] = front_v; //��¼ǰ������right_matching_[adj_v]�ҵ�����ƥ�䣬��front_v��adj_vƥ��
                    }
                    else { //adj_vû��ƥ��
                        Vertex from = front_v, to = adj_v;
                        Vertex tmp;
                        while (from != NO_VERTEX) {							
                            tmp = left_matching_[from]; //fromԭ����ƥ��
                            left_matching_[from] = to; //from �� to ƥ��
                            right_matching_[to] = from; //from �� to ƥ��
                            //���£��´�ѭ���У�from��ǰ����fromԭ����ƥ�䶥��ƥ��
                            to = tmp; //to����Ϊfromԭ����ƥ��
                            from = pre_[from]; //from����Ϊfrom��ǰ��							
                        }
                        //����whileѭ������������Ϊ from == NO_VERTEX �������һ��whileѭ���У�from =  i  ( i �������forѭ����)��	\
                        from ����Ϊ pre_[from]��NO_VERTEX��Ȼ�����whileѭ������ʱ i �Ѿ�ƥ�䡣
                        while (!vqueue_.empty()) vqueue_.pop(); //��ն���
                        goto NEXT;
                    }
                }
            }
        } //bfs while
    NEXT:
        if (left_matching_[i] != NO_VERTEX) num++;
    } //for
    printf("%u\n", num);
    if (num > 0) {
        for (size_t i = 0; i < left_num; i++)
            if (left_matching_[i] != NO_VERTEX) {
                //���ƥ�䣬�����Ż�ԭ
                printf("%d %d\n", (int)i + 1, (int)left_matching_[i] + left_num + 1);
            }
    }
    else {
        printf("No Solution!\n");
    }
    //�ͷ��ڴ�
    free(left_matching_);
    free(right_matching_);
    free(pre_);
    free(visited_);
}

int main() {
    int m, n;
    scanf("%d %d", &m, &n);
    vector<Vertex> * graph = new vector<Vertex>[m]; //���бߴ���߶���ָ���ұ߶���
    int i, j;
    while (true) {
        scanf("%d %d", &i, &j);
        if (i == -1) break;
        //������߱�� 1 ~ m���ұ߱�� m + 1 ~ n
        //��Ϊ: ��߱�� 0 ~ m - 1, �ұ߱�� 0 ~ n - m - 1
        i--;
        j -= m + 1;
        graph[(Vertex)i].push_back((Vertex)j);
    }
    //ͨ�� Hungarianָ��ָ��ͬ���������л��㷨
    //Hungarian * hungarian = new DFS();
    Hungarian * hungarian = new BFS();
    //Hungarian * hungarian = m % 2 ? (Hungarian *)new DFS() : (Hungarian *)new BFS();
    hungarian->maxMatching(graph, m, n - m);	
    for (size_t i = 0; i < m; i++)
        vector<Vertex>().swap(graph[i]);
    delete hungarian;
    return 0;
}
```