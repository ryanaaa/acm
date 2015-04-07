/*
 * 	n个点，ent给出图G，rank返回每个点的排名(当然可以扩展求出拓扑序列)， maxn为点的最大个数
 * 	Top和degree函数中初始化了，所以不用管
 * 	0表示又有向环
 * 	注意事项：
 * 	虽然重边不会出错，但尽量不要加，防止Edge数组不够大
 * 	不同的方式不断处理入度为0的点，并更新其他点的入度，得到的拓扑序列意义各不一样，用栈的话类似dfs，队列的话向bfs，set的话(每次取最小的，也可以枚举)得到字典序最小的
 */

int stack[maxn], Top, degree[maxn];
int TopoSort(int n, Edge **ent, int *rank) {
	Top = 0;
	memset(degree, 0, sizeof(degree));
	for (int i = 0; i < n; i++)
		for (Edge *e = ent[i]; e; e = e->nxt)
			degree[e->ver]++;
	for (int i = 0; i < n; i++)
	if (degree[i] == 0)
		stack[Top++] = i;
	for (int count = 0; count < n; count++) {
		if (!Top) return 0;
// if (Top > 1) 拓扑序不唯一		
		int u = stack[--Top];
		rank[u] = count;
		for (Edge *e = ent[u]; e; e = e->nxt)
			if (!(--degree[e->ver]))
				stack[Top++] = e->ver;
	}
	return 1;
}

int degree[maxn];
stack<int> S;
int TopoSort(int V, int ent[], int arr[]) {
	while (S.size()) S.pop();
	memset(degree, 0, sizeof(degree));
	for (int u = 0; u < V; u++)
		for (int i = ent[u]; ~i; i = nxt[i])
			degree[ver[i]]++;
	for (int u = 0; u < V; u++)
	if (degree[u] == 0)
		S.push(u);
	for (int count = 0; count < V; count++) {
		if (!S.size()) return 0;
		int u = S.top();	S.pop();
		arr[count] = u;
		for (int i = ent[u]; ~i; i = nxt[i])
			if (!(--degree[ver[i]]))
				S.push(ver[i]);
	}
	return 1;
}
