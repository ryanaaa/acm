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

const int maxn = 100 + 5;
const double INF = 1e30;
int n, rCnt, res[maxn << 1], resType[maxn << 1];
double dp[maxn][maxn][maxn];
int sol[maxn][maxn][maxn];

struct Point {
	double x, y;
	void input() {
		scanf("%lf %lf", &x, &y);
	}
	double dis(const Point &p) {
		return sqrt((x - p.x) * (x - p.x) + (y - p.y) * (y - p.y));
	}
} pIn[maxn], pOut[maxn];

void getSol(int l, int r, int x) {
	if (l > r)
		return;
	if (x == r) {
		resType[rCnt] = 0;
		res[rCnt++] = x;
		getSol(l, r - 1, sol[l][r][x]);
		resType[rCnt] = 1;
		res[rCnt++] = x;
	} else {
		getSol(l, x, x);
		getSol(x + 1, r, sol[l][r][x]);
	}
}

void update(int l, int r, int x, double upd, int y) {
	if (dp[l][r][x] > upd) {
		dp[l][r][x] = upd;
		sol[l][r][x] = y;
	}
}

int main() {
	while (~scanf("%d", &n)) {
		for (int i = 1; i <= n; i++) {
			pIn[i].input();
			pOut[i].input();
		}

		for (int r = 1; r <= n; r++)
		for (int l = r; l >= 1; l--) 
		for (int x = l; x <= r; x++) 
			dp[l][r][x] = INF;

		for (int r = 1; r <= n; r++)
		for (int l = r; l >= 1; l--) {
			if (l == r) {
				dp[l][r][r] = pIn[r].dis(pOut[r]);
				continue;
			}
			for (int x = l; x <= r; x++) {
				if (x == r) {
					for (int y = l; y <= r - 1; y++) {
						double tmp = pIn[x].dis(pIn[y]) + dp[l][r - 1][y] + pOut[r - 1].dis(pOut[x]);
						update(l, r, x, tmp, y);
					}
				} else {
					for (int y = x + 1; y <= r; y++) {
						double tmp = dp[l][x][x] + pOut[x].dis(pIn[y]) + dp[x + 1][r][y];
						update(l, r, x, tmp, y);
					}
				}
			}
		}

		int first;
		double mn = INF;
		for (int x = 1; x <= n; x++)
		if (dp[1][n][x] < mn) {
			mn = dp[1][n][x];
			first = x;
		}

		rCnt = 0;
		getSol(1, n, first);

		for (int i = 0; i < rCnt; i++) {
			printf("%d", res[i]);
			putchar(resType[i] ? '-' : '+');
			putchar(i < rCnt - 1 ? ' ' : '\n');
		}
	}

	return 0;
}
