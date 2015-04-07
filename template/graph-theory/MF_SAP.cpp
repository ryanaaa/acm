// SAP
const int MAXV = maxn  << 1, MAXE = (5000 + 205) << 1;
struct SAP {
	int V, src, sink;
	int cnt[MAXV], dist[MAXV];
	int ent[MAXV], ver[MAXE], nxt[MAXE], cap[MAXE], ff[MAXE], ENUM;
	
	int rec(int u, int flow) {
		if (u == sink) return flow;
		int rem = flow, mn = V;
		for (int i = ent[u], v; ~i; i = nxt[i]) {
			if (dist[u] == dist[v = ver[i]] + 1 && cap[i] > ff[i]) {
				int leave = min(rem, cap[i] - ff[i]);
				leave = rec(v, leave);
				rem -= leave;
				ff[i] += leave;
				ff[i ^ 1] -= leave;
				if (rem == 0 || dist[src] >= V)	//dist[src] or dist[u]
					return flow - rem;
			}
			if (cap[i] - ff[i])
				mn = min(mn, dist[v]);
		}
		if (rem == flow) {
			cnt[dist[u]]--;
			if (cnt[dist[u]] == 0) {
				dist[src] = V;
			} else {
				dist[u] = mn + 1;
				cnt[dist[u]]++;
			}
		}
		return flow - rem;
	}

	int exec() {
		int ret = 0;
		memset(dist, 0, sizeof(dist));
		memset(cnt, 0, sizeof(cnt));
		while (dist[src] < V) {
			int add = rec(src, INF);
			ret += add;
		}
		return ret;
	}

	void init() {
		V = n << 1;	src = Src + n;	sink = Sink;
		ENUM = 0;
		memset(ent, -1, sizeof(ent));
		reset();
	}
	void reset() { memset(ff, 0, sizeof(ff)); }

	void addEdge(int u, int v, int c) {
//printf("%d %d %d\n", u, v, c);
		ver[ENUM] = v;	cap[ENUM] = c;	nxt[ENUM] = ent[u];	ent[u] = ENUM++;
		ver[ENUM] = u;	cap[ENUM] = 0;	nxt[ENUM] = ent[v];	ent[v] = ENUM++;
	}
} sap;
