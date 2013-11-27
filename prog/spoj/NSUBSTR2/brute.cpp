#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <vector>
using namespace std;

typedef long long LL;
typedef pair<int, int> PII;
#define MP(a, b) make_pair(a, b)
#define FOREACH(e,x) for(__typeof(x.begin()) e=x.begin();e!=x.end();++e)
#pragma comment(linker, "/STACK:1024000000,1024000000") 

const int MAX_LEN = 20000;
char T[MAX_LEN], S[MAX_LEN];
int qnum, QA, QB, LT, LS;
int main() {
	scanf("%s", T);
	LT = strlen(T);
	scanf("%d %d %d", &qnum, &QA, &QB);

	while (qnum--) {
		scanf("%s", S);
		LS = strlen(S);
		int res = 0;
		for (int i = 0; i + LS <= LT; i++) {
			int eq = 1;
			for (int j = 0; j < LS; j++)
				if (S[j] != T[i + j]) {
					eq = 0;
					break;
				}
			if (eq)
				res++;
		}
		printf("%d\n", res);
		T[LT] = 'a' + (QA * res + QB) % 26;
		LT++;
	}

	return 0;
}

