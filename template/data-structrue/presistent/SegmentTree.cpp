const int POOL_SIZE = 0;
struct Node {
    Node *lson, *rson;
    LL sum, add;

} node[POOL_SIZE], *node0 = node, *tree[MAX_Q];

void Init() {
	node0 = node;
    tree[0] = 0;
//sz=0;
}

Node* newNode(Node *x) {
    if (x) 
		memcpy(node0, x, sizeof(node[0]));
	else
		memset(node0, 0, sizeof(node[0]));
//if (++sz >= POOL_SIZE) while (1);
	return node0++;
}

void update(Node *&rt, int segl, int segr, int ql, int qr, LL add) {
	rt = newNode(rt);
    if (ql <= segl && qr >= segr) {
        rt->sum += add * (segr - segl + 1);
        rt->add += add;
        return;
    }
    int mid = (segl + segr) >> 1;
	if (ql <= mid) update(rt->lson, segl, mid, ql, qr, add);
	if (qr > mid) update(rt->rson, mid + 1, segr, ql, qr, add);
	rt->sum = rt->add * (segr - segl + 1);
    if (rt->lson) rt->sum += rt->lson->sum;
    if (rt->rson) rt->sum += rt->rson->sum;
}

LL query(Node *rt, int segl, int segr, int ql, int qr) {
    if (!rt) return 0;
    if (ql <= segl && qr >= segr)
        return rt->sum;
    LL ret = rt->add * (qr - ql + 1);
    int mid = (segl + segr) >> 1;
    if (ql <= mid) ret += query(rt->lson, segl, mid, ql, min(mid, qr));
    if (qr > mid) ret += query(rt->rson, mid + 1, segr, max(ql, mid + 1), qr);
    return ret;
}

/*
 * update and time stamp add: tree[cur] = tree[cur - 1], update(tree[cur]..)
 * query at time t: query(tree[t])
 * back to time t: cur = t
 */
