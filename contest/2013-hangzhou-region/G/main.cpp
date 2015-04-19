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
typedef pair<LL, int> PLI;
#define MP(a, b) make_pair(a, b)
#define FOREACH(e,x) for(__typeof(x.begin()) e=x.begin();e!=x.end();++e)
#pragma comment(linker, "/STACK:1024000000,1024000000") 

const int MAX_N = 100000 + 50, MAX_K = 200000 + 5, MAX_BIT = 60, MAX_NODE = MAX_N * (MAX_BIT + 1);
int n, cst[MAX_N];
LL dis[MAX_N], cnt[MAX_N], sum[MAX_N], bit[MAX_BIT + 1];
priority_queue<PLI > que;

int ent[MAX_N], ver[MAX_N << 1], nxt[MAX_N << 1], ENUM;
LL len[MAX_N << 1];
void addEdge(int u, int v, LL l) {
	ver[ENUM] = v;
	len[ENUM] = l;
	nxt[ENUM] = ent[u];
	ent[u] = ENUM++;
}

struct Node {
	Node* go[2];
	LL cnt;
} node[MAX_NODE], *nodeCur, *root;

Node* newNode() {
	nodeCur->go[0] = nodeCur->go[1] = NULL;
	nodeCur->cnt = 0;
	return nodeCur++;
}

void trieInit() {
	nodeCur = node + 0;
	root = newNode();
}

void trieInsert(LL val, int cnt) {
	Node* cur = root;
	for (int i = MAX_BIT; i >= 0; i--) {
		int a = (val & bit[i]) ? 1 : 0;
		if (!(cur->go[a]))
			cur->go[a] = newNode();
		cur = cur->go[a];
	}
	cur->cnt += cnt;
}

void triePullAll(Node* cur) {
	if (cur->go[0]) {
		triePullAll(cur->go[0]);
		cur->cnt += cur->go[0]->cnt;
	}
	if (cur->go[1]) {
		triePullAll(cur->go[1]);
		cur->cnt += cur->go[1]->cnt;
	}
}

LL findKth(int u, LL rk) {
	LL val = dis[u];
	Node* cur = root;
	LL ret = 0;
	int first = 1;
	for (int i = MAX_BIT; i >= 0; i--) {
		int up = (first == 0 || (val & bit[i])) ? 1 : 0;
		int a = (val & bit[i]) ? 1 : 0;
		if (up > 0) {
			if (cur->go[a ^ 1]) {
				if (cur->go[a ^ 1]->cnt < rk) {
					rk -= cur->go[a ^ 1]->cnt;
				} else {
					a = a ^ 1;
				}
			}
		} else {
			a = 0;
		}
		if (a != up)
			first = 0;
		if (a)
			ret |= bit[i];
		cur = cur->go[a];
	}
	return ret ^ val;
}

void rec(int u, int pre) {
	for (int i = ent[u], v; ~i; i = nxt[i])
	if (pre != (v = ver[i])) {
		dis[v] = dis[u] ^ len[i];
		rec(v, u);
	}
}

LL res[MAX_K + 10];
int resCnt;
int main() {
	for (int i = 0; i <= MAX_BIT; i++) bit[i] = 1LL << i;

	while (~scanf("%d", &n) && n) {
		memset(ent, -1, sizeof(ent));
		ENUM = 0;
		LL tmpL;
		for (int i = 1, u, v; i < n; i++) {
			scanf("%d %d %lld", &u, &v, &tmpL);
			addEdge(u, v, tmpL);
			addEdge(v, u, tmpL);
		}

		rec(1, 0);
		sort(dis + 1, dis + n + 1);

		int nn = 0;
		memset(cnt, 0, sizeof(cnt));
		for (int u = 1; u <= n; u++)
			if (u == 1 || dis[u] != dis[u - 1]) {
				dis[++nn] = dis[u]; 
				cnt[nn] = 1;
			} else {
				cnt[nn]++;
			}
		n = nn;
		sum[0] = 0;
		for (int u = 1; u <= n; u++)
			sum[u] = cnt[u - 1] + sum[u - 1];
//for (int u = 1; u <= n; u++)
//	printf("dis: %lld %lld %lld\n", dis[u], cnt[u], sum[u]);


		trieInit();
		while (que.size()) que.pop();
		for (int u = 1; u <= n; u++)
			trieInsert(dis[u], cnt[u]);
		triePullAll(root);

		for (int u = 1; u <= n; u++) 
		if (sum[u]) {
			LL val = findKth(u, 1);
			que.push(MP(val, u));
//printf("push1: %lld %d\n", val, u);
		}

		int resCnt = 0;

		memset(cst, 0, sizeof(cst));
		while (resCnt < MAX_K && que.size()) {
			PLI cur = que.top();
			que.pop();
			LL val = cur.first;
			int u = cur.second;
//printf("pop: %lld %d\n", val, u);

			res[++resCnt] = val;
			res[++resCnt] = val;
			cst[u]++;
			if (cst[u] + 1 <= sum[u]) {
				LL nVal = findKth(u, cst[u] + 1);
//printf("push: %lld %d\n", nVal, u);
				que.push(MP(nVal, u));
			}
		}

		for (int u = 1; resCnt < MAX_K && u <= n; u++) {
			LL pr = (LL) cnt[u] * (cnt[u] - 1);
			while (pr-- > 0 && resCnt < MAX_K) {
				res[++resCnt] = 0;
			}
		}

		int qnum, rk;	scanf("%d", &qnum);
		while (qnum--) {
			scanf("%d", &rk);
			if (rk > resCnt)
				puts("-1");
			else
				printf("%lld\n", res[rk]);
		}
	}
	return 0;
}
