/*

bj6179 River Crossing

John이 소(1<=N<=2500)를 데리고 강을 건넌다.

뗏목을 타고 건너는데 걸리는 시간이 주어진다.

혼자 건너갈 때 M(1<=M<=1000)분이 걸린다.
여기에 소를 i마리 더 태우면 M_i(1<=M_i<=1000)분이 더 걸린다.
참고로, i<j일때 M_i<M_j이다.

John이 소와 함께 강을 건너는 데 걸리는 최소 시간을 구하시오.

입력:
N M
M_1
M_2
...
M_N

접근: 
*/

#include <iostream>
#include <memory>
//#include <vector>

int main(void) {
	// c++ fast io
	std::cin.tie(0);
	std::ios_base::sync_with_stdio(false);

	int n, m;
	std::cin >> n >> m;

	std::unique_ptr<int[]> m_arr(new int[n]);

	for (int i = 0; i < n; ++i) {
		std::cin >> m_arr[i];
	}




	


}