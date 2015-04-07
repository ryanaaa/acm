const int MAXV = 2 * maxn * maxn, MAXE = maxn * maxn * 8;
struct MinCost {
	int V, dist[MAXV], vis[MAXV], pre[MAXV];
	int ent[MAXV], ver[MAXE], nxt[MAXE], len[MAXE], cap[MAXE], ENUM;
	
	void init() {
		V = size * 2 + 2;	
		ENUM = 0;
		memset(ent, -1, sizeof(ent));
	}

	int SPFA(int src, int sink) {
		static queue<int> Q;
		for (int i = 0; i < V; i++)
			dist[i] = -INF, vis[i] = 0, pre[i] = -1;
		dist[src] = 0;
		Q.push(src);	vis[src] = 1;
		while (Q.size()) {
			int u = Q.front();	Q.pop();
			for (int i = ent[u], v; ~i; i = nxt[i])
			if (cap[i] && dist[v = ver[i]] < dist[u] + len[i]) {
				dist[v] = dist[u] + len[i];
				pre[v] = i;
				if (!vis[v])
					Q.push(v), vis[v] = 1;
			}
			vis[u] = 0;
		}
		return dist[sink] != -INF;
	}

	int exec(int src, int sink) {
		int cost = 0, flow = 0;
		while (SPFA(src, sink)) {
			int neck = INF;
			for (int i = pre[sink]; ~i; i = pre[ver[i ^ 1]])
				neck = min(neck, cap[i]);
			flow += neck;
			for (int i = pre[sink]; ~i; i = pre[ver[i ^ 1]]) {
				cap[i] -= neck;
				cap[i ^ 1] += neck;
				cost += neck * len[i];
			}
		}
		return cost;
	}

	void addEdge(int u, int v, int c, int l) {
//printf("%d %d %d\n", u, v, c);
		ver[ENUM] = v;	cap[ENUM] = c;	nxt[ENUM] = ent[u];	
		len[ENUM] = l;	ent[u] = ENUM++; 
		ver[ENUM] = u;	cap[ENUM] = 0;	nxt[ENUM] = ent[v];	
		len[ENUM] = -l;	ent[v] = ENUM++;
	}
} mc;
