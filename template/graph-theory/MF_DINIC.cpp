// Dinic (V^2E 实际差不多sqrt(VE))
// init，每次冲新构图前调用
// 每次求新的最大流前调用，（入一个case里每次只是修改几个cap重新求最大流，如求最小割点集）
const int MAXV = maxn << 1, MAXE = (5000 + 205) << 1;
struct Dinic {
	int V, src, sink, que[MAXV], qL, qR, dist[MAXV];
	int cur[MAXV], ent[MAXV], ver[MAXE], nxt[MAXE], cap[MAXE], ff[MAXE], ENUM;
	
	int rec(int u, int flow, int sink) {
		if (u == sink) return flow;
		for (int i = cur[u], v; ~i; i = nxt[i], cur[u] = i) 
		if (dist[v = ver[i]] == dist[u] + 1 && cap[i] > ff[i]) {
			int ret = rec(v, min(flow, cap[i] - ff[i]), sink);
			if (ret) {
				ff[i] += ret;
				ff[i ^ 1] -= ret;
				return ret;
			}
		}
		dist[u] = -1;
		return 0;
	}

	int exec(int src, int sink) {
		int ret = 0;
		while (1) {
			for (int i = 0; i < V; i++)
				dist[i] = MAXV, cur[i] = ent[i];
			dist[src] = 0;
			qL = qR = 0;
			que[qR++] = src;
			//dist[sink]==MAXV is an optimization
			while (qL < qR && dist[sink] == MAXV) {
				int u = que[qL++], v;
				for (int i = ent[u]; i != -1; i = nxt[i]) 
				if (cap[i] > ff[i] && dist[v = ver[i]] == MAXV) {
					dist[v] = dist[u] + 1;
					que[qR++] = v;
				}
			}
			if (dist[sink] == MAXV) break;
			int flag = 0;
			while (1) {
				int add = rec(src, INF, sink);
				if (!add) break;
				ret += add;
				flag = 1;
			}
			if (!flag) break;
		}
		return ret;
	}

	void init(int _V) {
		V = _V;
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
} dinic;
