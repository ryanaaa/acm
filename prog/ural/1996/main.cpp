#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>
using namespace std;
typedef long long LL;

const int maxn = 250000 + 50;
const double PI = acos(-1.0);
const double eps = 1e-6;

int n, m;
int a[maxn], aa[maxn], b[maxn], bb[maxn], lcp1[maxn], lcp2[maxn];
int res[maxn];

struct Complex {
	double x, y;
	Complex() {}
	Complex(double _x, double _y): x(_x), y(_y) {}
} ca[maxn << 1], cb[maxn << 1];

inline Complex operator + (const Complex &a, const Complex &b) {
	return Complex(a.x + b.x, a.y + b.y);
}
inline Complex operator - (const Complex &a, const Complex &b) {
	return Complex(a.x - b.x, a.y - b.y);
}
inline Complex operator * (const Complex &a, const Complex &b) {
	return Complex(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x);
}

void exKMP(int T[], int M, int S[], int N, int lcp1[], int lcp2[]) {
	int tr, sl, sr;
	if (T != S) {
		for (tr = 0, sr = 0; tr < N && sr < M && T[tr] == S[sr]; tr++, sr++);
		lcp2[0] = tr;
		sl = 0;
	} else if (N > 1) {
		for (tr = 0, sr = 1; tr < N && sr < M && T[tr] == S[sr]; tr++, sr++);
		lcp2[1] = tr;
		sl = 1;
	}
	for (int i = sl + 1; i < N; i++) {
		if (sr < i || i + lcp1[i - sl] >= sr) {
			tr = sr - i;
			if (tr < 0)
				tr = 0, sr = i;
			for (; sr < N && tr < M && S[sr] == T[tr]; sr++, tr++);
			lcp2[i] = tr;
			sl = i;
		} else 
			lcp2[i] = lcp1[i - sl];
	}
}

void FFT(Complex a[], int n, int inv) {
	for (int i = 0, refI, j; i < n; i++) {
		for (refI = 0, j = 1; j < n; j <<= 1)
			refI = (refI << 1) | ((i & j) > 0);
		if (refI > i) swap(a[i], a[refI]);	
	}

	for (int len = 2; len <= n; len <<= 1) {
		Complex E = Complex(cos(PI * 2 / len), sin(PI * 2 / len));
		if (inv) E.y = -E.y;
		for (int i = 0; i < n; i += len) {
			Complex w = Complex(1.0, 0.0);
			for (int j = 0; j + j < len; j++) {
				int k1 = i + j, k2 = i + j + len / 2;
				Complex tmp1 = a[k1], tmp2 = w * a[k2];
				a[k1] = tmp1 + tmp2;
				a[k2] = tmp1 - tmp2;
				w = w * E;
			}
		}
	}
	
	if (inv) for (int i = 0; i < n; i++) a[i].x /= n, a[i].y /= n;
}

void work(int flag) {
	int nn = max(n, m);
	while (nn & (nn - 1)) nn += (nn & -nn);
	for (int i = 0; i < nn; i++) {
		ca[i].x = 0;
		ca[i].y = 0;
		if (i < n)
			ca[i].x = aa[n - 1 - i] == flag ? 0 : 1;
	}
	for (int i = 0; i < nn; i++) {
		cb[i].x = 0;
		cb[i].y = 0;
		if (i < m)
			cb[i].x = bb[i] == flag ? 1 : 0;
	}
	FFT(ca, nn, 0);
	FFT(cb, nn, 0);
	for (int i = 0; i < nn; i++)
		ca[i] = ca[i] * cb[i];
	FFT(ca, nn, 1);

	for (int i = 0; i < n; i++)
		res[i] += (int)(ca[n - i - 1].x + eps);
}

char tmp[100];
int main() {
	scanf("%d %d", &n, &m);
	
	for (int i = 0; i < n; i++) {
		scanf("%s", tmp);
		a[i] = 0;
		aa[i] = tmp[7] == '1';
		for (int j = 0; j < 7; j++)
			a[i] = a[i] << 1 | (tmp[j] == '1' ? 1 : 0);
	}

	for (int i = 0; i < m; i++) {
		scanf("%s", tmp);
		b[i] = 0;
		bb[i] = tmp[7] == '1';
		for (int j = 0; j < 7; j++)
			b[i] = b[i] << 1 | (tmp[j] == '1' ? 1 : 0);
	}

	exKMP(b, m, b, m, lcp2, lcp2);
	exKMP(b, m, a, n, lcp2, lcp1);
	memset(res, 0, sizeof(res));
	work(0);
	work(1);

	int minResult = 0x3f3f3f3f, minI = -1;
	for (int i = 0; i < n; i++)
	if (lcp1[i] == m) {
		if (res[i] < minResult) {
			minResult = res[i];
			minI = i;
		}
	}

	if (minI == -1)
		puts("No");
	else
		printf("Yes\n%d %d\n", minResult, minI + 1);

	return 0;
}
