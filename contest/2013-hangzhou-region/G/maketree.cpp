#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
using namespace std;
typedef long long LL;

LL randLong(LL mod) {
	return (rand() * rand() % mod + mod) % mod;
}

LL randInt(int mod) {
	return (rand() % mod + mod) % mod;
}

const int MAX_N = 100000 + 5, MAX_E = MAX_N << 1, MAX_M = 100000 + 5;
int p[MAX_N], deg[MAX_N];
int ent[MAX_N], ver[MAX_E], nxt[MAX_E], ENUM;

void addEdge(int u, int v) {
//	ver[ENUM] = v;	nxt[ENUM] = ent[u];	ent[u] = ENUM++;
	printf("%d %d %lld\n", u, v, randLong(100000LL));
}

void Prufer(int n) {
	for (int u = 1; u <= n; u++)
		deg[u] = 1;
	memset(ent, -1, sizeof(ent));
	ENUM = 0;
	for (int i = 0; i < n - 2; i++)
		p[i] = randInt(n) + 1, deg[p[i]]++;
	for (int i = 0; i < n - 2; i++) {
		for (int u = 1; u <= n; u++) if (deg[u] == 1) {
			addEdge(u, p[i]);
			deg[u]--;
			deg[p[i]]--;
			break;
		}
	}
	int u1 = 0, u2 = 0;
	for (int u = 1; u <= n; u++) if (deg[u]) {
		if (u1) u2 = u;
		else u1 = u;
	}
	addEdge(u1, u2);
}

int main() {
	int test = 1;
	while (test--) {
		srand(time(NULL));
		int n = 100;
		printf("%d\n", n);
		Prufer(n);

		int m = 100;
		printf("%d\n", m);
		while (m--) {
			int rk = randInt(20000);
			printf("%d\n", rk);
		}
	}
	puts("0");

	return 0;
}
