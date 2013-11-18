struct Node {
    Node *son[2], *par;
	int sz, key, mx;
	int rev, add;	//lazy
	int dir() {
		if (par->son[0] == this) return 0;
		if (par->son[1] == this) return 1;
		return 2;
	}
	void setSon(Node *s, int d) {
		if (d == 0 || d == 1) son[d] = s;
		s->par = this;
	}
	void init(int k, Node *null) {
		key = mx = k;
		son[0] = son[1] = par = null;
		sz = 1;
		rev = add = 0;
	} 
	void relax();
	void pull();
	void update(int r, int a);
} *NIL;

void Node::update(int r, int a) {
	if (this == NIL) return;
	if (r) {
		rev ^= 1;
		swap(son[0], son[1]);
	}
	if (a) {
		add += a;
		key += a;	mx += a;
	}
}
void Node::relax() {
	if (this == NIL) return;
	son[0]->update(rev, add);
	son[1]->update(rev, add);
	rev = add = 0;
}
void Node::pull() {
	if (this == NIL) return;
	mx = max(key, max(son[0]->mx, son[1]->mx));
	sz = 1 + son[0]->sz + son[1]->sz;
}

Node node[maxn];
struct SplayTree {
	// assert(x->par != NIL)
	void rotate(Node *x) {
		Node *y = x->par;
		y->relax();	x->relax();
		int dx = x->dir(), dy = y->dir();
		y->par->setSon(x, dy);	//!!!
if (dx == 2) while (1);
		y->setSon(x->son[dx ^ 1], dx);
		x->setSon(y, dx ^ 1);
		y->pull();	x->pull();
	}
	void splay(Node *x) {
		if (x == NIL) return;
		NIL->son[0] = NIL->son[1] = NIL->par = NIL;
		x->relax();
		while (x->dir() != 2) {
			if (x->par->dir() == 2)
				rotate(x);
			else if (x->dir() == x->par->dir()) {
				rotate(x->par); rotate(x);
			} else {
				rotate(x); rotate(x);
			}
		}
		x->pull();
	}
	void access0(Node *x) {
		static Node *stack[MAX_N];
		int top = 0; while (x->par != NIL) {
			stack[top++] = x;
			x = x->par;
		}
		for (int i = top - 1; i >= 0; i--)
			stack[i]->relax();
	}
	// after acess, x->son[0] = NIL
    void access(Node *x) {
        access0(x);
        for (Node *v = NIL, *u = x; u != NIL; u = u->par) {
            splay(u);
            u->son[0] = v;  v->par = u;
            v = u;
			v->pull();
        }
		// x is in the top-level solid tree, v is root, u is NIL
        splay(x);
    }
    Node* findRoot(Node* x) {
        access(x);
        while (x->son[1] != NIL) x = x->son[1];
        return x; 
	}
	// make x is root of its tree, and y is x's parent
    void link(Node *x, Node* y) {
        if (findRoot(x) != x)
            evert(x);
        access(x);
        access(y);
        x->par = y;
    }
    void cut(Node *x) {
        access(x);
		x->relax();	//
        x->son[1]->par = NIL;
        x->son[1] = NIL;
		x->pull();
    }
    void evert(Node *x) {
        if (findRoot(x) == x) return;
        access(x);
		x->relax();	//
        x->son[0] = NIL;
		x->pull();
		x->update(1, 0);
    }

    void init() {
        //init properly is Important
        NIL = &node[0];
        NIL->son[0] = NIL->son[1] = NIL->par = NIL;
        NIL->sz = NIL->mx = NIL->key = NIL->add = NIL->rev = 0;    
    }

	// u is root, and LCA of x and y
	// u->son[0] is x->u's chain, v is y->u's chain
	// if LCA is x: x->son[0]==NIL, is y: v=NIL
    int queryChain(Node *x, Node* y) {
        access(x);
        for (Node *v = NIL, *u = y; u != NIL; u = u->par) {
            splay(u);
            if (u->par == NIL) {
				u->relax();	//
                int ret = max(u->key, max(u->son[0]->mx, v->mx));
                return ret;
            }
            u->son[0] = v;     v->par = u;
            v = u;
			v->pull();
        }
        return 0;
    }
    void updateChain(Node *x, Node* y, int w) {
        int ret = 0;
        access(x);
        for (Node *v = NIL, *u = y; u != NIL; u = u->par) {
            splay(u); 
			if (u->par == NIL) { 
				u->key += w;
				u->son[0]->update(0, w);
                v->update(0, w);
				u->pull();
                break;
            }
            u->son[0] = v;     v->par = u;
            v = u;
			v->pull();
        }
    }

} spt;

int que[maxn], qL, qR, vis[maxn];
void bfsBuildTree(int rt) {
    memset(vis, 0, sizeof(vis));
	node[rt].init(wgt[rt], NIL);
    qL = qR = 0;
    que[qR++] = rt;
    vis[rt] = 1;
    while (qL < qR) {
        int u = que[qL++], v;
        for (int i = ent[u]; i != -1; i = nxt[i])
        if (!vis[v = ver[i]]) {
			node[v].init(wgt[v], NIL);
            node[v].par = &node[u];
            vis[v] = 1;
            que[qR++] = v;
        }
    }
}
/*
 * spt.init();
 * bfsBuildTree(root);
 */
