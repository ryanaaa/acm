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

const int MAX_B = 21, MAX_G = 8, INF = 0x3f3f3f3f;
int G, B, S;
int gem[MAX_B][MAX_G], dp[1 << MAX_B];//, cnt[1 << MAX_B][MAX_G];


int cnt[MAX_G];
int main() {
	while (~scanf("%d %d %d", &G, &B, &S)) {
		if (G + B + S == 0)
			break;
		memset(gem, 0, sizeof(gem));
		for (int i = 0; i < B; i++) {
			int num, t;	scanf("%d", &num);
			while (num-- > 0) {
				scanf("%d", &t);
				gem[i][t - 1]++;
			}
		}

		int ALL = (1 << B) - 1;
		dp[0] = 0;
		memset(cnt, 0, sizeof(cnt));
		for (int s = 1; s <= ALL; s++) {
			dp[s] = -0x3f3f3f3f;
			for (int j = 0; j < MAX_G; j++) {
				cnt[j] = 0;
				for (int i = 0; i < MAX_B; i++) 
				if ((s & (1 << i)) == 0)
					cnt[j] += gem[i][j];
				cnt[j] %= S;
			}
			for (int i = 0; i < B; i++)
			if (s & (1 << i)) {
				int add = 0;
				for (int j = 0; j < G; j++)
					add += (gem[i][j] + cnt[j]) / S;
				int tmp = add ? (add + dp[s ^ (1 << i)]) : (add - dp[s ^ (1 << i)]);
				dp[s] = max(dp[s], tmp);
			}
			//for (int j = 0; j < G; j++)
			//	printf("%d ", cnt[j]);
			//puts("");
		}
		
		printf("%d\n", dp[ALL]);
	}
}
