/*
 *gcd在书比较大时用递归的效率比循环和__gcd差很多
 */
#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <vector>
using namespace std;

typedef long long LL;
typedef pair<int, int> PII;
#define MP(a, b) make_pair(a, b)
#define FOREACH(e,x) for(__typeof(x.begin()) e=x.begin();e!=x.end();++e)
#define FOREACHINV(e,x) for(__typeof(x.rbegin()) e=x.rbegin();e!=x.rend();++e)

const int maxn = 1000000 + 50;
int n;
LL a[maxn];
map<LL, int> mp;

LL gcd(LL a, LL b) {
	//return b ? gcd(b, a % b) : a;
	while (b) {
		LL tmp = b;
		b = a % b;
		a = tmp;
	}
}

LL tempKey[10000];
int tempValue[10000];
int tempCnt = 0;
LL work(LL ar) {
	mp.clear();
	tempCnt = 0;
	for (LL d = 1; d * d <= ar; d++)
	if (ar % d == 0) {
		tempKey[tempCnt++] = d;
		if (d * d != ar)
			tempKey[tempCnt++] = ar / d;
	}
	sort(tempKey, tempKey + tempCnt);
	memset(tempValue, 0, sizeof(tempValue));

	//printf("ar=%lld\n", ar);
	for (int i = 0; i < n; i++) {
		LL x = __gcd(a[i], ar);
		tempValue[lower_bound(tempKey, tempKey + tempCnt, x) - tempKey]++;
	}

//	FOREACH(e, mp) {
//		tempKey[tempCnt] = e->first;
//		tempValue[tempCnt++] = e->second;
//	}
	//FOREACH(e, mp)
	//	printf("Map1: %lld %d\n", e->first, e->second);
	int threshold = (n + 1) >> 1;
	for (int i = tempCnt - 1; i >= 0; i--) {
		int tmp = tempValue[i];
		for (int j = i + 1; j < tempCnt; j++)
			if (tempKey[j] % tempKey[i] == 0)
				tmp += tempValue[j];
		if (tmp >= threshold)
			return tempKey[i];
	}
	//FOREACHINV(e1, mp) {
	//	int tmp = e1->second;
	//	FOREACH(e2, mp)
	//		if (e2->first % e1->first == 0 && e1->first != e2->first)
	//			tmp += e2->second;
	//	if (tmp >= threshold)
	//		return e1->first;
	//}
	//FOREACH(e, mp)
	//	printf("Map: %lld %d\n", e->first, e->second);
	//LL ret = 1;
	//FOREACHINV(e, mp)
	//	if (e->second >= threshold) {
	//		ret = e->first;
	//		break;
	//	}
	//printf("Ret = %lld\n", ret);
	return 0;
}
int main() {
	srand(time(NULL));
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%lld", a + i);
	
	LL res = 1;
	for (int loop = 10; loop > 0; --loop) {
		int ri = (rand() % n + n) %n;
		LL tmp = work(a[ri]);
		res = max(res, tmp);
	}

	cout << res << endl;
}
