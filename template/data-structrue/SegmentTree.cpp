const int maxn = 100000 + 50;
int n, m, quar[maxn];

struct ST {
	int cnt[maxn << 2][4];
	int invX[maxn << 2], invY[maxn << 2];	//lazy
	void init() {
		memset(cnt, 0, sizeof(cnt));
		memset(invX, 0, sizeof(invX));
		memset(invY, 0, sizeof(invY));
	}
	void build(int rt, int rtl, int rtr) {
		if (rtl == rtr) {
			cnt[rt][quar[rtl]] = 1;
			return;
		}
		int mid = (rtl + rtr) >> 1;
		build(rt << 1, rtl, mid);
		build(rt << 1 | 1, mid + 1, rtr);
		pull(rt);
	}
	void query(int rt, int rtl, int rtr, int ql, int qr, int ret[]) {
		if (ql <= rtl && qr >= rtr) {
			for (int i = 0; i < 4; i++)
				ret[i] += cnt[rt][i];
			return;
		}
		int mid = (rtl + rtr) >> 1;
		push(rt);
		if (ql <= mid) query(rt << 1, rtl, mid, ql, qr, ret);
		if (qr > mid) query(rt << 1 | 1, mid + 1, rtr, ql, qr, ret);
	}
	void update(int rt, int rtl, int rtr, int ql, int qr, int ix, int iy) {
		if (ql <= rtl && qr >= rtr) {
			updateAll(rt, ix, iy);
			return;
		}
		push(rt);
		int mid = (rtl + rtr) >> 1;
		if (ql <= mid) update(rt << 1, rtl, mid, ql, qr, ix, iy);
		if (qr > mid) update(rt << 1 | 1, mid + 1, rtr, ql, qr, ix, iy);
		pull(rt);
	}
	void push(int rt) {
		updateAll(rt << 1, invX[rt], invY[rt]);
		updateAll(rt << 1 | 1, invX[rt], invY[rt]);
		invX[rt] = invY[rt] = 0;
	}
	void pull(int rt) {
		for (int i = 0; i < 4; i++)
			cnt[rt][i] = cnt[rt << 1][i] + cnt[rt << 1 | 1][i];
	}
	void updateAll(int rt, int ix, int iy) {
		if (ix) {
			swap(cnt[rt][0], cnt[rt][1]);
			swap(cnt[rt][2], cnt[rt][3]);
			invX[rt] ^= 1;
		}
		if (iy) {
			swap(cnt[rt][0], cnt[rt][2]);
			swap(cnt[rt][1], cnt[rt][3]);
			invY[rt] ^= 1;
		}
	}
} st;
