// prime[i]: 1..MAX_P之间的第i个素数
// minp[i]: i的最小素因子
// MAX_P <= MAX_N <= MAX_P * MAX_P
int minp[MAX_N], prime[], pnum;
void initPrimes() {
	pnum = 0;
	minp[1] = 0;
	for (int i = 2; i <= MAX_N; i++) 
		minp[i] = i;
	for (LL i = 2; i <= MAX_P; i++) 
	if (minp[i] == i) {
		prime[pnum++] = i;
		for (LL j = i * i; j <= MAX_N; j += i) 
		if (minp[j] == j)
			minp[j] = i;
	}
}

// N = factor[0]^exp[0] * ... * factor[fnum-1]^exp[fnum-1]
// 复杂度N*sqrt(N)
void decompose(int n, int *factor, int *exp, int &fnum) {
	fnum = 0;
	for (int i = 0; (LL) prime[i] * prime[i] <= n; i++) 
	if (n % prime[i] == 0) {
		factor[fnum] = prime[i];
		exp[fnum] = 0;
		while (n % prime[i] == 0) {
			n /= prime[i];
			exp[fnum]++;
		}
		fnum++;
	}
	if (n > 1) {
		factor[fnum] = n;
		exp[fnum++] = 1;
	}
}

// 同上，复杂度N*log(N)，但是需要预处理出minp[n]是
void decompose(int n, int *factor, int *exp, int &fnum) {
	fnum = 0;
	for (int cur = minp[n]; cur; cur = minp[n]) {
		factor[fnum] = cur;
		exp[fnum] = 0;
		while (n % cur == 0) {
			n /= cur;
			exp[fnum]++;
		}
		fnum++;
	}
}

// 获得a模p的阶, 及最小的x，满足a^x = 1 mod p
int getOrder(int a, int p) {
	static int pFactor[100], pExp[100], pFnum;
	decompose(p - 1, pFactor, pExp, pFnum);
	int cur = p - 1;
	for (int i = 0; i < pFnum; i++) {
		for (int j = 0; j < pExp[i]; j++) {
			if (fastpow(a, cur / pFactor[i], p) == 1)
				cur /= pFactor[i];
		}
	}
	return cur;
}
