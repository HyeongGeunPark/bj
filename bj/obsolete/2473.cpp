/*

bj2473 �� ���

����� ��: ���밪 1'000'000'000 ����
����� ����: 3~5000��

���� 0�� ���� ��������� �� ����� ���� ������������ �����϶�.

���ٹ�(�� ������)
1. ����� �����Ѵ�.
2. �� ����� ����.
3. �� ������ �˰������� ������ �� ����� ã�´�.(bj2467 ����)
4. ���� ����� �� �� ���� �ʵ��� �����Ѵ�.  

*/

#include<iostream>
#include<vector>
#include<algorithm>
#include<limits>


struct answer {
	std::vector<long long> liquids;
	long long sum = std::numeric_limits<long long>::max();
};

int main(void) {
	std::cin.tie(0);
	std::ios_base::sync_with_stdio(0);

	int n;
	std::vector<long long> arr;
	answer ans;
	std::cin >> n;
	arr.resize(n);
	ans.liquids.resize(3);
	for (int i = 0; i < n; ++i) {
		std::cin >> arr[i];
	}

	std::sort(arr.begin(), arr.end());

	// �켱 �� ����� ����.
	for (int i = 0; i < n - 1; ++i) {
		// 2 pointers
		// �� ����� �� ���� �ʵ��� �������� ���� ��ġ�� �����Ѵ�.
		for (int lp = i+1, rp = n - 1; lp < rp;) {
			long long sum = arr[i] + arr[lp] + arr[rp];
			if (std::abs(ans.sum) > std::abs(sum)) {
				ans.liquids[0] = arr[i];
				ans.liquids[1] = arr[lp];
				ans.liquids[2] = arr[rp];
				ans.sum = sum;
			}

			if (sum > 0) {
				--rp;
			}
			else if (sum < 0) {
				++lp;
			}
			else {
				goto Print; // ���� 0�� ��츦 ã���� �� ����� �ʿ䰡 ����.
			} 
		}
	}

Print:
	for (auto elem : ans.liquids) std::cout << elem << ' ';



}