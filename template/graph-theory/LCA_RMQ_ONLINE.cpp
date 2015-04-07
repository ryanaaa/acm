// 预处理后在线查询
// memory: V*LOGV RMQ所占
// time-init: V+E+V*LOGV
// time-query: V*LOGV
/*
 * fst是欧拉序列中u的first id, uid表示dfs的顺序
 */
int cnt2, cnt1;
void dfs(int u, int pre) {
	int uid = ++cnt1;	// dfs id
	dpt[++cnt2] = uid;	// euler id -> dfs id
	pts[uid] = u;		// dfs id -> vertex
	fst[u] = cnt2;		

	for (int i = ent[u], v; ~i; i = nxt[i])
	if ((v = ver[i]) != pre) {
		dfs(v, u);
		dpt[++cnt2] = uid; 
	}
}

int LCA(int u, int v) {
	if (fst[u] > fst[v]) swap(u, v);
	return pts[RMQ::query(fst[u], fst[v])];
}

int main() {
	RMQ::init0(MAX_N + MAX_N);

	cnt1 = cnt2 = 0;
	dfs(1, 0);
	RMQ::init(dpt, 1, n + n);
}
