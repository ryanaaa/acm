/*
 * 递归写法
 */
void dfs(int u, int pre) {
	//** Pa
	for (int i = ent[u], v; ~i; i = nxt[i])
	if ((v = ver[i]) != pre) {
		//** Pb
		dfs(v, u);
		//** Pc
	}
	//** Pd
}

/*
 * 栈模拟，不能处理Pc
 */
void dfs(int root) {
	static int stk[MAX_N << 1], par[MAX_N], top;
	top = 0;
	par[root] = 0;
	stk[top++] = root << 1 | 1;
	stk[top++] = root << 1;
	while (top) {
		int u = stk[--top], f = u & 1;
		u >>= 1;
		if (f) {
			//** Pd
			continue;
		}
		//** Pa
		for (int i = ent[u], v; ~i; i = nxt[i])
		if ((v = ver[i]) != par[u]) {
			par[v] = u;
			stk[top++] = v << 1 | 1;
			stk[top++] = v << 1;
			//** Pb
		}
	}
}
