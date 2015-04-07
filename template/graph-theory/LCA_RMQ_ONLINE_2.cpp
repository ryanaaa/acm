// 和传统的RMQ是一样的方式，但是实现起来更简单
// memory: N*LOGN 
// time-init: N*LOGN
// time-query: N*LOGN

// 2^LOG_N > MAX_N
int par[MAX_N][LOG_N], dep[MAX_N];

int cnt;
void dfs(int u, int pre) {
	par[u][0] = pre;
	for (int i = ent[u], v; ~i; i = nxt[i])
	if ((v = ver[i]) != pre) {
		dep[v] = dep[u] + 1;
		dfs(v, u);
	}
}

int LCA(int x, int y) {
	if (dep[y] > dep[x]) swap(x,y);
	for(int k = dep[x] - dep[y], i = 0; i < LOG_N; i++)
		if ((k >> i) & 1) 
			x = par[x][i];
	if (x == y) return x;
	for (int i = LOG_N - 1; i >= 0; i--) 
		if (par[x][i] != par[y][i])
			x = par[x][i], y = par[y][i];
	return par[x][0];
}

int main() {
	cnt = 0;
	dep[0] = 0;
	dfs(1, 0);
	for (int i = 1; i < LOG_N; i++)
	for (int u = 1; u <= n; u++)
		par[u][i] = par[par[u][i - 1]][i - 1];
}
