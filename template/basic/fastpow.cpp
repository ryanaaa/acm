// 使用快速幂的方式算置换
vector<int> transform(vector<int> a, vector<int> b, int n) {
	vector<int> ret(n);
	for (int i = 0; i < n; i++) ret[i] = b[a[i]];
	return ret;
}

vector<int> transformPow(vector<int> a, int n, int p) {
	vector<int> tmp(n), ret(n);
	for (int i = 0; i < n; i++) tmp[i] = a[i], ret[i] = i;
	while (p) {
		if (p & 1) ret = transform(ret, tmp, n); 
		if (p >>= 1) tmp = transform(tmp, tmp, n);
	}
	return ret;
}
