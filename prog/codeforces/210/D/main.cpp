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

const int maxn = 10000 + 50, maxm = 100000 + 50;
int n, m, p, a[maxn], b[maxm];

const int MAX_P = 33000;
int minp[MAX_P], prime[10000], pnum;
void initPrimes() {
	pnum = 0;
	minp[1] = 0;
	for (int i = 2; i <= MAX_P; i++) 
		minp[i] = i;
	for (LL i = 2; i <= MAX_P; i++) 
	if (minp[i] == i) {
		prime[pnum++] = i;
		for (LL j = i * i; j <= MAX_P; j += i) 
		if (minp[j] == j)
			minp[j] = i;
	}
}

void decompose(int n, int *factor, int *exp, int &fnum) {
	fnum = 0;
	for (int i = 0; (LL) prime[i] * prime[i] <= n; i++) 
	if (n % prime[i] == 0) {
		factor[fnum] = prime[i];
		exp[fnum] = 0;
		while (n % prime[i] == 0) {
			n /= prime[i];
			exp[fnum]++;
		}
		fnum++;
	}
	if (n > 1) {
		factor[fnum] = n;
		exp[fnum++] = 1;
	}
}

int fastpow(LL a, LL p, int m) {
	LL ret = 1;
	while (p) {
		if (p & 1) ret = ret * a % m;
		if (p >>= 1) a = a * a % m;
	}
	return (int) ret;
}

LL gcd(LL a, LL b) {
	return b ? gcd(b, a % b) : a;
}

LL lcm(LL a, LL b) {
	return a / gcd(a, b) * b;
}

int getOrder(int a, int p) {
	static int pFactor[100], pExp[100], pFnum;
	decompose(p - 1, pFactor, pExp, pFnum);
	int cur = p - 1;
	for (int i = 0; i < pFnum; i++) {
		for (int j = 0; j < pExp[i]; j++) {
			if (fastpow(a, cur / pFactor[i], p) == 1)
				cur /= pFactor[i];
		}
	}
	return cur;
}

map<LL, LL> dp[2];
int main() {
	initPrimes();
	scanf("%d %d %d", &n, &m, &p);
	for (int i = 1; i <= n; i++) 
		scanf("%d", a + i);
	for (int j = 1; j <= m; j++)
		scanf("%d", b + j);

	int B = p - 1;
	for (int j = 1; j <= m; j++)
		B = gcd(B, b[j]);

	for (int i = 1; i <= n; i++) {
		int order = getOrder(a[i], p);
		a[i] = gcd((LL) (p - 1) / order * B, p - 1);
		// !!
		if (a[i] == 0) a[i] = p - 1;
	}

	int pre = 0, cur = 1;
	dp[cur].clear();
	for (int i = 1; i <= n; i++) {
		swap(pre, cur);
		dp[cur].clear();
		dp[cur][a[i]] = 1;
		FOREACH(e, dp[pre]) {
			//printf("%d %lld\n", e->first, e->second);
			dp[cur][e->first] += e->second;
			dp[cur][lcm(e->first, a[i])] -= e->second;
		}
		//puts("----------");
	}

	LL res = 0;
	FOREACH(e, dp[cur]) {
		//printf("%d %lld\n", e->first, e->second);
		LL add = (p - 1) / e->first;
		res += add * (e->second);
	}

	printf("%d\n", (int) res);

	return 0;
}
