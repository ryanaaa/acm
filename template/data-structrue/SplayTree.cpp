const int TYPE_DELETE = 1, TYPE_MAKESAME = 2, TYPE_REVERSE = 3;
const int TYPE_GETSUM = 4, TYPE_MAXSUM = 5;
const int MAX_N = 500000 + 5;

struct Node {
	Node *son[2], *par;
	int sz, keyVar;
	int lazyVar;
	int dir() {
		return par->son[0] == this ? 0 : 1;
	}
	void setSon(Node *s, int d) {
		son[d] = s;
		s->par = this;
	}
	void init(int k, Node *p);
	void relax();
	void pull();
	void update(int lazyVar);
} *NIL;

void Node::init(int k, Node *p) {
	son[0] = son[1] = NIL;
	par = p;
	sz = 1;
	//**init keyVar by k
	//**init lazyVar by k
}
void Node::relax() {
	if (this == NIL) return;
	//** update by lazy var
	son[0]->update(lazyVar);
	son[1]->update(lazyVar);
	//** clear lazy var
}
void Node::pull() {
	if (this == NIL) return;
	//** update key var by son's and this key var
	sz = son[0]->sz + son[1]->sz;
}
void Node::update(int lazyVar) {
	if (this == NIL) return;
	//** update key var
}

Node node[MAX_N], *node0, *dust[MAX_N], **dust0, *spRoot; 
void InitEnv() {
	NIL = node + 0; NIL->sz = 0;
	NIL->par = NIL->son[0] = NIL->son[1] = NIL;
	//init NIL's keyVar
	node0 = node + 1;
	dust0 = dust + 0;
	spRoot = NIL;
}
Node* newNode(int k, Node *p) {
	Node *nn = dust0 == dust + 0 ? *(--dust0) : node0++;
	nn->init(k, p);
	return nn;
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

namespace SPT {
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
		NIL->son[0] = NIL->son[1] = NIL->par = NIL;	//!!
		while (x->par != t) { 
			if (x->par->par == t) 
				rotate(x);
			else if (x->dir() == x->par->dir()) {
				rotate(x->par); rotate(x);
			} else {
				rotate(x); rotate(x);
			}
		}
		if (t == NIL) spRoot = x;
	}

	void eraseSubTree(Node *x) {
		if (x == NIL) return;
		eraseSubTree(x->son[0]);
		eraseSubTree(x->son[1]);
		*dust0 = x;	dust0++;
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
		for (; y != NIL && x == y->son[suc]; x = y, y = x->par);
		return y;
	}
	Node* getKth(int pos, Node *x) {
		if (x == NIL) return x;
		x->relax();	//
        int ls = x->son[0]->sz;	
        if(pos == ls + 1) return x;
		return pos <= ls ? getKth(pos, x->son[0]) : getKth(pos-ls-1, x->son[1]);
	}

	void InsertPos(int pos, int num, int key[]);
	void Update(int l, int r, int type, int *arg);
	int Query(int l, int r, int type);
}

// assert pos > 1 && pos + num - 1 < n
void SPT::InsertPos(int pos, int num, int key[]) {
	Node *x = getKth(pos, spRoot);
	splay(x);
	Node *y = getMinMax(x->son[1], 0);
	splay(y, x);
	y->son[0] = makeTree(key, 0, num - 1, y);
	x->pull();
}
void SPT::Update(int l, int r, int type, int *arg) {
	Node *x = getKth(l - 1, spRoot);
	Node *y = getKth(r + 1, spRoot);
	splay(x);
	splay(y, x);
	if (type == TYPE_DELETE) {
		eraseSubTree(y->son[0]);
		y->son[0] = NIL;
	} else if (type == TYPE_MAKESAME) {
		//y->son[0]->update(1, arg[0], 0);
	} else if (type == TYPE_REVERSE) {
		//y->son[0]->update(0, 0, 1);
	}
	y->pull();
	x->pull();
}
int SPT::Query(int l, int r, int type) {
	Node *x = getKth(l - 1, spRoot);
	Node *y = getKth(r + 1, spRoot);
	splay(x);
	splay(y, x);
	if (type == TYPE_GETSUM)
		return 0;//y->son[0]->sum;
	if (type == TYPE_MAXSUM)
		return 0;//y->son[0]->mc;
}

/*--------------------debug--------------------*/
void traverse(Node *x, int dep) { 
	if (x==NIL) return;
	x->relax();
	traverse(x->son[0], dep + 1);
	//printf("%d ", x->keyVar);
	traverse(x->son[1], dep + 1);
}

/*
 * need change in SplayTree:
 *		SplayTree::init();
 *		SplayTree::makeTree();	paragram need change by actrual key var
 *		SplayTree::newNode();	paragram need change by actrual key var
 * init: 
 * InitEnv();
 * spRoot = makeTree(arr, arrL, arrR, NIL);
 */
