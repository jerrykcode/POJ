#include "stdio.h"
#include "stdlib.h"

#ifndef max
#define max(a,b) (((a) > (b)) ? (a) : (b))
#define min(a,b) (((a) < (b)) ? (a) : (b))
#endif

int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	int *cost = (int *)malloc((m + 1) * sizeof(int));
	int *value = (int *)malloc((m + 1) * sizeof(int));
	for (int i = 1; i < m + 1; i++) {
		//����i�ļ۸�͵ȼ�
		scanf("%d %d", cost + i, value + i);
		//i�ļ�ֵΪi�ļ۸����i�ĵȼ�
		value[i] *= cost[i];
	}
	//��ʼ��dp
	int **dp = (int **)malloc((m + 1) * sizeof(int *));
	for (int i = 0; i < m + 1; i++) {
		dp[i] = (int *)malloc((n + 1) * sizeof(int));	
		dp[i][0] = 0;
	}
	for (int i = 0; i < n + 1; i++) {
		dp[0][i] = 0;
	}
	//����
	for (int i = 1; i < m + 1; i++) {
		for (int j = 1; j < n + 1; j++) {
			if (j >= cost[i]) {
				dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - cost[i]] + value[i]);
			}
			else dp[i][j] = dp[i - 1][j];
		}
	}
	printf("%d", dp[m][n]);
	//�ͷ��ڴ�
	free(cost);
	free(value);
	for (int i = 0; i < m + 1; i++)
		free(dp[i]);
	free(dp);
	return 0;
}