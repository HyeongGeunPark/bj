/*
bj17404 rgb거리

다이나믹 프로그래밍 이용.
구현 편의상 초기 선택을 고정하여 dp를 세 번 수행하고,
조건에 만족하는 결과들만 고려한다.

첫번째 집에 빨간색 선택 -> 첫번째 집에 빨간색 이외의 비용을 MAX로 하여 빨간색 강제
-> dp 수행 후 마지막 집을 빨간색으로 칠하지 않은 경우에만 그 비용을 고려하여 최종 결과 갱신

-> 첫번째 집에 다른 색을 선택한 경우도 마저 계산
-> 최종 결과 출력.

*/

#include<cstdio>
#include<iostream>
#include<limits>

int mem[1000][3];
int cost[1000][3];

constexpr int MAX = 1000 * 1000 + 1;

int main() {

	int n;
	int result = MAX;

	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < 3; ++j) {
			scanf("%d", &cost[i][j]);
		} 
	}

	for (int s = 0; s < 3; ++s) {
		// initial color select
		for (int i = 0; i < 3; ++i) {
			if (i == s)
				mem[0][i] = cost[0][i];
			else
				mem[0][i] = MAX;
		}
		// dp
		for (int i = 1; i < n; ++i) {
			mem[i][0] = cost[i][0] + std::min(mem[i - 1][1], mem[i - 1][2]);
			mem[i][1] = cost[i][1] + std::min(mem[i - 1][0], mem[i - 1][2]);
			mem[i][2] = cost[i][2] + std::min(mem[i - 1][0], mem[i - 1][1]);
		}
		// result select
		for (int i = 0; i < 3; ++i) {
			if (i == s)//invalid 
				continue;
			result = std::min(result, mem[n - 1][i]);
		} 
	}

	printf("%d\n", result); 
}