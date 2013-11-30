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

const int maxn = 200000 + 50;
int n, m, w[maxn], L[maxn], R[maxn], qid[maxn], pval[maxn];
set<PII > stR;

int minp[maxn], prime[maxn], pnum;
void initPrimes() {
	pnum = 0;
	minp[1] = 0;
	for (int i = 2; i < maxn; i++) 
		minp[i] = i;
	for (LL i = 2; i < maxn; i++) 
	if (minp[i] == i) {
		prime[pnum++] = i;
		for (LL j = i * i; j < maxn; j += i) 
		if (minp[j] == j)
			minp[j] = i;
	}
}

struct Query {
	int id, l, r, res; 
	void init(int _id) {
		id = _id;
		scanf("%d %d", &l, &r);
	}
} qry[maxn];

bool cmp(int i, int j) {
	return qry[i].r < qry[j].r;
}


struct BIT {
	int bit[maxn], n;
	void init(int _n) {
		n = _n + 1;
		memset(bit, 0, sizeof(bit));
	}
	void update(int x, int add) {
		x++;
		for (; x <= n; x += (x & -x)) bit[x] += add;
	}
	int query(int x) {
		x++;
		int ret = 0;
		for (; x; x -= (x & -x)) ret += bit[x];
		return ret;
	}
} bitL, bitId;

int main() {
	initPrimes();
	while (~scanf("%d %d", &n, &m)) {
		if (n + m == 0)
			break;
		for (int i = 1; i <= n; i++)
			scanf("%d", w + i);
		for (int j = 1; j <= m; j++)
			qry[j].init(j);
		for (int j = 1; j <= m; j++) qid[j] = j;

		sort(qid + 1, qid + m + 1, cmp);

		for (int k = 0; k < maxn; k++) pval[k] = 0;
		for (int i = 1; i <= n; i++) {
			L[i] = 0;
			int ww = w[i];
			for (int cur = minp[ww]; cur; cur = minp[ww]) {
				L[i] = max(L[i], pval[cur]);
				while (ww % cur == 0) 
					ww /= cur;
				pval[cur] = i;
			}
		}
		for (int k = 0; k < maxn; k++) pval[k] = n + 1;
		for (int i = n; i >= 1; i--) {
			R[i] = n + 1;
			int ww = w[i];
			for (int cur = minp[ww]; cur; cur = minp[ww]) {
				R[i] = min(R[i], pval[cur]);
				while (ww % cur == 0) 
					ww /= cur;
				pval[cur] = i;
			}
		}

		stR.clear();
		bitL.init(n);
		bitId.init(n);
		for (int i = 1, j = 1; i <= n; i++) {
			set<PII >::iterator it = stR.begin(), it2;
			for (; it != stR.end() && it->first == i; ++it); 

			for (it2 = stR.begin(); it2 != it; ++it2) {
				//printf("remove: %d %d\n", i, it2->second);
				bitL.update(L[it2->second], -1);
				bitId.update(it2->second, -1);
			}
			stR.erase(stR.begin(), it);
			stR.insert(MP(R[i], i));
			bitL.update(L[i], 1);
			bitId.update(i, 1);

			for (; j <= m && qry[qid[j]].r == i; j++) {
				//printf("%d %d %d %d\n", qid[j], qry[qid[j]].l, bitId.query(qry[qid[j]].l - 1), bitL.query(qry[qid[j]].l - 1));
				qry[qid[j]].res = -bitId.query(qry[qid[j]].l - 1) + bitL.query(qry[qid[j]].l - 1);
			}
		}

		for (int j = 1; j <= m; j++)
			printf("%d\n", qry[j].res);
	}
	return 0;
}
