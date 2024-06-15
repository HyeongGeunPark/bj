/*

bj10942 팰린드롬?

길이 2000의 수열에서 주어진 범위가 팰린드롬인지 구하는 문제.
질문을 1,000,000개 한다.

*/
#include<iostream>
#include<cstdio>
#include<cstring>

char mem[2001][2001];
int arr[2001];

char check(int s, int e) {
	if (mem[s][e] < 0) {
		// not evaluated yet
		if (e - s < 2) {
			mem[s][e] = (arr[s] == arr[e]) ? 1 : 0;
		}
		else {
			mem[s][e] = (check(s + 1, e - 1) && ((arr[s] == arr[e]) ? 1 : 0))?1:0;
		}
	}
	return mem[s][e];
}

int main() {
	std::memset(mem, 0xFF, sizeof(char) * (2001 * 2001));

	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &arr[i]);
	}

	int m;
	scanf("%d", &m);
	for (int i = 0; i < m; ++i) {
		int s, e;
		scanf("%d%d", &s, &e);
		printf("%d\n", (int)check(s, e));
	} 
}
