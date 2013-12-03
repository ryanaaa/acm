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

const int MAX_N = 200 + 5, MAX_T = 200 + 5, MAX_P = 200 + 5;
const int mod = 1000000007;

LL dp[MAX_N][MAX_N][MAX_P];
LL fac[MAX_N], invFac[MAX_N];

void update(LL &a, LL upd) {
	a = (a + upd) % mod;
}

LL comb(int n, int m) {
	return fac[n] * invFac[n - m] % mod * invFac[m] % mod;
}

LL aomb(int n, int m) {
	return fac[n] * invFac[n - m] % mod;
}

LL fastpow(LL a, int p, int m) {
	LL ret = 1;
	while (p) {
		if (p & 1) ret = ret * a % mod;
		if (p >>= 1) a = a * a % mod;
	}
	return ret;
}

void prepare() {
	fac[0] = invFac[0] = 1;
	for (int i = 1; i < MAX_N; i++) fac[i] = fac[i - 1] * i % mod;
	for (int i = 1; i < MAX_N; i++) invFac[i] = fastpow(fac[i], mod - 2, mod);

	int N = MAX_N - 1;
	int M = MAX_N - 1;//qry[test - 1].m;
	int P = MAX_P - 1;

	for (int n = 0; n <= N; n++)
	for (int p = 0; p <= P; p++)
		dp[n][0][p] = 1;
	for (int m = 1; m <= M; m++) {
		for (int n = 0; n <= N; n++) 
		for (int p = 0; p <= P; p++) {
			dp[n][m][p] = dp[n][m - 1][p];
			if (n >= 1 && m >= 1 && p >= 1)
				update(dp[n][m][p], dp[n - 1][m - 1][p - 1] * n);
			if (n >= 1 && m >= 2 && p >= 2)
				update(dp[n][m][p], dp[n - 1][m - 2][p - 2] * n * (m - 1));
			if (n >= 2 && m >= 1 && p >= 2)
				update(dp[n][m][p], dp[n - 2][m - 1][p - 2] * comb(n, 2));
//				printf("[%d,%d,%d,%d]=%lld\n", m, n, p, n1, dp[cur][n][p][n1]);
		 }
	}
}

int main() {
	prepare();

	int test;	scanf("%d", &test);
	for (int ti = 0; ti < test; ti++) {
		LL res = 0;
		int N, M, P, Q;	scanf("%d %d %d %d", &N, &M, &P, &Q);
		for (int q = 0; q <= Q && q <= N && q <= M; q++) {
			LL tmp = comb(N, q) * aomb(M, q) % mod * dp[N - q][M - q][P] % mod;
			update(res, tmp);
		}
		res = (res + mod - 1) % mod;
		printf("%d\n", (int) res);
	}

	return 0;
}
