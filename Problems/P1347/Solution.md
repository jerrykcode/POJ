# P1347 ����
[ԭ���ַ](https://www.luogu.org/problemnew/show/P1347)

## ��Ŀ����

һ����ͬ��ֵ��������������ָ����һ��������Ԫ��������������У����磬һ�����������A,B,C,D ��ʾA<B,B<C,C<D����������У����ǽ�����һϵ������A<B�Ĺ�ϵ����Ҫ�����ж��Ƿ��ܹ�������Щ��ϵȷ��������е�˳��

## ���������ʽ

### �����ʽ��

��һ������������n,m��n��ʾ��Ҫ�����Ԫ��������2<=n<=26����1��n��Ԫ�ؽ��ô�д��A,B,C,D....��ʾ��m��ʾ������������A<B�Ĺ�ϵ��������

��������m�У�ÿ����3���ַ����ֱ�Ϊһ����д��ĸ��һ��<���ţ�һ����д��ĸ����ʾ����Ԫ��֮��Ĺ�ϵ��

### �����ʽ��

������ǰx����ϵ����ȷ����n��Ԫ�ص�˳��yyy..y����ABC�������

> Sorted sequence determined after xxx relations: yyy...y.

������ǰx����ϵ�����ִ���ì�ܣ���A<B,B<C,C<A�������

> Inconsistency found after 2 relations.

��������m����ϵ�޷�ȷ����n��Ԫ�ص�˳�����

> Sorted sequence cannot be determined.

����ʾ��ȷ��n��Ԫ�ص�˳��󼴿ɽ������򣬿���`���ÿ���ȷ��˳��֮�����ì�ܵ����`��

## �����������

### ��������#1�� 
> 4 6  
> A<B  
> A<C  
> B<C  
> C<D  
> B<D  
> A<B  

### �������#1�� 

> Sorted sequence determined after 4 relations: ABCD.


### ��������#2�� 
> 3 2  
> A<B  
> B<A  

### �������#2�� 

> Inconsistency found after 2 relations.

### ��������#3�� 
> 26 1  
> A<Z  

## �������#3�� 

> Sorted sequence cannot be determined.

## ˼·

��������x<y��x��y��һ������ߡ�����ͼ��

ÿ����һ���ߣ��������������򣬴�ʱͼ�Ķ�����������ı��еĶ��㣨��һ�����ж��㶼������ˣ�����¼�����еĶ�����Ŀ����¼������������¼�Ķ�����ĿС��ͼ�Ķ�����Ŀ�����л��������޻���������������ͼ�Ķ�������������������򣬷����޷�ȷ�������ڷ����л�ʱ���������룬�����ж��㶼�ڱ��б�����������������Ҳ�������룬����������벢����ߡ�ÿ�����������������vector�洢����еĶ��㣬�����ж��㶼�ڱ��б��������������������

## ����

```cpp
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

#define MAX_LETTER 26
#define NO_VERTEX 0xff

typedef unsigned char BYTE;
typedef BYTE Vertex; //���ֻ��26�����㣬unsigned char�㹻

//����������
class Topsort {
public:
    Topsort() {}
    ~Topsort() {
        vector<Vertex>().swap(order);
    }

    //����������
    typedef enum {
        SORTED, //ȷ������
        UNSORTED, //�޷�ȷ������
        HAS_LOOP, //�л�
    } TopRESULT;

    /* �������򣬷��ؽ����*/
    Topsort::TopRESULT top(vector<Vertex> *graph, int nv, int *indegree);

    /* �������vertex_to_letter�Ƕ�����Ŷ�Ӧ����ĸ��*/
    void print_order(char *vertex_to_letter);

private:
    //�����
    vector<Vertex> order; //��������
    queue<Vertex> q;
};

Topsort::TopRESULT Topsort::top(vector<Vertex>* graph, int nv, int * indegree) {
    order.clear();
    int *level = new int[nv]; //����
    int vcount = 0;
    for (int i = 0; i < nv; i++) 
        if (indegree[i] == 0) {
            q.push((Vertex)i);
            order.push_back((Vertex)i);
            level[i] = 1;
            vcount++;
        }
    int max_level = 1; //������
    while (!q.empty()) {
        Vertex v = q.front();
        q.pop();
        for (Vertex w : graph[(int)v]) {
            if (--indegree[w] == 0) {
                q.push(w);
                order.push_back(w);
                level[(int)w] = level[(int)v] + 1;
                if (level[(int)w] > max_level) max_level = level[(int)w];
                vcount++;
            }
        }
    }
    free(level);
    if (vcount == nv) {
        return max_level == nv ? SORTED : UNSORTED;
    }
    else return HAS_LOOP;
}

void Topsort::print_order(char * vertex_to_letter) {
    for (auto it = order.begin(); it != order.end(); it++) {
        printf("%c", vertex_to_letter[(int)(*it)]);
    }
}

int main() {
    int n, m, a, b;
    scanf("%d %d", &n, &m);
    vector<Vertex> *graph = new vector<Vertex>[n]; //ͼ
    int *indegree = new int[n]; //�������
    fill(indegree, indegree + n, 0);
    int *indegree_copy = new int[n]; //������鿽��
    Vertex *letter_to_vertex = new Vertex[MAX_LETTER]; //��ĸ��Ӧ�������
    fill(letter_to_vertex, letter_to_vertex + MAX_LETTER, NO_VERTEX); 
    char *vertex_to_letter = new char[n]; //������Ŷ�Ӧ��ĸ
    int count = 0;
    char *s = new char[3];
    Topsort topsort;
    bool unsorted_flag = true;
    for (int i = 0; i < m; i++) {
        scanf("%s", s);
        a = s[0] - 'A';
        b = s[2] - 'A';
        if (letter_to_vertex[a] == NO_VERTEX) {
            //���
            letter_to_vertex[a] = (Vertex)count;
            vertex_to_letter[count++] = s[0];
        }
        if (letter_to_vertex[b] == NO_VERTEX) {
            //���
            letter_to_vertex[b] = (Vertex)count;
            vertex_to_letter[count++] = s[2];
        }
        graph[letter_to_vertex[a]].push_back(letter_to_vertex[b]);
        indegree[letter_to_vertex[b]]++;
        memcpy(indegree_copy, indegree, n * sizeof(int)); //�����������
        Topsort::TopRESULT top_result = topsort.top(graph, count, indegree_copy); //ע�⴫��count(��ǰ������Ķ�����)����n
        switch (top_result) {
        case Topsort::SORTED: {
            if (n == count) { //δ�������ж���Ҳ���ܿ�������ɹ�
                printf("Sorted sequence determined after %d relations: ", i + 1);
                topsort.print_order(vertex_to_letter);
                printf(".");
                unsorted_flag = false;
                goto END;
            }
            break;
        }
        case Topsort::UNSORTED: {
            break;
        }
        case Topsort::HAS_LOOP: { //�л�
            printf("Inconsistency found after %d relations.", i + 1);
            unsorted_flag = false;
            goto END;
        }
        }
    }
END:
    if (unsorted_flag) {
        printf("Sorted sequence cannot be determined.");
    }
    for (int i = 0; i < n; i++)
        vector<Vertex>().swap(graph[i]);
    free(indegree);
    free(indegree_copy);
    free(letter_to_vertex);
    free(vertex_to_letter);
    return 0;    
}

```