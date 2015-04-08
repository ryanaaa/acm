// [modify-unproved]
// low[u]: DFS tree中, u能到达深度最低的祖先
// vis[u]: inStack[u]
// 强联通缩点 Tarjan算法 O(V+E)
int low[MAXV], dfn[MAXV], id[MAXV], vis[MAXV], size[MAXV], depth, sccSz;
stack<int> S;
void Tarjan(int u) {
	dfn[u] = low[u] = depth++;
	S.push(u);
	vis[u] = 1;
	for (int i = ent[u]; ~i; i = nxt[i]) {
		int v = ver[i];
		if (dfn[v] == -1) {
			Tarjan(v);
			low[u] = min(low[u], low[v]);
		} else if (vis[v]) {
			low[u] = min(low[u], dfn[v]);
		}
	}
	if (low[u] == dfn[u]) {
		size[sccSz++] = 0;
		int v;	
		do {
			size[sccSz]++;
			v = S.top();
			S.pop();
			id[v] = sccSz;
			vis[v] = 0;
		} while (u != v);
	}
}

void SCC(int V) {
	memset(dfn, -1, sizeof(dfn));
	memset(vis, 0, sizeof(vis));
	while (S.size()) S.pop();
	sccSz = 0;
	depth = 1;
	//如果从0开始，需开成0到V。如果指定了起始点，则不用循环V。
	for (int i = 1; i <= V; i++)		
		if (dfn[i] == -1) Tarjan(i);
}
