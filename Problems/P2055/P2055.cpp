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