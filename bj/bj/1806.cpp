/*

bj1806 �κ���

moving window

1. �� �����͸� ó���� ��ġ��Ų��.
2. ���غ��� �κ����� ������ ���� �����͸� ���������� �ű��.
3. ���غ��� �κ����� ũ�� �� ���� ���̸� �����Ѵ�. �� ���� �ּҰ����� �����Ѵ�.
�� �� ���� �����͸� �������� �ű��.
4. ���� �����Ͱ� ������ ����� ������.  

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

