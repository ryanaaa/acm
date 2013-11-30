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
typedef pair<LL, int> PLI;
#define MP(a, b) make_pair(a, b)
#define FOREACH(e,x) for(__typeof(x.begin()) e=x.begin();e!=x.end();++e)
#pragma comment(linker, "/STACK:1024000000,1024000000") 

priority_queue<PLI > que;
int main() {
	que.push(MP(1LL, 2));
	que.push(MP(3LL, 1));

	while (que.size()) {
		PLI cur = que.top();
		que.pop();
		printf("%lld %d\n", cur.first, cur.second);
	}
	return 0;
}
