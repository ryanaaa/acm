// Dijskra + 堆优化 ((V + E)logV + E)
// 不能有负权边
double Dijaskra(int src, int ent[]) {
	static priority_queue<PII > Q;
	static int vis[maxn], dis[maxn];
	memset(vis, 0, sizeof(vis));
	for (int i = 1; i <= n; i++)
		dis[i] = INF;
	while (Q.size()) Q.pop();
	dis[src] = 0;
	Q.push(MP(0, src));
	int ret = 0;
	for (int count = 0; count < n; ) {
		PII node = Q.top();
		Q.pop();
		int u = node.second;
		if (vis[u]) continue;
		count++;
		ret -= node.first;
		vis[u] = 1;
		for (int i = ent[u], v; i != -1; i = nxt[i])
		if (!vis[v = ver[i]])
			if (dis[v] > dis[u] + len[i]) {
				dis[v] = dis[u] + len[i];
				Q.push(MP(-dis[v], v));
			}
	}
	return ret;
} 
