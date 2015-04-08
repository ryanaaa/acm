// 无向图双连通分量（并查集差维护每个分量，vector<PII >保存桥）
// 桥(bridge): 删除就不连通了
// 割点(isolated vertex): 删除图就不连通了
// (不考虑重边，即加入邻接表时有重边和没有一样)
int low[MAXV], dfn[MAXV], vis[MAXV], depth;
void Tarjan(int u, int pre) {
	dfn[u] = low[u] = depth++;
	vis[u] = 1;
	for (int i = ent[u], v; ~i; i = nxt[i]) 
	if (pre != (v = ver[i])) {
		if (vis[v] == 0) {
			Tarjan(v, u);
			low[u] = min(low[u], low[v]);
			if (low[v] <= dfn[u]) 
				Union(u, v);	
			else 
				bridge.push_back(MP(u, v));
			// if ((u==root && edge(u) > 1) || (u != root && low[v] >= dfn[u])) u is isolated vertex
		} else 
			low[u] = min(low[u], dfn[v]);
	}
}

void ESCC(int V) {
	memset(vis, 0, sizeof(vis));
	depth = 1;
	bridge.clear();
	for (int u = 1; u <= V; u++)
		par[u] = u;
	Tarjan(1, 0); // 若图不连通需循环
}
