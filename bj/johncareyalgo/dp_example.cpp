#include<iostream>
#include<vector>
#include<algorithm>
#include<functional>
#include<chrono>
#include<iomanip>

// dp ������ Ǫ�� ����
// �κ������� �� ����: ������ �κ����� �� ���� Ư�� ���� �κ������� �����ϴ��� ã�� ����.

// 1�ܰ�: bruteforce, ��� �κ������� ���ϰ�, �� ���� ���Ѵ�.
void getallsubsets(std::vector<int>& set, std::vector<int> subset, int index,
	std::vector<std::vector<std::vector<int>>>& allsubsets) {
	// ���� ����: ������ ��� ���Ҹ� �����.
	if (index == set.size()) {
		allsubsets[subset.size()].push_back(subset);
		return;
	}

	// �б� 1: ���� �ε����� ���Ҹ� �������� �ʴ� �κ����� ����
	getallsubsets(set, subset, index + 1, allsubsets);
	// �б� 2: ���� �ε����� ���Ҹ� �����ϴ� �κ����� ����
	subset.push_back(set[index]);
	getallsubsets(set, subset, index + 1, allsubsets); 
}

bool subsetsum_bruteforce(std::vector<int> set, int target) {
	std::vector<std::vector<std::vector<int>>> allsubsets(set.size() + 1);
	getallsubsets(set, {}, 0, allsubsets);

	// ��� �κ����տ� ���� �� ���� ���� ���ϰ� �̸� target�� ���Ѵ�.
	for (int size = 0; size <= set.size(); ++size) {
		for (auto subset : allsubsets[size]) {
			int sum = 0;
			for (auto number : subset) {
				sum += number;
			}
			if (sum == target)
				return true;
		}
	}
	return false;
}


// 2�ܰ�: ��Ʈ��ŷ, ���� ������ �����ϰ� �����Ͽ� �� �б� ȸ���� ���δ�.
bool subsetsum_backtrack(std::vector<int>& set, int sum, int i) {
	// ���� ���ǵ�
	if (sum == 0) return true; // �������� 1. target�� ���� ���� ������ �κ������� ã�� 
	if (i == set.size() || set[i] > sum) return false;
	// �������� 2. target�� ���� ���� ������ �κ������� ã�� ����
	// 2-1. �̹� ��� ���Ҹ� �����
	// 2-2. ���� �κ������� ���� �̹� target�� �ʰ���

	// �� ������ ���� ���ǿ� ���� ������ ���� Ž���� ���� �ʴ´�.


	// ��� ȣ���� �ʿ��� ���
	// ���� �ε����� ���Ҹ� ������ ���, �������� ���� ����� ���� �κ������� ����
	return subsetsum_backtrack(set, sum - set[i], i + 1)
		|| subsetsum_backtrack(set, sum, i + 1); 
}

// 3�ܰ�: �޸������̼�.
constexpr int UNKNOWN = 1e9;
bool subsetsum_memoization(std::vector<int>& set, int sum, int i, std::vector<std::vector<int>>& memo)
{
	// ���� ����, ��Ʈ��ŷ Ȱ�� �����ϴ�.
	if (sum == 0) return true;
	if (i == set.size() || set[i] > sum) return false;

	// ĳ�� Ž��
	// ���´� �� ������ ���ǵȴ�.
	// i : i��° ���ұ��� ����Ͽ���
	// j : �κ������� ���� ��
	if (memo[i][sum] == UNKNOWN)
	{
		bool append = subsetsum_memoization(set, sum - set[i], i + 1, memo);
		bool ignore = subsetsum_memoization(set, sum, i + 1, memo);
		memo[i][sum] = append || ignore; 
	}

	// ĳ�ÿ� ����� ���� �ִ� ���
	return memo[i][sum];
}

// 4�ܰ�: Ÿ�淹�̼�. ��� ������ ������� �ʰ�, ����� ������ ����Ѵ�.
std::vector<std::vector<bool>> subsetsum_tabulation(std::vector<int>& set) {
	int maxSum = 0;
	for (int i : set) maxSum += i;

	std::vector<std::vector<bool>> DP(set.size() + 1, std::vector<bool>(maxSum + 1, false));

	// ���� ���� 1: �������� ���� 0�̴�.
	for (int i = 0; i < set.size(); ++i) {
		DP[i][0] = true;
	}

	for (int i = 1; i <= set.size(); ++i) {
		for (int sum = 1; sum <= maxSum; ++sum) {
			if (sum < set[i - 1])
				DP[i][sum] = DP[i - 1][sum];
			else {
				DP[i][sum] = DP[i - 1][sum]
					|| DP[i - 1][sum - set[i-1]];
			}
		}
	}

	return DP;
}



// �ð� ����
void test_time(std::function<bool()> f, std::string s) {
	auto t0 = std::chrono::steady_clock::now();
	bool result = f();
	auto t1 = std::chrono::steady_clock::now();
	std::chrono::duration<double> diff = (t1 - t0);

	std::cout << "�׽�Ʈ: " << s << '\n';
	std::cout << "���� ���: " << (result ? "true" : "false") << '\n';
	std::cout << "���� �ð�: " << std::fixed << std::setprecision(9)
		<<  diff << "\n";


}

int main(void) {
	std::vector<int> set{ 16, 1058,22,13,46,55,3,92,47,7,
	98,367,807,106,333,85,577,9,3059 };
	int target = 6799;
	int tests = 2;

	std::sort(set.begin(), set.end());
	test_time([&]()->bool {return subsetsum_backtrack(set, target, 0); }, "backtrack, find " + std::to_string(target));
	test_time([&]()->bool {return subsetsum_bruteforce(set, target); }, "bruteforce, find " + std::to_string(target));

	// ���� ����: i��° ���ұ��� ������� ��, �������� j�� �κ������� �����ϴ��� == memo[i][j]
	std::vector<std::vector<int>> memo(set.size(), std::vector<int>(7000, UNKNOWN));
	test_time([&]()->bool {return subsetsum_memoization(set, target, 0, memo); }, "memoization, find " + std::to_string(target));
	test_time([&]()->bool { auto result = subsetsum_tabulation(set);
		return result[set.size()][target]; }, "tabulation, find " + std::to_string(target));
}