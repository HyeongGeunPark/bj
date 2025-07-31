/*
bj1106 호텔

입력 인자 조건
1 <= c <= 1000
1 <= n <= 20
1 <= buf[i][0], buf[i][1] <= 100 

dp
index = 비용
dp[i] = 비용 i를 지불했을 때 얻을 수 있는 최대 고객 수

*/

#include <iostream>

int main(void) {
	// c++ fast io
	std::cin.tie(0);
	std::ios_base::sync_with_stdio(0);

	// input
	int c, n;
	int buf[1000][2] = { 0, };

	std::cin >> c >> n;

	for(int i=0;i<n;++i) {
		std::cin >> buf[i][0] >> buf[i][1];
	}

	// process


	// output

}