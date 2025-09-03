/*
bj3013 부분 수열의 중앙값

1부터 N까지 자연수 N개로 이루어진 수열 A가 있다. 각 자연수는 수열에서 한 번씩만
등장한다.

A의 부분 수열은 A의 앞과 뒤에서 숫자를 제거해서 만들 수 있다.
길이가 홀수이면서 중앙값이 B인 A의 부분 수열의 개수를 구하는 프로그램을 작성하시오.

입력
N B
수열 A의 원소(space-delimited)

출력
중앙값이 B인 A의 부분 수열의 개수

접근법
1. 일단 B는 부분 수열에 포함되어야 한다.
2. [i, j)로 부분수열을 표현하면, 다음과 같다.

중앙값이 B이려면, [i, index_of_b)와 [index_of_b+1, j) 두 구간에서
B보다 큰 수와 작은 수의 갯수가 같아야 한다.

3. 적당한 자료구조(hash?)를 사용해서, i=0, 1, ..., index_of_b에 대해
[i index_of_b) 구간의 B보다 큰 수와 작은 수의 갯수 차이를 저장해 둔다.

갯수 차이를 키로, 그러한 i값의 갯수를 값으로 한다.

4. j=index_of_b+1, ..., n에 대해서 [index_of_b+1, j) 구간에서
B보다 큰 수와 작은 수의 갯수 차이를 구한다.
그 값에 -1을 곱한 값을 키로 3에서 구한 hash를 검색하여, 그 값을
결과에 더한다.  

O(n)

*/

#include <iostream>
#include <vector>
#include <unordered_map>

#include <cassert>

int main(void) {
	// c++ fast IO
	std::cin.tie(0);
	std::ios_base::sync_with_stdio(false);

	int n, b;
	std::cin >> n >> b;


	std::vector<int> count(n + 1, 0);

	int index_of_b = -1;
	int sum = 0;
	for (int i = 0; i < n; ++i) {
		int temp;
		std::cin >> temp;
		if (temp > b) {
			++sum;
		}
		else if (temp < b) {
			--sum;
		}
		else {
			index_of_b = i;
		}
		count[i + 1] = sum; 
	}

	assert(index_of_b != -1);

	std::unordered_map<int, int> hash;
	for (int i = 0; i <= index_of_b; ++i) {
		int key = count[index_of_b] - count[i];
		if (hash.contains(key)) {
			++hash[key];
		}
		else {
			hash.emplace(key, 1);
		}
	}

	int result = 0;

	for (int j = index_of_b + 1; j <= n; ++j) {
		int key = count[j] - count[index_of_b + 1];
		if (hash.contains(-key)) {
			result += hash[-key];
		} 
	}

	std::cout << result << '\n';
	return 0; 
}