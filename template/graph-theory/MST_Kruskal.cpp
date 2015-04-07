// Kruskal (ElogV)

int Find(int x) {
	if (x == par[x]) return x;
	return par[x] = Find(par[x]);
}

double Kruskal(int n, int eord, Edge *edge) {
	double wsum = 0;
	sort(edge, edge + eord);
	for (int i = 0, u, v, size = 0; size < n - 1 && i < eord; i++) {
		int x = Find(u = edge[i].u);
		int y = Find(v = edge[i].v);
		if (x != y) {
			par[x] = y;
			wsum += edge[i].wgt;
			size++;
		}
	}
	return wsum;
}
