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

LL randLL(LL mod) {
	return (rand() % mod + mod) % mod;
}

int main() {
	int n = 1000000;
	printf("%d\n", n);
	for (int i = 0; i < n; i++)
		printf("%lld ", randLL(1000000000000LL) + 1);
	return 0;
}
