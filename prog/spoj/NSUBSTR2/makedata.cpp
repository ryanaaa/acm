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

int randInt(int mod) {
	return (rand() % mod + mod) % mod;
}

int main() {
	int len = 10000;
	for (int i = 0; i < len; i++)
		putchar('a' + randInt(8));
	puts("");
	int qnum = 1000, QA = randInt(27), QB = randInt(26);
	printf("%d %d %d\n", qnum, QA, QB);

	for (int i = 0; i < qnum; i++) {
		int len = randInt(100) + 1;
		for (int i = 0; i < len; i++)
			putchar('a' + randInt(8));
		puts("");
	}
}
