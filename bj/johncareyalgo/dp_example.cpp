#include<iostream>
#include<vector>
#include<algorithm>
#include<functional>
#include<chrono>
#include<iomanip>

// dp 문제를 푸는 예시
// 부분집합의 합 문제: 집합의 부분집합 중 합이 특정 값인 부분집합이 존재하는지 찾는 문제.

// 1단계: bruteforce, 모든 부분집합을 구하고, 그 합을 구한다.
void getallsubsets(std::vector<int>& set, std::vector<int> subset, int index,
	std::vector<std::vector<std::vector<int>>>& allsubsets) {
	// 기저 조건: 집합의 모든 원소를 고려함.
	if (index == set.size()) {
		allsubsets[subset.size()].push_back(subset);
		return;
	}

	// 분기 1: 현재 인덱스의 원소를 포함하지 않는 부분집합 구성
	getallsubsets(set, subset, index + 1, allsubsets);
	// 분기 2: 현재 인덱스의 원소를 포함하는 부분집합 구성
	subset.push_back(set[index]);
	getallsubsets(set, subset, index + 1, allsubsets); 
}

bool subsetsum_bruteforce(std::vector<int> set, int target) {
	std::vector<std::vector<std::vector<int>>> allsubsets(set.size() + 1);
	getallsubsets(set, {}, 0, allsubsets);

	// 모든 부분집합에 대해 그 원소 합을 구하고 이를 target과 비교한다.
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


// 2단계: 백트래킹, 기저 조건을 빡빡하게 설정하여 총 분기 회수를 줄인다.
bool subsetsum_backtrack(std::vector<int>& set, int sum, int i) {
	// 기저 조건들
	if (sum == 0) return true; // 기저조건 1. target과 같은 합을 가지는 부분집합을 찾음 
	if (i == set.size() || set[i] > sum) return false;
	// 기저조건 2. target과 같은 합을 가지는 부분집합을 찾지 못함
	// 2-1. 이미 모든 원소를 고려함
	// 2-2. 현재 부분집합의 합이 이미 target을 초과함

	// 더 세세한 기저 조건에 의해 가망이 없는 탐색을 하지 않는다.


	// 재귀 호출이 필요한 경우
	// 현재 인덱스의 원소를 포함한 경우, 포함하지 않은 경우의 다음 부분집합을 생성
	return subsetsum_backtrack(set, sum - set[i], i + 1)
		|| subsetsum_backtrack(set, sum, i + 1); 
}

// 3단계: 메모이제이션.
constexpr int UNKNOWN = 1e9;
bool subsetsum_memoization(std::vector<int>& set, int sum, int i, std::vector<std::vector<int>>& memo)
{
	// 기저 조건, 백트래킹 활용 가능하다.
	if (sum == 0) return true;
	if (i == set.size() || set[i] > sum) return false;

	// 캐시 탐색
	// 상태는 두 정수로 정의된다.
	// i : i번째 원소까지 고려하였음
	// j : 부분집합의 원소 합
	if (memo[i][sum] == UNKNOWN)
	{
		bool append = subsetsum_memoization(set, sum - set[i], i + 1, memo);
		bool ignore = subsetsum_memoization(set, sum, i + 1, memo);
		memo[i][sum] = append || ignore; 
	}

	// 캐시에 저장된 값이 있는 경우
	return memo[i][sum];
}

// 4단계: 타뷸레이션. 재귀 구조를 사용하지 않고, 상향식 구조를 사용한다.
std::vector<std::vector<bool>> subsetsum_tabulation(std::vector<int>& set) {
	int maxSum = 0;
	for (int i : set) maxSum += i;

	std::vector<std::vector<bool>> DP(set.size() + 1, std::vector<bool>(maxSum + 1, false));

	// 기저 조건 1: 공집합의 합은 0이다.
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



// 시간 측정
void test_time(std::function<bool()> f, std::string s) {
	auto t0 = std::chrono::steady_clock::now();
	bool result = f();
	auto t1 = std::chrono::steady_clock::now();
	std::chrono::duration<double> diff = (t1 - t0);

	std::cout << "테스트: " << s << '\n';
	std::cout << "실행 결과: " << (result ? "true" : "false") << '\n';
	std::cout << "실행 시간: " << std::fixed << std::setprecision(9)
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

	// 상태 정의: i번째 원소까지 고려했을 때, 원소합이 j인 부분집합이 존재하는지 == memo[i][j]
	std::vector<std::vector<int>> memo(set.size(), std::vector<int>(7000, UNKNOWN));
	test_time([&]()->bool {return subsetsum_memoization(set, target, 0, memo); }, "memoization, find " + std::to_string(target));
	test_time([&]()->bool { auto result = subsetsum_tabulation(set);
		return result[set.size()][target]; }, "tabulation, find " + std::to_string(target));
}