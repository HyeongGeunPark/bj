/*
bj20495 수열과 헌팅

a_i +- b_i 꼴의 n개의 원소를 입력받는다.
이것은 각 원소가 가질 수 있는 값의 범위를 나타낸다.

이 원소들을 정렬했을 때, 각 원소가 가질 수 있는 인덱스의 최대/최소값을 출력한다.

접근: 정렬, 탐색

1. 각 원소의 최소값을 가정하여 정렬한다.
2. 각 원소의 최대값을 가정하여 정렬한다.

3. 인덱스의 최소값 찾기
	3-1. 그 원소가 최소값을 가진다고 가정한다.
	3-2. 다른 원소가 최대값을 가진다고 가정한다.
	3-3. 따라서 그 원소를 정렬된 최대값들에서 탐색하여
		앞에서 몇 번째에 있을 수 있는지 찾는다.
4. ''' 최대값 찾기
	4-1. 위와 비슷하게 찾는다.
*/

#include<iostream>
#include<vector>
#include<algorithm>

int main(void) {
	// c++ fast i/o
	std::cin.tie(0);
	std::ios_base::sync_with_stdio(false);

	int n;
	std::cin >> n;

	std::vector<int> min_values;
	std::vector<int> max_values;
}