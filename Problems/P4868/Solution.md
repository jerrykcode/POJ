# P4868 Preprefix sum
[ԭ���ַ](https://www.luogu.org/problem/P4868)

## ��Ŀ����

ǰ׺��(prefix sum)Si = a1 + a2 + ... + ak��

ǰǰ׺��(preprefix sum) ���Si��Ϊԭ�����ٽ���ǰ׺�͡����ٴ����ǰ׺�͵�i����SSi 

��һ������n������a1��a2��... an�������ֲ�����

Modify i x����ai�ĳ�x��
Query i����ѯSSi

## �����ʽ

��һ�и�����������N��M���ֱ��ʾ���г��ȺͲ�������  
������һ����N������������������a1,a2,....an  
������M�У�ÿ�ж�Ӧһ����������ʽ����Ŀ����  

## �����ʽ
����ÿ��ѯ�ʲ��������һ�У���ʾ��ѯ�ʵ�SSi��ֵ��

## �����������

### ���� #1
 > 5 3  
1 2 3 4 5  
Query 5  
Modify 3 2  
Query 5  

### ��� #1
> 35  
32  

## ˵��/��ʾ
1<=N,M<=100000,��������ʱ��0<=Ai<=100000

## ˼·

����ԭ����a��ǰ׺��s�Լ�s��ǰ׺��ss��  
����ss[i] = s[1] + s[2] + ... + s[i]  
������a[i]��s[i]��s[i + 1]��...��s[n]��Ҫ���¡� 
��ô�����ת��Ϊ��`ǰ׺��s�������޸�/��Ͳ�����`  
�����޸�/�������״����������Ҫ���֣���s�Ĳ����ʵ����:  
s[i] - s[i - 1]  
= (s[i - 1] + a[i]) - s[i - 1]  
= a[i]  
�������̫�����ˣ�  
Ҫ��¼�Ĳ�־���a���鱾�� 
����״�����¼a���Լ���һ������b��b[i] = a[i]\*i  
��Modify i x������ֱ�Ӹ���a��b����״���鼴�ɡ�  
�� 
ss[i]  
= s[1] + s[2] + ... + s[i]  
= a[1] + a[1] + a[2] + ... + a[1] + a[2] + ... + a[i]  
= i \* a[1] + (i - 1) \* a[2] + ... + 1 \* a[i]  
= (i + 1) \* a[1] - 1 \* a[1] + (i + 1) \* a[2] - 2 \* a[2] + ... + (i + 1) \* a[i] - i \* a[i]  
= (i + 1) \* (a[1] + a[2] + ... + a[i]) - (1 \* a[1] + 2 \* a[2] + ... + i \* a[i])  
= (i + 1) \* (a[1] + a[2] + ... + a[i]) - (b[1] + b[2] + ... + b[i])  
��ô��ѯss[i]ֻ���a��b����������ͣ�  
ͨ��a��b����״����Ҳ��������ʵ�֡�  

## Code

```cc
#include "stdio.h"
#include "stdlib.h"
#include <iostream>
#include <string>
using namespace std;

typedef long long LL;

int lowbit(int x) {
	return x & -x;
}

int n;

void update(LL * bit, int idx, LL k) {
	for (; idx <= n; idx += lowbit(idx)) {
		bit[idx] += k;
	}
}

LL sum(LL * bit, int idx) {
	LL result = 0;
	for (; idx > 0; idx -= lowbit(idx)) {
		result += bit[idx];
	}
	return result;
}

int main() {
	int m;
	scanf("%d %d", &n, &m);
	LL * bit_a = (LL *)malloc((n + 1) * sizeof(LL));
	LL * bit_b = (LL *)malloc((n + 1) * sizeof(LL));
	for (int i = 1; i < n + 1; i++) {
		bit_a[i] = bit_b[i] = 0;
	}
	LL *a = (LL *)malloc((n + 1) * sizeof(LL));
	for (int i = 1; i < n + 1; i++) {
		scanf("%lld", a + i);
		update(bit_a, i, a[i]);
		update(bit_b, i, a[i]*i);
	}
	//char cmd[6];
	string cmd;
	int idx;
	LL x;
	for (int i = 0; i < m; i++) {
		//scanf("%s", cmd);
		cin >> cmd;
		if (cmd[0] == 'M') {
			scanf("%d %lld", &idx, &x);
			update(bit_a, idx, x - a[idx]);
			update(bit_b, idx, (x - a[idx]) * idx);
			a[idx] = x;		
		}
		else {
			scanf("%d", &idx);			
			printf("%lld\n", sum(bit_a, idx) * (idx + 1) - sum(bit_b, idx));
		}		
	}
	free(bit_a);
	free(bit_b);
	free(a);
	return 0;
}
```