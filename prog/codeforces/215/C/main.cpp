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

const int maxn = 2000000 + 50, maxm = 100000 + 50;
int n, m, q[maxm], w[maxm];

/*
 * 设F(K) 表示最小的N，满足a[1,,N]由K个不同元素组成，且任意两个不同元素在a中的至少一处相邻
 * K == 1, F(K) = 1
 * 对于K == Odd
 *		1. 因为长度为N的数列最都有N-1个相邻对, 所以N - 1 >= C(K, 2)
 *		2. 考虑K个顶点的完全无向图，任意删掉一条边，可知存在欧拉路径(无向图存在欧拉路径<=>奇数度点=2)
 *		F(K) = C(K, 2) + 1 (K == odd And K > 1)
 *	对于K == Even
 *		1. 因为每个元素最少需要出现upper((K - 1) / 2) = K / 2次，所以N >= K*K/2
 *		2. 考虑K个顶点的完全无向图，将边(Vi, V(i+1)): i = 0 mod 2 And i >= 2, 变成两条无向边, 也可以证明其上
 */
int getMaxNumber(int n) {
	if (n == 1)
		return 1;
	int even = (int) sqrt(2.0 * n) + 1;
	if (even & 1) even--;
	while (even * even / 2 > n) even -= 2;

	int odd = (int) sqrt(2.0 * n) + 1;
	if ((odd & 1) == 0) odd--;
	while (odd * (odd - 1) / 2 + 1 > n) odd -= 2;

	return max(even, odd);
}

int main() {
	scanf("%d %d", &n, &m);
	for (int i = 0; i < m; i++) {
		scanf("%d %d", q + i, w + i);
	}

	sort(w, w + m);

	int maxNumber = getMaxNumber(n);
	//printf("maxNumber: %d\n", maxNumber);
	LL res = 0;
	for (int i = m - 1; i >= 0 && i >= m - maxNumber; i--)
		res += w[i];

	cout << res << endl;

	return 0;
}
