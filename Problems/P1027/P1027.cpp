#include <iostream>
#include <stdio.h>
#include <math.h>
using namespace std;

#define N_AIRPORTS_PER_CITY 4 //ÿ�����еĻ�����
#define GET_CITY_INDEX(airport_idx) ((airport_idx) / N_AIRPORTS_PER_CITY) //�õ�һ�����������ĳ��б��
#define GET_AIRPORT_INDEX(city_idx, i) ((city_idx) * N_AIRPORTS_PER_CITY + (i)) //�õ�һ�����е�i�������ı��
#define NO_VALUE -1

class CarRoute {
public:
	CarRoute() {}
	~CarRoute() {}

	void solve(); //������

private:
	struct Airport {
		//����������
		int x; 
		int y;
	};

	int square(int x) { return x * x; }

	/* ���������������ֱ�߾��� */
	float getAirportDist(Airport& a, Airport& b);

	/* ��dijkstra�����· */
	float dijkstra(int src_city, int des_city);

	int nAirports_; //�ܻ�������
	Airport *airports_; //�������飬���δ洢��0������1�����������е�4������

	int cost_air_; //���ߵ�λ��̵ļ۸�
	int *cost_train_; //cost_train_[i]Ϊ��i�������и�����·�ĵ�λ��̼۸�
};

void CarRoute::solve() {
	int nCities, src_city, des_city; //����������㣬�յ�
	scanf("%d %d %d %d", &nCities, &cost_air_, &src_city, &des_city);
	src_city--; //��Ϊ��0��ʼ���
	des_city--;
	nAirports_ = nCities * N_AIRPORTS_PER_CITY;
	airports_ = new Airport[nAirports_];
	cost_train_ = new int[nCities];
	for (int i = 0; i < nCities; i++) {
		int ax, ay, bx, by, cx, cy, dx, dy;
		//����ÿ������ǰ��������
		scanf("%d %d %d %d %d %d %d", &ax, &ay, &bx, &by, &cx, &cy, cost_train_ + i);
		airports_[GET_AIRPORT_INDEX(i, 0)].x = ax;
		airports_[GET_AIRPORT_INDEX(i, 0)].y = ay;
		airports_[GET_AIRPORT_INDEX(i, 1)].x = bx;
		airports_[GET_AIRPORT_INDEX(i, 1)].y = by;
		airports_[GET_AIRPORT_INDEX(i, 2)].x = cx;
		airports_[GET_AIRPORT_INDEX(i, 2)].y = cy;
		int abSquare = square(ax - bx) + square(ay - by);
		int acSquare = square(ax - cx) + square(ay - cy);
		int bcSquare = square(bx - cx) + square(by - cy);
		if (abSquare == acSquare + bcSquare) { //cΪֱ�Ƕ���
			dx = ax + bx - cx;
			dy = ay + by - cy;
		}
		else if (acSquare == abSquare + bcSquare) { //bΪֱ�Ƕ���
			dx = ax + cx - bx;
			dy = ay + cy - by;
		}
		else { //aΪֱ�Ƕ���
			dx = bx + cx - ax;
			dy = by + cy - ay;
		}
		//���һ��������������ȷ��
		airports_[GET_AIRPORT_INDEX(i, 3)].x = dx;
		airports_[GET_AIRPORT_INDEX(i, 3)].y = dy;
	}
	float minCost = dijkstra(src_city, des_city); //�������·
	printf("%.1f\n", minCost);
	free(airports_);
	free(cost_train_);
}

float CarRoute::getAirportDist(Airport & a, Airport & b) {
	return sqrt(square(a.x - b.x) + square(a.y - b.y));
}

float CarRoute::dijkstra(int src_city, int des_city) {
	float *cost = new float[nAirports_]; //cost[i]��ʾ����㵽��i�������ĵ�ǰ��С����
	bool *collected = new bool[nAirports_];
	fill(cost, cost + nAirports_, NO_VALUE);
	fill(collected, collected + nAirports_, false);
	for (int i = 0; i < 4; i++) //�������е�4��������cost��Ϊ0
		cost[GET_AIRPORT_INDEX(src_city, i)] = 0;
	while (true) {
		int minV = NO_VALUE;
		float minCost = NO_VALUE;
		//��δ��¼�������ҵ�cost��С��
		for (int i = 0; i < nAirports_; i++)
			if (!collected[i] && cost[i] != NO_VALUE && (cost[i] < minCost || minCost == NO_VALUE)) {
				minV = i;
				minCost = cost[i];
			}
		int minCity = GET_CITY_INDEX(minV); //minCityΪ��Сcost����minV���ڳ���
		if (minCity == des_city) { //�����յ���ͬһ����
			free(cost);
			free(collected);
			return minCost;
		}
		if (minV == NO_VALUE) break;
		collected[minV] = true; //��¼minV
		for (int i = 0; i < nAirports_; i++) 
			if (!collected[i]) {
				float dist = getAirportDist(airports_[minV], airports_[i]); //distΪminV��i��ֱ�߾���
				//��minV��i��ͬһ�����У����minV��i�ķ���Ϊdist���Ըó��е���·���ã�����Ϊdist���Ժ��߷���
				float cost_tmp = GET_CITY_INDEX(i) == minCity ? dist * cost_train_[minCity] : dist * cost_air_;
				if (minCost + cost_tmp < cost[i] || cost[i] == NO_VALUE) { //��ͨ��minVʹcost[i]��С
					cost[i] = minCost + cost_tmp; //����
				}
			}
	} //while
	free(cost);
	free(collected);
	return NO_VALUE;
}


int main() {
	CarRoute carRoute;
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		carRoute.solve();
	}
	return 0;
}