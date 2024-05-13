/*

bj1799 비숍

정사각형 체스판의 빈 칸에 비숍을 서로 잡을 수 없는 위치에 배치한다.
최대 몇 개의 비숍을 배치할 수 있는가?

입력:
체스판의 크기 N
체스판의 상태 (1 = 빈 칸, 0 = 비숍을 놓지 못하는 칸)

접근법: 전수탐색, 백트래킹

dfs로 모든 경우를 탐색한다.
더 이상 비숍을 배치하지 못하게 되었을 때 현재까지 놓은 비숍의 갯수를 저장한다.

각 대각선에 하나의 비숍만 들어갈 수 있다는 점을 이용한다.

흰색 칸에 놓인 비숍은 오직 흰색 칸에만 영향을 미치고,
검은색 칸에 놓인 비숍은 오직 검은색 칸에만 영향을 미치므로
문제를 흰색 칸과 검은색 칸에 대해 각각 풀 수도 있다.
*/


#include<iostream>
#include<limits> 

int n;
bool diag1[20];
bool diag2[20];

/*	
	0	1	2	3	4	5	6 -> diag1[2n-1]
	/	/	/	/	/	/	/
	0	0	0	0 /   /   /
	0	0	0	0/ /   /
	0	0	0	0/  /
	0	0	0	0/
	\	\	\	\	\	\	\
	0	1	2	3	4	5	6 -> diag2[2n-1]

	x = index of diag1 = i + j
	y = index of diag2 = -i + j + n - 1
 
*/

int map[10][10];

int result = 0;
void DFS(int depth, int num) {
	if (depth >= (2 * n - 1)) {
		result = std::max(result, num);
		return;
	} 

	bool flag = true;
	for (int i = 0; i < n; ++i) {
		int j = depth - i;
		if (j < 0 || j >= n) continue; // out of range

		if (map[i][j] == 1 && !diag2[-i + j + n - 1]) {
			flag = false;
			diag2[-i + j + n - 1] = true;
			DFS(depth + 2, num + 1);
			diag2[-i + j + n - 1] = false;
		}
	} 
	if (flag) {
		DFS(depth + 2, num);
	} 
}

int solve() {
	DFS(0, 0);
	int ans = result;
	result = 0;
	DFS(1, 0);
	ans += result;
	return ans; 
}


int main(void) {
	std::cin >> n; 

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			std::cin >> map[i][j];
		}
	}

	std::cout << solve(); 
}
