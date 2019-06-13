#include <cstdio>
#include <cstdlib>
#include <queue>
#include <vector>
using namespace std;

typedef unsigned short uint16_t; //16λ�޷�������
typedef uint16_t grid_t; //����
typedef uint16_t dist_t; //����(����)
#define DIST_INF 0xffff

//����
struct Coordinate {
	grid_t row, col; //������
	Coordinate() {}
	Coordinate(grid_t row, grid_t col) : row(row), col(col) {}
};

//dijkstra�д������ȶ��е�����
struct PriorityCoordinate : public Coordinate {
	dist_t dist; //��Դ�ľ���
	PriorityCoordinate(grid_t row, grid_t col, dist_t dist) : Coordinate(row, col), dist(dist) {}
	
	//���ȶ������ڱȽϵĽṹ��
	struct cmp {
		bool operator() (PriorityCoordinate& a, PriorityCoordinate& b) {
			return a.dist > b.dist;
		}
	};
};

//������������ö��һ���������ڵĸ���
struct Iterator {
	//���캯��������������ߴ�
	Iterator(char ** board, grid_t n_rows, grid_t n_cols) : board(board), n_rows(n_rows), n_cols(n_cols) {}
	
	//���ø���
	bool setCoordinate(grid_t row, grid_t col) {
		if (row < n_rows && col < n_cols) {
			this->row = row;
			this->col = col;
			direction = UP; //��ʼ���Ͽ�ʼ��
			return true;
		}
		return false;
	}
	
	//�õ���һ�����ڸ��ӵ�������
	bool next(grid_t * p_row, grid_t * p_col) {
		switch (direction) {
		case UP: { //������
			direction = LEFT; //�´�����
			if (row - 1 >= 0) { //������ڸ���
				*p_row = row - 1;
				*p_col = col;
				return true;
			}
			else //���治����
				return next(p_row, p_col); //�ݹ���
			break;
		}
		case LEFT: { //������
			direction = RIGHT; //�´�����
			if (col - 1 >= 0) { //��ߴ��ڸ���
				*p_row = row;
				*p_col = col - 1;
				return true;
			}
			else 
				return next(p_row, p_col); //�ݹ���
			break;
		}
		case RIGHT: { //������
			direction = DOWN; //�´�����
			if (col + 1 < n_cols) { //�ұߴ��ڸ���
				*p_row = row;
				*p_col = col + 1;
				return true;
			}
			else 
				return next(p_row, p_col); //�ݹ�
			break;
		}
		case DOWN: { //������
			direction = END; //����Ϊ�����ܵõ������ڸ��ӣ��´ν�����Ѱ��
			if (row + 1 < n_rows) { //�±ߴ��ڸ���
				*p_row = row + 1;
				*p_col = col;
				return true;
			}
			else
				return next(p_row, p_col); //�ݹ飬��ʵ��direction����ΪEND�󣬵ݹ�Ҳֻ���ܷ���false
			break;
		}
		case END :{ //�޴�����
			return false; //����false
			break;
		}
		default: return false; break;
		}	
		return false;
	}
private:
	char ** board; //����
	grid_t n_rows, n_cols; //���̵ĳߴ�
	grid_t row, col; //��ǰ���ӣ�next�����õ��ı���row, col�����ڸ���

	//Ѱ�����ڸ��ӵķ���
	typedef enum {
		UP,
		LEFT,
		RIGHT,
		DOWN,
		END,
	} Direction;

	Direction direction;
};

//������̾���(��С����)
//����ͨdijkstra��ͬ��ֻ��ͼ�Ķ����������е�һ������(����)��һ��������ڽӵ�Ϊ�������������ڵĸ���
dist_t dijkstra(char ** board, grid_t n_rows, grid_t n_cols, Coordinate src, Coordinate des) {
	bool ** collected = new bool *[n_rows];
	dist_t ** dist = new dist_t *[n_rows];
	for (size_t i = 0; i < n_rows; i++) {
		collected[i] = new bool[n_cols];
		fill(collected[i], collected[i] + n_cols, false);
		dist[i] = new dist_t[n_cols];
		fill(dist[i], dist[i] + n_cols, DIST_INF);
	}
	priority_queue<PriorityCoordinate, vector<PriorityCoordinate>, PriorityCoordinate::cmp> pq;
	pq.push(PriorityCoordinate(src.row, src.col, 0));
	dist[src.row][src.col] = 0;
	grid_t top_row, top_col;	
	dist_t top_dist, tmp_dist;
	grid_t adj_row, adj_col;
	Iterator it(board, n_rows, n_cols);
	while (!pq.empty()) {
		top_row = pq.top().row;
		top_col = pq.top().col;
		top_dist = pq.top().dist;
		pq.pop();
		if (collected[top_row][top_col]) continue;
		collected[top_row][top_col] = true;
		if (top_row == des.row && top_col == des.col) {
			//�����յ�
			while (!pq.empty()) pq.pop();
			break;
		}
		it.setCoordinate(top_row, top_col); //���õ�����
		while (it.next(&adj_row, &adj_col)) { //�������ڵĸ���
			if (!collected[adj_row][adj_col]) {
				tmp_dist = top_dist + (board[top_row][top_col] == board[adj_row][adj_col] ? 0 : 1);
				if (tmp_dist < dist[adj_row][adj_col]) {
					//����
					dist[adj_row][adj_col] = tmp_dist;
					pq.push(PriorityCoordinate(adj_row, adj_col, tmp_dist));
				}
			}
		}
	}
	dist_t result = dist[des.row][des.col];
	//�ͷ��ڴ�
	for (size_t i = 0; i < n_rows; i++) {
		free(collected[i]);
		free(dist[i]);
	}
	free(collected);
	free(dist);
	return result;
}

int main() {
	grid_t n, m, x1, y1, x2, y2;
	Coordinate src, des;
	char ** board;
	while (1) {
		scanf("%hd %hd", &n, &m);		
		if (!n) break;
		//��������
		board = new char *[n];
		for (size_t i = 0; i < n; i++) {
			board[i] = new char[m];			
			for (size_t j = 0; j < m; j++) {		
				scanf(" %c", &board[i][j]);
			}
		}
		//������㣬�յ�����
		scanf("%hd %hd %hd %hd", &x1, &y1, &x2, &y2);
		src.row = x1;
		src.col = y1;
		des.row = x2;
		des.col = y2;
		printf("%hd\n", dijkstra(board, n, m, src, des));
		for (size_t i = 0; i < n; i++) {
			free(board[i]);
		}
		free(board);
	}
	return 0;
}
