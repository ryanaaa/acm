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
#pragma comment(linker, "/STACK:1024000000,1024000000") 

const int maxn = 100000 + 59, maxm = 20;
int n, m, d, a[maxn], dp[1 << maxm], cnt[maxm + 10];

int main() {
	scanf("%d %d %d", &n, &m, &d);
	for (int i = 0, x, k; i < m; i++) {
		scanf("%d", &k);
		while (k--) 
			scanf("%d", &x), a[x] = i;
	}

	memset(cnt, 0, sizeof(cnt));
	memset(dp, 0, sizeof(dp));

	int MASK = (1 << m) - 1;
	for (int i = 1, cur = 0; i <= n; i++) {
		if (i > d) {
			--cnt[a[i - d]];
			if (cnt[a[i - d]] == 0) cur ^= (1 << a[i - d]);
		}
		cnt[a[i]]++;
		cur |= (1 << a[i]);
		if (i >= d)
			dp[cur ^ MASK] = 1;
	}

	int res = m;
	for (int s = (1 << m) - 1; s >= 0; s--) {
		if (dp[s]) {
			for (int i = 0; i < m; i++) 
				if (s & (1 << i))
					dp[s ^ (1 << i)] = 1;
		} else
			res = min(res, __builtin_popcount(s));
	}

	printf("%d\n", res);
}
