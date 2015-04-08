// 强联通缩点 Kosaraju
// 需要ent,entInv分别索引正想边和反向边
// 用传统dfs序,kArr放在dfs0函数第一行,下面for循环按顺序就可以?
int id[MAXV], vis[MAXV], kArr[MAXV], sccSz, kCnt;
void dfs0(int u) {
	vis[u] = 1;
	for (int i = ent[u], v; ~i; i = nxt[i])
	if (!vis[v = ver[i]]) 
		dfs0(v);
	kArr[kCnt++] = u;
}

void dfs1(int u) {
	id[u] = sccSz;
	vis[u] = 1;
	for (int i = entInv[u], v; ~i; i = nxt[i])
	if (!vis[v = ver[i]])
		dfs1(v);
}

void Kosaraju(int V) {
	kCnt = 0;
	memset(vis, 0, sizeof(vis));
	for (int u = 0; u < V; u++) if (!vis[u])
		dfs0(u);
	memset(vis, 0, sizeof(vis));
	sccSz = 0;
	for (int i = V - 1; i >= 0; i--) if (!vis[kArr[i]]) {
		dfs1(kArr[i]);
		sccSz++;
	}
}
