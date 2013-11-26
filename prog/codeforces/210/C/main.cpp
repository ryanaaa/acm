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

const int maxn = 2000 + 50, maxs = 2000 + 50, MOD = 1000000007;
int n, sum;
LL F[maxn][maxs], G[maxn][maxs];
char str[maxn];
// G(i, s) 表示有多少个t,满足t[i+1,,n]=s[i+1,,n],t[i]!=s[i],且满足t[x,y]>s[x,y]的子串个数=sum
// F(i, s) 表示有多少个t,满足t[i+1,,n]=s[i+1,,n],且满足t[x,y]>s[x,y]的子串个数=sum

int main() {
	scanf("%d %d", &n, &sum);
	scanf("%s", str + 1);

	memset(G, 0, sizeof(G));
	memset(F, 0, sizeof(F));
	F[0][0] = G[0][0] = 1;
	for (int i = 1; i <= n; i++) 
	for (int s = 0; s <= sum; s++) {
		G[i][s] = F[i - 1][s] * (str[i] - 'a') % MOD;
		for (int pref = 0; pref < i && (1 + pref) * (n - i + 1) <= s; pref++)
			G[i][s] = (G[i][s] + G[i - pref - 1][s - (1 + pref) * (n - i + 1)] * ('z' - str[i])) % MOD;
		F[i][s] = (F[i - 1][s] + G[i][s]) % MOD;
	}

	cout << F[n][sum] << endl;
}
