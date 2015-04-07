// 二分图最大匹配
// mx[i]：与左边集合第i个元素匹配的点
// my[i]：同上
// vis：寻找可增广轨时记录R集合中点是否已被访问过
// MAXV是值max( |L|, |R| )
// 注意：点从0开始标号的话，mx，my要初始化为-1，==0改成==-1
int mx[MAXV], my[MAXV], vis[MAXV];
int path(int u) {
	for (int v = 1; v <= cnum; v++)
	if (edge[u][v] && !vis[v]) {
		vis[v] = 1;
		if (my[v] == 0 || path(my[v])) {
			my[v] = u;
			mx[u] = v;
			return 1;
		}
	}
	return 0;
}

int maxMatch() {
	int ret = 0;
	memset(mx, 0, sizeof(mx));
	memset(my, 0, sizeof(my));
	for (int i = 1; i <= rnum; i++) {
		memset(vis, 0, sizeof(vis));
		if (mx[i] == 0)
			ret += path(i);
	}
	return ret;
}
