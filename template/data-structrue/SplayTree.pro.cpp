const int TYPE_DELETE = 1, TYPE_MAKESAME = 2, TYPE_REVERSE = 3;
const int TYPE_GETSUM = 4, TYPE_MAXSUM = 5;
const int MAX_N = 500000 + 5, INF = 1<<29;

struct Node {
	Node *son[2], *par;
	int key, sz, sum;
	int mc, lc, rc;	// max continous sum
	int same, rev;
	void init(int k, Node *s1, Node *s2, Node *p) {
		son[0] = s1; son[1] = s2; par = p;
		key = sum = mc = lc = rc = k;
		same = rev = 0;
		sz = 1;
	}
	int dir() {
		return par->son[0] == this ? 0 : 1;
	}
	void setSon(Node *s, int d) {
		son[d] = s;
		s->par = this;
	}
	void relax() {
		son[0]->update(same, key, rev);
		son[1]->update(same, key, rev);
		same = rev = 0;
	}
	void pull() {
		sum = son[0]->sum + son[1]->sum + key;
		sz = son[0]->sz + son[1]->sz + 1;
		mc = max(0, son[0]->rc) + key + max(0, son[1]->lc);
		mc = max(mc, max(son[0]->mc, son[1]->mc));
		lc = max(son[0]->lc, son[0]->sum + key + max(0, son[1]->lc));
		rc = max(son[1]->rc, son[1]->sum + key + max(0, son[0]->rc));
	}
	void update(int s, int k, int r) {
		if (s) { 
			same = s;
			key = k;
			mc = lc = rc = k > 0 ? k * sz : k;
			sum = k * sz;
		}
		if (r) { 
			swap(son[0], son[1]);
			swap(lc, rc);
			rev = rev ^ 1;
		}
	}
} *NIL;

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
	void access0(Node *x) {
		static Node *stack[MAX_N];
		int top = 0;
		while (x->par != NIL) {
			stack[top++] = x;
			x = x->par;
		}
		for (int i = top - 1; i >= 0; i--)
			stack[i]->relax();
	}
	// assert t is x's accestor;
	// splay x to t's son, if t == NIL , splay x to root;
	void splay(Node *x, Node *t = NIL) {
		NIL->son[0] = NIL->son[1] = NIL->par = NIL;	//!!
		while (x->par != t) { if (x->par->par == t)
				rotate(x);
			else if (x->dir() == x->par->dir()) {
				rotate(x->par); rotate(x);
			} else {
				rotate(x); rotate(x);
			}
		}
		if (t == NIL) root = x;
	}
	/*-------------------------basic function----------------------*/
	Node node[MAX_N], *current, *dust[MAX_N], *root;
	int dustSz;
	void init() {
		dustSz = 0;
		current = node;
		NIL = newNode(0, 0); 
		NIL->par = NIL->son[0] = NIL->son[1] = NIL;
		NIL->sz = 0;
		NIL->mc = NIL->lc = NIL->rc = -INF;
		root = NIL;
	}
	Node* newNode(int k, Node *p) {
		Node *nn = dustSz ? dust[--dustSz] : (current++);
		nn->init(k, NIL, NIL, p);
		return nn;
	}
	void eraseSubTree(Node *x) {
		if (x == NIL) return;
		eraseSubTree(x->son[0]);
		eraseSubTree(x->son[1]);
		dust[dustSz++] = x;
	}
	Node* getMin(Node *x) {
		x->relax();
		Node *ret;
		for (ret = x; ret->son[0] != NIL; ret = ret->son[0], ret->relax());
		return ret;
	}
	Node* getMax(Node *x) {
		x->relax();
		Node *ret;
		for (ret = x; ret->son[1] != NIL; ret = ret->son[1], ret->relax());
		return ret;
	}
	Node* getKth(int pos, Node *x) {
		if (x == NIL) return x;
		x->relax();	//
        int ls = x->son[0]->sz;	
        if(pos == ls + 1)
            return x;
		return pos <= ls ? getKth(pos, x->son[0]) : getKth(pos-ls-1, x->son[1]);
	}
	Node* makeTree(int key[], int l, int r, Node* p) {
		if (l > r) return NIL;
		int m = (l + r) >> 1;
		Node *x = newNode(key[m], p);
		x->son[0] = makeTree(key, l, m - 1, x);
		x->son[1] = makeTree(key, m + 1, r, x);
		x->pull();
		return x;
	}
	/*-------------For Particular Problem---------------------------*/
	// assert pos > 1 && pos + num - 1 < n
	void InsertPos(int pos, int num, int key[]) {
		Node *x = getKth(pos, root);
		splay(x);
		Node *y = getMin(x->son[1]);
		splay(y, x);
		y->son[0] = makeTree(key, 0, num - 1, y);
		x->pull();
	}
	void Update(int l, int r, int type, int *arg = NULL) {
		Node *x = getKth(l - 1, root);
		Node *y = getKth(r + 1, root);
		splay(x);
		splay(y, x);
		if (type == TYPE_DELETE) {
			eraseSubTree(y->son[0]);
			y->son[0] = NIL;
		} else if (type == TYPE_MAKESAME) {
			y->son[0]->update(1, arg[0], 0);
		} else if (type == TYPE_REVERSE) {
			y->son[0]->update(0, 0, 1);
		}
		y->pull();
		x->pull();
	}
	int Query(int l, int r, int type) {
		Node *x = getKth(l - 1, root);
		Node *y = getKth(r + 1, root);
		splay(x);
		splay(y, x);
		if (type == TYPE_GETSUM)
			return y->son[0]->sum;
		if (type == TYPE_MAXSUM)
			return y->son[0]->mc;
	}
	/*--------------------debug--------------------*/
	void traverse(Node *x, int dep) {
		if (x==NIL) return;
		x->relax();
		traverse(x->son[0], dep + 1);
		printf("%d ", x->key);
		traverse(x->son[1], dep + 1);
	}
} spt;

/*
 * init: 
 * spt.init();
 * spt.root = spt.makeTree(arr, arrL, arrR, NIL);
 */
