struct Node {
	Node *son[2], *par;
	LL key, keyAdd, keyMul;
	int sz, mnId, id;
	void init(int k, int i, Node *s1, Node *s2, Node *p) {
		son[0] = s1; son[1] = s2; par = p;
		key = k;
		mnId = id = i;
		sz = 1;
		keyAdd = 0;
		keyMul = 1;
	}
	int dir() {
		return par->son[0] == this ? 0 : 1;
	}
	void setSon(Node *s, int d) {
		son[d] = s;
		s->par = this;
	}
	void relax() {
		calculateOps();
		son[0]->update(keyMul, keyAdd);
		son[1]->update(keyMul, keyAdd);
		keyMul = 1;
		keyAdd = 0;
	}
	void pull() {
		sz = son[0]->sz + son[1]->sz + 1;
		mnId = min(id, min(son[0]->mnId, son[1]->mnId));
	}
	void calculateOps() {
		key = (key * keyMul + keyAdd) % MOD;
	}
	void update(LL m, LL a) {
		updateMul(m);
		updateAdd(a);
	}
	void updateAdd(LL a) {
		keyAdd = (keyAdd + a) % MOD;
	}
	void updateMul(LL m) {
		keyAdd = (keyAdd * m) % MOD;
		keyMul = (keyMul * m) % MOD;
	}
} *NIL, node[MAX_N << 1], null;

struct SplayTree {
	/*-----------------------splay's function----------------------*/
	// assert(x->par != NIL)
	void rotate(Node *x) {
		Node *y = x->par;
		y->relax();	x->relax();
		int dx = x->dir(), dy = y->dir();
		y->par->setSon(x, dy);
		y->setSon(x->son[dx ^ 1], dx);
		x->setSon(y, dx ^ 1);
		y->pull();	x->pull();
	}
	// assert t is x's accestor;
	// splay x to t's son, if t == NIL , splay x to root;
	void splay(Node *x, Node *t = NIL) {
		while (x->par != t) { if (x->par->par == t)
				rotate(x);
			else if (x->dir() == x->par->dir()) {
				rotate(x->par);
				rotate(x);
			} else {
				rotate(x);
				rotate(x);
			}
		}
	}
	// mx = 0 -> getMin, mx = 1 -> getMax
	Node* getMinMax(Node *x, int mx) {
		x->relax();
		Node *ret;
		for (ret = x; ret->son[mx] != NIL; ret = ret->son[mx], ret->relax());
		return ret;
	}

	// getNext(x, 0) = getPre, getNext(x, 1) = getSucc
	Node* getNext(Node *x, int suc) {
		if (x->son[suc] != NIL)
			return getMinMax(x->son[suc], suc ^ 1);
		Node *y = x->par;
		while (y != NIL && x == y->son[suc]) {
			x = y;		
			y = x->par;
		}
		return y;
	}
	/*-------------------------basic function----------------------*/
	Node* makeTree(int l, int r, Node* p) {
		if (l > r) return NIL;
		int m = (l + r) >> 1;
		Node *x = node + m;
		x->son[0] = makeTree(l, m - 1, x);
		x->son[1] = makeTree(m + 1, r, x);
		x->par = p;
		x->pull();
		return x;
	}
	void init() {
		NIL = &null;
		NIL->init(0, INF, 0, 0, 0);
		NIL->par = NIL->son[0] = NIL->son[1] = NIL;
		NIL->sz = 0;
	}

	LL query(int u) {
		Node *x = getNext(&node[fst[u]], 0);
		Node *y = getNext(&node[fst[u]], 1);
		splay(x);
		splay(y, x);
		x->relax();
		y->relax();
		y->son[0]->relax();
		return y->son[0]->key;
	}
	void cut(int u, LL key) {
		Node *x = getNext(&node[fst[u]], 0);
		Node *y = getNext(&node[lst[u]], 1);
		splay(x);
		splay(y, x);
		Node *z = y->son[0];
		x->relax();
		y->relax();
		z->par = NIL;
		y->son[0] = NIL;
		y->pull();
		x->pull();
		if (x->sz > z->sz || (x->sz == z->sz && x->mnId > z->mnId)) {
			x->updateAdd(key);
			z->updateMul(key);
		} else {
			x->updateMul(key);
			z->updateAdd(key);
		}
	}
	/*--------------------debug--------------------*/
	void traverse(Node *x, int dep) {
		if (x==NIL) return;
		x->relax();
		traverse(x->son[0], dep + 1);
		printf("%d ", x->id);
		vis[x->id] = 1;
		traverse(x->son[1], dep + 1);
	}
} spt;

int cnt;
void dfs(int u, int pre, int l) {
	fst[u] = ++cnt;
	node[cnt].init((LL) l, u, 0, 0, 0);
	for (int i = ent[u], v; ~i; i = nxt[i])
	if ((v = ver[i]) != pre) 
		dfs(v, u, len[i]);
	lst[u] = ++cnt;
	node[cnt].init((LL) l, u + n, 0, 0, 0);
}

void buildETT() {
	spt.makeTree(1, n + n, NIL);
}

/*---------------DEBUG------------------------*/
void debug() {
	puts("----------DEBUGSTART-----------");
	memset(vis, 0, sizeof(vis));
	for (int x = 1; x <= n + n; x++)
	if (!vis[x]) {
	Node *rt = node + x;
	while (rt->par != NIL) rt = rt->par;
		spt.traverse(rt, 0);
		puts("");
	}
	puts("----------DEBUGEND-----------");
}
