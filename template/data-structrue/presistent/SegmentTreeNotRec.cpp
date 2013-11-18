/*
 * struct Node 省略
 * update: 单点更新的循环版
 * query: u,v,a为三棵主席树, 查询u+v-2a上的第K大值的循环版
 * 还可以不用递归的是单点查询
 */
namespace ST {
	void init() {
		node0 = node;
		tree[0] = 0;
	}
	void update(Node *rt, int segl, int segr, int x, int add) {
		while (1) {
			rt->sum += add;
			if (segl == segr) 
				break;
			int mid = (segl + segr) >> 1;
			if (x <= mid) {
				rt->lson = newNode(rt->lson);
				rt = rt->lson;
				segr = mid;
			} else {
				rt->rson = newNode(rt->rson);
				rt = rt->rson;
				segl = mid + 1;
			}
		}
	} 
	int query(Node *u, Node *v, Node *a, int arnk, int k) {
		int ll = 1, rr = wcnt, mm;
		while (ll < rr) {
			mm = (ll + rr) >> 1;
			int t = (arnk >= ll && arnk <= mm);
			if (u && u->lson) t += u->lson->sum;
			if (v && v->lson) t += v->lson->sum;
			if (a && a->lson) t -= (a->lson->sum + a->lson->sum);
			if (t >= k) {
				if (u) u = u->lson;
				if (v) v = v->lson;
				if (a) a = a->lson;
				rr = mm;
			} else {
				k -= t;
				if (u) u = u->rson;
				if (v) v = v->rson;
				if (a) a = a->rson;
				ll = mm + 1;
			}
		}
		return ll;
	}
}
