/*
 * 2^LOG_N > MAX_N
 */
namespace RMQ {
	int rq[LOG_N][MAX_N], lg[MAX_N];
	void init0(int n) {
		lg[0] = -1;
		for (int i = 1; i < n; i++) 
			lg[i] = (i & (i - 1)) == 0 ? lg[i - 1] + 1 : lg[i - 1];
	}
	void init(int v[], int s, int e) {
		for (int i = s; i <= e; i++) rq[0][i] = v[i];
		for (int t = 1, _t = lg[e - s + 1], j = 1, bit = 1; t <= _t; t++, bit <<= 1) {
			for (int i = s; i <= e; i++) 
				if (i + bit <= e) rq[t][i]= min(rq[t - 1][i], rq[t - 1][i + bit]);
				else rq[t][i] = rq[t - 1][i];
		}
	}
	int query(int l, int r) {
		int m = lg[r - l + 1];
		return min(rq[m][l], rq[m][r - (1 << m) + 1]);
	} 
}

