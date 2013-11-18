#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>
using namespace std;
typedef long long LL;

const double PI = acos(-1.0);

struct Complex {
	double x, y;
	Complex() {}
	Complex(double _x, double _y): x(_x), y(_y) {}
};

inline Complex operator + (const Complex &a, const Complex &b) {
	return Complex(a.x + b.x, a.y + b.y);
}
inline Complex operator - (const Complex &a, const Complex &b) {
	return Complex(a.x - b.x, a.y - b.y);
}
inline Complex operator * (const Complex &a, const Complex &b) {
	return Complex(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x);
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

void init(Complex a[], int n, char *num, int BASE) {
	int numLen = strlen(num);
	for (int i = 0; i < n; i++)
		a[i] = Complex(0.0, 0.0);
	for (int i = 0; i < numLen; i++) 
		a[(numLen - 1 - i) / BASE].x = a[(numLen - 1 - i) / BASE].x * 10 + num[i] -'0';
}

int outInt[maxLen << 2];
char outCh[maxLen << 2];
void output(Complex a[], int n, int sig, int BPOW) {
	int outLen = 0;
	for (int i = 0; i <= n; i++)
		outInt[i] = 0;
	for (int i = 0; i < n; i++) {
		int num = (int)(a[i].x + eps);	
		outInt[i] += num % BPOW; 
		outInt[i + 1] += num / BPOW + outInt[i] / BPOW;
		outInt[i] %= BPOW;
		if (outInt[i + 1]) outLen = i + 2;
		else if (outInt[i]) outLen = i + 1;
	}
	if (!outLen) printf("0\n"); 
	else {
		if (sig) putchar('-');
		printf("%d", outInt[outLen - 1]);
		char *cur = outCh;
		while (--outLen) {
			// 这里时BASE=3, BPOW=1000时候的情况，BASE是其他情况时需另外讨论
			// better write '0' after out
			*cur++ = outInt[outLen - 1] / 100 % 10 + '0';	
			*cur++ = outInt[outLen - 1] / 10 % 10 + '0';
			*cur++ = outInt[outLen - 1] % 10 + '0';
		}
		*cur++ = 0;
		puts(outCh);
	}
}
