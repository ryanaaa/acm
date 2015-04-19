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

const int maxn = 10000 + 50;
const int dir[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
int n, par[maxn], sum[maxn];
map<int, int> del[maxn];

void merge(int x, int y) {
	FOREACH(e, del[y])
		del[x][e->first] += e->second;
}

int find(int x) {
	return x == par[x] ? x : (par[x] = find(par[x]));
}

int inside(int x, int y) {
	return x >= 1 && y >= 1;
}

int res[2];
map<PII, int> mp;
int main() {
	int test;	scanf("%d", &test);
	for (int ti = 1; ti <= test; ti++) {
		scanf("%d", &n);	

		mp.clear();
		for (int i = 0; i < n; i++) {
			par[i] = i;
			sum[i] = 0;
			del[i].clear();
		}

		for (int i = 0, curx, cury; i < n; i++) {
			scanf("%d %d", &curx, &cury);
			
			for (int di = 0; di < 4; di++) {
				int nx = curx + dir[di][0];
				int ny = cury + dir[di][1];

				int id = -1;
				if (mp.find(MP(nx, ny)) != mp.end()) {
					id = mp[MP(nx, ny)];
				}
				if (id != -1 && sum[find(id)]) {
					// have chess in (nx, ny)
					int x = find(i);
					int y = find(id);
					if ((id & 1) == (i & 1)) {
						if (x != y) {
							sum[x] += sum[y] - 1;
							par[y] = x;
							merge(x, y);
						}
					} else {
						del[y][x]++;
					}
				} else if (inside(nx, ny)) {
					int x = find(i);
					sum[x]++;
				}
			}

			int x = find(i);

			for (int di = 0; di < 4; di++) {
				int nx = curx + dir[di][0];
				int ny = cury + dir[di][1];

				int id = -1;
				if (mp.find(MP(nx, ny)) != mp.end()) {
					id = mp[MP(nx, ny)];
				}
				if (id != -1 && sum[find(id)]) {
					// have chess in (nx, ny)
					if ((id & 1) == (i & 1)) {
						;
					} else {
						int y = find(id);
						sum[y]--;
						del[x][y]++;
						if (sum[y] == 0) {
							FOREACH(e, del[y])
							if (sum[find(e->first)])
								sum[find(e->first)] += e->second;
						}
					}
				} 
			}

			if (sum[x] == 0) {
				FOREACH(e, del[x])
				if (sum[find(e->first)])
					sum[find(e->first)] += e->second;
			}

			mp[MP(curx, cury)] = i;
		}

		res[0] = res[1] = 0;
		for (int i = 0; i < n; i++) {
			int x = find(i);
			if (sum[x])
				res[i & 1]++;
		}
		printf("%d %d\n", res[0], res[1]);
	}
}
