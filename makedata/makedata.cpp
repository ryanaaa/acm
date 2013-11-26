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
	srand(time(NULL));
	int Lx = 300, Ly = 300;
	for (int i = 0; i < Lx; i++) putchar(randInt(26) + 'A');
	putchar('\n');
	for (int i = 0; i < Ly; i++) putchar(randInt(26) + 'A');
	putchar('\n');
	return 0;
}
