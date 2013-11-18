/*
 * Node: pull(), relax(), dir(), setSon()
 * initEnv() 初始化NIL
 * newNode() 
 */
Node *NIL, node[SZ], node0;
namespace TRP {
	void rotate(Node*& y, int s) {
		Node *x = y->son[s];
		//y->relax();	x->relax();
		y->son[s] = x->son[s ^ 1];
		x->son[s ^ 1] = y;
		y->pull();	x->pull();
		y = x;
	}
    void insertKey(Node*& rt, int k, int v) {
		if (rt == NIL) {
			rt = newNode(k, v, NIL);
		} else if (rt->key == k) 
			rt->val += v, rt->sum += v;
		else {
			int s = k > rt->key;
			insertKey(rt->son[s], k, v);
			rt->pull();
			if (rt->pri < rt->son[s]->pri)
				rotate(rt, s);
		}
    }
	int query(Node *rt, int k) {
		int ret = 0;
		while (rt != NIL) {
			if (k >= rt->key) {
				ret += rt->val + rt->son[0]->sum;
				rt = rt->son[1];
			} else
				rt = rt->son[0];
		}
		return ret;
	}
}
