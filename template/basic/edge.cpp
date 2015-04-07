// 加边操作，一定记住初始化(edgenum = 0, memset(ent, 0))
struct Edge {
	int ver;
	Edge *nxt;
} edata[max_edgenum];
Edge *ent[maxn];
int edgenum;

void addEdge(int i, int j) {
	edata[edgenum].ver = j;
	edata[edgenum].nxt = ent[i];
	ent[i] = &edata[edgenum++];
}

// 邻接表数组形式
int ent[MAXV], ver[MAXE], nxt[MAXE], ENUM;
void addEdge(int u, int v) {
	ver[ENUM] = v;	nxt[ENUM] = ent[u];	ent[u] = ENUM++;
}

int main() {
	memset(ent, -1, sizeof(ent));
	ENUM = 0;
}
