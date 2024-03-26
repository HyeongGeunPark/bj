/*

bj1806 부분합

moving window

1. 두 포인터를 처음에 위치시킨다.
2. 기준보다 부분합이 작으면 우측 포인터를 오른쪽으로 옮긴다.
3. 기준보다 부분합이 크면 그 범위 길이를 저장한다. 이 값은 최소값으로 갱신한다.
그 후 좌측 포인터를 우측으로 옮긴다.
4. 우측 포인터가 범위를 벗어나면 끝난다.  

*/

#include<iostream>
#include<vector>
#include<limits>
#include<algorithm>

int main() {
	int n, s;
	std::cin >> n >> s;

	std::vector<int> arr;
	arr.reserve(n);

	for (int i = 0; i < n; ++i) {
		int temp;
		std::cin >> temp;
		arr.push_back(temp);
	}
	auto p1 = arr.cbegin();
	auto p2 = arr.cbegin();
	int partial_sum = 0;
	std::ptrdiff_t min_len = std::numeric_limits<std::ptrdiff_t>::max();

	while (true) {
		if (partial_sum < s) {
			if (p2 == arr.cend()) break;
			partial_sum += *p2;
			++p2;
		}
		else {
			min_len = std::min(min_len, (p2 - p1));
			partial_sum -= *p1;
			++p1; 
		}
	}
    if(min_len!=std::numeric_limits<std::ptrdiff_t>::max())
	    std::cout << static_cast<long long>(min_len); 
    else
        std::cout << '0';
}

