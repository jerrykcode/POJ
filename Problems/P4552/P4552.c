#include "stdio.h"
#include "stdlib.h"
typedef long long LL;
int main() {
    int n;
    scanf("%d", &n);
    LL  d, pre, a;
    LL positive = 0, negative = 0;
    int i;
    for (i = 0; i < n; i++) {
        scanf("%lld", &a);
        //����
        //����dû��ʹ�����飬��i��ѭ����d��ʾd[i]
        if (i) d = a - pre;
        else d = a;
        pre = a;
        if (i) {
        //�����d[0]������֮���븺������ֵ֮��
            d > 0 ? (positive += d) : (negative -= d);
        }
    }
    LL max = positive > negative ? positive : negative;
    LL min = positive > negative ? negative : positive;
    //����max�β�����max - min�ε�������/���ٲ�����d[0]��max - min + 1�ֲ�ͬ��ֵ
    printf("%lld\n%lld", max, max - min + 1);
    return 0;
}