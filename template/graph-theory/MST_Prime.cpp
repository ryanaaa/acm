// Prime V^2

void Prime(int src, int edge[maxn][maxn]) {
	static int preVer[maxn], vis[maxn];
	static int lowcost[maxn];
	for (int i = 0; i < n; i++) 
		lowcost[i] = INF, preVer[i] = 0, vis[i] = 0;
	int cur = src;
	vis[cur] = 1;
	for (int count = 1; count < n; count++) {
		for (int i = 0; i < n; i++)
			if (!vis[i] && edge[cur][i] < lowcost[i]) {
				preVer[i] = cur;
				lowcost[i] = edge[cur][i];
			}
		int mn = INF;
		for (int i = 0; i < n; i++)
			if (!vis[i] && lowcost[i] < mn)
				mn = lowcost[cur = i];
		vis[cur] = 1;
		if (!hasBuild[preVer[cur]][cur])
			printf("%d %d\n", preVer[cur] + 1, cur + 1);
	}
}
