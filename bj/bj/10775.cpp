/*

bj10775 공항

접근법: 그리디

i번째 비행기는 1~gi번 게이트에 도킹할 수 있다.
최대한 큰 번호의 게이트에 도킹한다.  

속도 향상을 위해 경로 압축이 필요하다.

유니온 파인드를 사용할 수도 있다. (코드 분할이 다를 뿐이다.)

*/

#include<iostream>

int next_available[100001];
inline int find_next(int i) {
	if (next_available[i] == i) {
		--next_available[i];
		return i;
	}
	// 경로 압축
	next_available[i] = find_next(next_available[i]);
	return next_available[i]; 
}

int main(void) {
	std::cin.tie(0);
	std::ios_base::sync_with_stdio(0);

	int g, p;
	int cnt = 0;
	std::cin >> g >> p;
	for (int i = 0; i <= g; ++i) {
		next_available[i] = i;
	}



	for (int i = 0; i < p; ++i) {
		int gg;
		std::cin >> gg;
		if (find_next(gg) == 0) break;
		++cnt;
	}

	std::cout << cnt; 
}