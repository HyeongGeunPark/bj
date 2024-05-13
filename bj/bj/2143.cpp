/*

bj2143 �� �迭�� ��

���ٹ�
1. �� �迭�� �κ����� ��� ���� �����Ѵ�. �迭�� �Է¹��� �� 1~n�� �κ����� �����Ѵ�.
2. �κ����� occurence�� �����Ѵ�. �ؽ�, ����Ž��Ʈ���� ��ġ �ð��� ���� �ڷᱸ���� ����Ѵ�.
3. ���� int ������ ���� �� �ִٴ� ���� ����Ѵ�. (a, b ��� 0�� ���ҷ� ������ ��� ��)

*/

#include<iostream>
#include<unordered_map>
#include<vector>


int main() {
	std::cin.tie(0);
	std::ios_base::sync_with_stdio(0);

	std::vector<int> a, b;
	std::unordered_map<int, long> s1, s2;
	int t, n, m, temp, sum;

	std::cin >> t;

	std::cin >> n;
	a.resize(n+1);
	a[0] = 0;
	for (int i = 1, sum = 0; i <= n; ++i) {
		std::cin >> temp;
		sum += temp;
		a[i] = sum;
	}

	std::cin >> m;
	b.resize(m+1);
	b[0] = 0;
	for (int i = 1, sum = 0; i <= m; ++i) {
		std::cin >> temp;
		sum += temp;
		b[i] = sum;
	}
	
	s1.reserve(1000000);
	s2.reserve(1000000);

	for (int i = 0; i <= n; ++i) {
		for (int j = i + 1; j <= n; ++j) {
			sum = a[j] - a[i];
			if (s1.count(sum)) ++s1[sum];
			else s1[sum] = 1; 
		} 
	}

	for (int i = 0; i <= m; ++i) {
		for (int j = i + 1; j <= m; ++j) {
			sum = b[j] - b[i];
			if (s2.count(sum)) ++s2[sum];
			else s2[sum] = 1; 
		} 
	}

	long result = 0; 
	long count;
	for (auto& e : s1) {
		count = e.second;
		if (!s2.count(t - e.first)) continue;
		count *= s2[t - e.first]; 
		result += count; 
	}

	std::cout << result; 
}