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

const int maxn = 200000 + 50, maxm = maxn, maxk = maxn;
int a[maxn], b[maxm], n, m, p, match[maxk];
map<int, int> mpA[maxk], mpB;
vector<int> res;

int main() {
	scanf("%d %d %d", &n, &m, &p);
	for (int i = 0; i < n; i++) scanf("%d", a + i);
	for (int i = 0; i < m; i++) scanf("%d", b + i);

	for (int k = 0; k < p; k++) mpA[k].clear(), match[k] = 0;
	mpB.clear();
	for (int j = 0; j < m; j++) mpB[b[j]]++;

	res.clear();
	// p * m 可能大于int，我草
	for (int i = 0; i < n; i++) {
		int k = i % p;
		if (i >= (LL) p * m) {
			// remove a[i - p]
			int rem = a[i - p * m];
			if (mpB.find(rem) != mpB.end()) {
				if (mpA[k][rem] <= mpB[rem])
					match[k]--;
				mpA[k][rem]--;
			}
		}
		// insert a[i]
		int ins = a[i];
		if (mpB.find(ins) != mpB.end()) {
			if (mpA[k][ins] < mpB[ins])
				match[k]++;
			mpA[k][ins]++;
		}
		if (match[k] == m)
			// 这里如果算法对了，就保证合法
			res.push_back(i - p * m + p);
		//printf("%d %d\n", k, match[k]);
	}

	printf("%d\n", res.size());
	for (int i = 0, _i = res.size(); i < _i; i++) {
		printf("%d%c", res[i] + 1, i < _i - 1 ? ' ' : '\n');
	}

	return 0;
}
