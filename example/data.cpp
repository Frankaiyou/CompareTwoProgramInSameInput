#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>


void PUT(int n) {printf("%d\n", n);}
void PUTK(int n){printf("%d  ", n);}
int ZF(int n) {if (rand() % 2) return n; else return -n;}

int main () {
	int n, m;
	srand(time(0) + 20011212);
	n = 15;
	PUT(n);
	for (int i = 1; i <= n; i += 1)
		PUTK(ZF(rand() % 10 + 1));
	puts("");
	PUT(m = 15);
	for (int i = 1; i <= m; i += 1) {
		int l = rand() % n + 1;
		int r = rand() % n + 1;
		while (r < l) r = rand() % n + 1;
		PUTK(l), PUT(r);
	}
	return 0;
}