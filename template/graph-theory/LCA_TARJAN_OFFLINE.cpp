// Tarjan求LCA以及其DP
// 每次要查询链u到v的某个函数值
vector<PII > lst[MAX_N];	//lst[u]保存包含u的查询的v值和查询id
PII qry[MAX_Q];			//qry[i]表示第i个查询的u,v
int Find(int u) {
	if (par[u] != u) {
		int pu = par[u];
		par[u] = Find(pu);
		//更新F(u)表示u到par[u]的dp值
		up[u] = max(Max[pu] - Min[u], max(up[pu], up[u]));
		dn[u] = max(Max[u] - Min[pu], max(dn[pu], dn[u]));
		Max[u] = max(Max[pu], Max[u]);
		Min[u] = min(Min[pu], Min[u]);
	}
	return par[u];
}

//lca[u]保存以u为lca的查询标号
vector<int> lca[MAX_N];
void Tarjan(int u, int pre) {
	vis[u] = 1;
	FOREACH(e, lst[u])
	if (vis[(*e).first]) 
		//计算出LCA
		lca[Find((*e).first)].push_back((*e).second);

	for (int i = ent[u], v; ~i; i = nxt[i])
	if ((v = ver[i]) != pre) {
		Tarjan(v, u);
		par[v] = u;
	}

	FOREACH(e, lca[u]) {
		int i = (*e);
		int x = qry[i].first, y = qry[i].second;
		Find(x);
		Find(y);
		//计算第i个query的dp值
		res[i] = max(Max[y] - Min[x], max(up[x], dn[y]));
	}
}
