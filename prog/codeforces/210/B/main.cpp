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

const int maxn = 2000 + 50;
int n, limit, dp[maxn], a[maxn];

int check(LL x) {
	dp[1] = 0;
	for (int i = 2; i <= n; i++) {
		dp[i] = i - 1;
		for (int j = 1; j < i; j++)
			if (abs(a[i] - a[j]) <= x * (i - j))
				dp[i] = min(dp[i], dp[j] + i - j - 1);
	}
	for (int i = 1; i <= n; i++)
		if (dp[i] + n - i <= limit)
			return 1;
	return 0;
}

int main() {
	scanf("%d %d", &n, &limit);
	for (int i = 1; i <= n; i++)
		scanf("%d", a + i);
	LL ll = 0, rr = 2000000000, mid;
	while (ll < rr) {
		mid = (ll + rr) >> 1;
		if (check(mid)) rr = mid;
		else ll = mid + 1;
	}
	cout << ll << endl;
}
