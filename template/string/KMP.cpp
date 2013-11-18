#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>
using namespace std;
typedef long long LL;

void exKMP(char T[], int M, char S[], int N, int lcp1[], int lcp2[]) {
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

int main() {
	char a[] = "abaabc";
	char b[] = "aba";
	int lcp1[10];
	int lcp2[10];
	exKMP(b, 3, b, 3, lcp1, lcp1);
	exKMP(b, 3, a, 5, lcp1, lcp2);
	for (int i = 0; i < 3; i++)
		printf("%d ", lcp1[i]);
	puts("");
	for (int i = 0; i < 5; i++)
		printf("%d ", lcp2[i]);
	puts("");
	return 0;
}
