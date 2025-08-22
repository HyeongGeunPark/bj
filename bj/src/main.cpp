/*
bj31563 수열 회전과 쿼리

수열이 주어진다.

가능한 쿼리는 다음과 같다.
1 k -> 수열을 오른쪽으로 k만큼 회전한다.
2 k -> 수열을 왼쪽으로 k만큼 회전한다.
3 a b -> 수열의 a번째 수부터 b번째 수의 합을 출력한다.(inclusive range)

3번 쿼리에 대한 결과값을 한 줄에 하나씩 입력으로 주어진 순서대로 출력한다.

입력
N: 수열의 길이 (2 <= N <= 200'000)
Q: 쿼리의 수 (1<= Q <= 200'000)
1 <= A_i <= 10^9
1 <= k <= N
1 <= a <= b <= N

* 1-based index를 사용한다.

접근: 누적 합
1. 실제로 수열을 회전할 필요는 없다.
2. 수열이 얼마나 회전했는지만 기억해 둔다.
3. 3번 쿼리를 할 때, 현재 수열이 얼마나 회전했는지에 따라 범위를 조정한다.
4. 이 쿼리는 누적 합으로 빠르게 구할 수 있다.

*/

#include<iostream>
#include<vector>
#include<sstream>

int main(void) {
	// c++ fast io
	std::cin.tie(0);
	std::ios_base::sync_with_stdio(false);

	int n;
	int q;
	std::cin >> n >> q;

	std::vector<long long> array_sum;
	array_sum.push_back(0);
	long long sum = 0;
	for (int i = 0; i < n; ++i) {
		int temp;
		std::cin >> temp;
		sum += temp;
		array_sum.push_back(sum); 
	}

	int rotation = 0;

	std::stringstream obufss;

	// queries
	for (int i = 0; i < q; ++i) {
		int query;
		int k, a, b;
		std::cin >> query;
		switch (query) {
		case 1:
			std::cin >> k;
			rotation += k;
			rotation %= n;
			break;
		case 2:
			std::cin >> k;
			rotation -= k;
			rotation %= n;
			break;
		case 3:
			std::cin >> a >> b;
			--a; --b; // 1-based to 0-based

			// rotate
			a -= rotation;
			b -= rotation;
			while (a < 0)
				a += n;
			a %= n;
			while (b < 0)
				b += n;
			b %= n;

			if (a <= b)
				// case 1. a <= b
				obufss << array_sum[b + 1] - array_sum[a] << '\n';
			else {
				// case 2. a > b
				// get sum [a, n] + [1, b]
				sum = 0;

				obufss << array_sum[b + 1] + array_sum[n] - array_sum[a] << '\n'; 
			} 
			break;
		} 
	}

	std::cout << obufss.str();

	return 0;
}