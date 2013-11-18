struct NodeY {
	NodeY *lson, *rson;
	int sum;
	NodeY() { lson = rson = 0; sum = 0; }
};
struct NodeX {
    NodeX *lson, *rson;
	NodeY *ny;
	NodeX() { lson = rson = 0; ny = 0; }
};

NodeX *root;
namespace ST {
	void updateY(NodeY *rt, int y, int a) {
		int segl = 0, segr = n, mid;
		while (segl < segr) {
			rt->sum += a;
			mid = (segl + segr) >> 1;
			if (y <= mid) {
				segr = mid;
				if (!rt->lson) rt->lson = new NodeY();
				rt = rt->lson;
			} else {
				segl = mid + 1;
				if (!rt->rson) rt->rson = new NodeY();
				rt = rt->rson;
			}
		}
		rt->sum += a;
	}
	void updateX(NodeX *rt, int x, int y, int a) {
//printf("UpdateX: %d %d %d\n", x, y, a);
		int segl = 1, segr = n, mid;
		while (segl < segr) {
			if (!rt->ny) rt->ny = new NodeY();
			updateY(rt->ny, y, a);

			mid = (segl + segr) >> 1;
			if (x <= mid) {
				segr = mid;
				if (rt->lson == NULL) rt->lson = new NodeX();
				rt = rt->lson;
			} else {
				segl = mid + 1;
				if (rt->rson == NULL) rt->rson = new NodeX();
				rt = rt->rson;
			} 
		}
		if (!rt->ny) rt->ny = new NodeY();
		updateY(rt->ny, y, a);
	}
	int queryY(NodeY *rt, int yr) {
		int segl = 0, segr = n, mid, ret = 0;
		while (segl < segr && segl <= yr && rt) {
			mid = (segl + segr) >> 1; 
			if (yr > mid) {
				ret += rt->lson ? rt->lson->sum : 0;
				rt = rt->rson;
				segl = mid + 1;
			} else {
				rt = rt->lson;
				segr = mid;
			}
		}
		if (rt && segl <= yr) ret += rt->sum;
		return ret;
	}
	int queryX(NodeX *rt, int xr, int yr) {
		int segl = 1, segr = n, mid, ret = 0;
		while (segl < segr && segl <= xr && rt) {
			mid = (segl + segr) >> 1;
			if (xr > mid) {
				if (rt->lson) 
					ret += queryY(rt->lson->ny, yr);
				rt = rt->rson;
				segl = mid + 1;
			} else {
				rt = rt->lson;
				segr = mid;
			}
		}
		if (rt && segl <= xr) ret += queryY(rt->ny, yr);
//printf("QueryX: %d %d %d\n", xr, yr, ret);
		return ret;
	}
}

