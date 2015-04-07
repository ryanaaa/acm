// Bellman Ford (VE)
void Bellman(int src) {
	for (int i = 1; i <= n; i++)
		dis[i] = INF;
	dis[src] = 0;
	for (int count = 0; count < n; count++) 
	for (int u = 1; u <= n; u++)
	for (int i = ent[u], v; ~i; i = nxt[i]) 
	if (dis[v = ver[i]] != INF) {
		int tmp = dis[v] + len[i];
		dis[u] = min(dis[u], tmp);
	}
}
