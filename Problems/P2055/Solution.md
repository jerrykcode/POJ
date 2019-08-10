# P2055 [ZJOI2009]���ڵ�����
[ԭ���ַ](https://www.luogu.org/problem/P2055)

## ��Ŀ����
ѧУ�ż���...... ��Щͬѧ�ؼ��ˣ�����Щͬѧ������ǰ�ĺ�������̽�ã���ôס�޾���һ�����⡣

���� A �� B ����ѧУ��ѧ����A Ҫ�ؼң��� C ����B��C �� A ����ʶ�����Ǽ���ÿ����ֻ��˯���Լ�ֱ����ʶ���˵Ĵ�����ôһ������������� B ˯ A �Ĵ��� C ˯ B �Ĵ�����ʵ��������ܷǳ����ӣ��е��˿�����ʶ�ö���Уѧ������Уѧ��֮��Ҳ��һ����������ʶ��

������֪һ���� n ���ˣ�����֪������ÿ�����ǲ��Ǳ�Уѧ����Ҳ֪��ÿ����Уѧ���Ƿ�ؼҡ����Ƿ����һ������ʹ�����в��ؼҵı�Уѧ�����������ǵ������˶��еط�ס��

## �����ʽ

��һ��һ���� T ��ʾ���������������� T �����ݣ�ÿ�����ݵ�һ��һ����n ��ʾ�漰������������

������һ�� n �������� i ������ʾ�� i �����Ƿ�����Уѧ�� (0 ��ʾ���ǣ�1 ��ʾ��)���ٽ�����һ�� n �������� i ������ʾ�� i �����Ƿ�ؼ� (0 ��ʾ���ؼң�1 ��ʾ�ؼң�ע������� i ���˲�����Уѧ������ô���λ���ϵ�����һ�������������Ӧ���ڶ����Ժ������)��

������ n ��ÿ�� n �������� i �е� j ������ʾ i �� j �Ƿ���ʶ (1 ��ʾ��ʶ��0 ��ʾ����ʶ���� i �� i ����ֵΪ 0��������Ȼ�Լ����ǿ���˯�Լ��Ĵ�)����ʶ�Ĺ�ϵ���໥�ġ�

## �����ʽ

����ÿ�����ݣ��������һ����������� ��^_^��(��������) ���������T_T��(��������)��(ע������Ķ��ǰ���ַ������������ŵ� ASCII ��ֱ�Ϊ94,84,95)

## �����������

### ���� #1

> 1  
> 3  
> 1 1 0  
> 0 1 0  
> 0 1 1  
> 1 0 0  
> 1 0 0

### ��� #1

> ^_^

## ˵��/��ʾ

���� 30% ���������� 1 <= n <= 12��

���� 100% ���������� 1 <= n <= 50,1 <= T <= 20��

`�������ݣ�����`

## ˼·
����ͼ���ƥ��(����ʹ���������㷨BFSʵ��)������ͼģ���[`P3386����ͼƥ��`���](https://github.com/jerrykcode/luogu/blob/master/Problems/P3386/Solution.md)

Ҫ��ѧУס����Ϊ��ͼ����λΪ��ͼ��

ʹ�ýṹ��
```cpp
struct Person {
	bool is_student;
	bool go_home;
	vector<vertex> list;
	~Person() {
		vector<vertex>().swap(list);
	}
};
```
��¼һ�����Ƿ���У���Ƿ�ؼң��Լ�������˯�Ĵ�λ��`(is_student && go_home)`��ʾ���������У����Ҫ�ؼң���ô���ǲ���ѧУס�ģ������`!(is_student && go_home)`��Ҫ��ѧУס��

����ÿ�����ݣ���Person�ṹ������洢ÿ���ˣ���������ÿ�����Ƿ���У���Ƿ�ؼҡ�Ȼ��������ʶ��ϵ������a��ʶb����ô��aҪ��ѧУס��b����У������a����˯b�Ĵ���ע�ⲻ�ؼҵ���У���ǿ���˯���Լ��Ĵ��ġ�
��һ���˿���˯ĳ�Ŵ��������(��ͼ����)�͸ô�(��ͼ����)֮�����ߡ��˵ı��Ϊ`0 ~ n - 1`(ʵ����ѧУס������С�ڵ���n�����ڻؼҵ���У�����������Ǽ���)�����ı��`0 ~ n - 1`(ʵ���ϴ���������У���ĸ�������0 ~ n - 1��һ��ÿ�����ֶ�����Ӧ��ŵĴ������Ⲣ��Ӱ��)��

�Զ���ͼ�����ƥ�伴�ɡ�

## ����

### C++


```cpp
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <queue>
using namespace std;

typedef unsigned char byte; //n <= 50��һ���ֽ��㹻
typedef byte vertex; //���㣬��ͼ��ʾ��ѧУס���ˣ���ͼ��ʾ��λ
#define BYTE_MAX 0xff
#define NOT_A_VERTEX BYTE_MAX //��ʾ�����ڵĶ���

struct Person {
	bool is_student; //true��Ϊ��У��
	bool go_home; //true��Ҫ�ؼң����ڷ���У��������Ч
	vector<vertex> list; //����˯�Ĵ�λ
	~Person() {
		vector<vertex>().swap(list);
	}
};

queue<vertex> q; //�������
bool hungarian(Person * p, int n) {
	vertex * left_matching = new vertex[n]; //left_matching[v]��ʾ��߶���vƥ�䵽���ұ߶���
	fill(left_matching, left_matching + n, NOT_A_VERTEX);
	vertex * pre = new vertex[n]; //pre[v]��ʾ��v�ҵ��µ�ƥ�䣬��vԭ����ƥ����Ը�pre[v]
	fill(pre, pre + n, NOT_A_VERTEX);
	vertex * right_matching = new vertex[n]; //right_matching[v]��ʾ�ұ߶���vƥ�䵽����߶���
	fill(right_matching, right_matching + n, NOT_A_VERTEX);
	bool * visited = new bool[n]; //visited[v]��ʾBFS���ұ߶���v�Ƿ���ʹ�
	bool result = true; //�������ʼ��Ϊtrue
	for (vertex v = 0; v < n; v++) { //����������
		if (p[v].is_student && p[v].go_home) continue; //��v����У���һؼң���������ƥ�䴲λ
		//����v��Ҫƥ��һ����λ��v����߶���
		fill(visited, visited + n, false);
		q.push(v);
		vertex front_v, adj_v, from, to, tmp_v;
		while (!q.empty()) {
			front_v = q.front();
			q.pop();
			for (auto it = p[front_v].list.begin(); it != p[front_v].list.end(); it++) {
				adj_v = *it; //front_v���ڽӵ㣬(�ұ߶���)
				if (!visited[adj_v]) {
					visited[adj_v] = true;
					if (right_matching[adj_v] != NOT_A_VERTEX) { //adj_v��ƥ�����߶��㣬�����Ŵ�����ƥ��
						q.push(right_matching[adj_v]); //���Ŵ�ƥ����˽����У��൱��DFS�еĵݹ�
						pre[right_matching[adj_v]] = front_v; //���Ժ����Ŵ�ƥ������ҵ����µĴ�ƥ�䣬��ôԭ�����Ŵ����Ը�front_vƥ�䣬pre�������˼�¼������
					}
					else { //adj_vû��ƥ�����߶��㣬�����Ŵ���û����ƥ�䣬��front_v�ҵ���λ��
						from = front_v;
						to = adj_v;
						while (from != NOT_A_VERTEX) {
							tmp_v = left_matching[from]; //tmp_vΪfromԭ����ƥ�䣬��fromԭ��û��ƥ�䣬��tmp_vΪNOT_A_VERTEX
							left_matching[from] = to; //��߶���fromƥ�䵽���ұ߶������Ϊto
							right_matching[to] = from; //�ұ߶���toƥ�䵽����߶������Ϊfrom
							 //from�ҵ�ƥ���ˣ���ǰ������֮ǰƥ���tmp_v��pre[from]
							from = pre[from];
							to = tmp_v; //fromԭ����ƥ��
						}
						while (!q.empty()) q.pop();
						goto NEXT;
					}
				}
			} //for auto it
		} //while (!q.empty())
	NEXT:
		if (left_matching[v] != NOT_A_VERTEX) continue; //v�ҵ���ƥ�䣬����
		else {
			//v�޷�ƥ�䵽��λ
			result = false;
			break;
		}
	} //for v
	free(left_matching);
	free(pre);
	free(right_matching);
	free(visited);
	return result;
}

//����һ�ֽ�
void inputByte(byte* p_byte) {
	int in;
	scanf("%d", &in);
	*p_byte = in;
}

void inputBoolean(bool * p_bool) {
	int in;
	scanf("%d", &in);
	if (in) *p_bool = true;
	else *p_bool = false;
}

int main() {
	byte t, n, i, j, k;
	inputByte(&t);
	for (i = 0; i < t; i++) {
		inputByte(&n);
		Person * p = new Person[n];
		for (j = 0; j < n; j++) inputBoolean(&p[j].is_student);
		for (j = 0; j < n; j++) inputBoolean(&p[j].go_home);
		for (j = 0; j < n; j++) {
			if (p[j].is_student && !p[j].go_home) p[j].list.push_back(j); //����У�Ҳ��ؼң�����˯�Լ��Ĵ�
			bool know_each_other;
			for (k = 0; k < n; k++) {
				inputBoolean(&know_each_other);
				if (know_each_other && !(p[j].is_student && p[j].go_home) && p[k].is_student) { //j��ʶk��j��ѧУס��k����У����j����˯k�Ĵ�
					p[j].list.push_back(k);
				}
			} //for k
		} //for j
		hungarian(p, n) ? printf("^_^\n") : printf("T_T\n");
		for (j = 0; j < n; j++) {
			p[j].~Person();
		}
	} //for i	
	return 0;
}
```
