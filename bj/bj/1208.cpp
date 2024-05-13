/*

bj1208 부분수열의 합 2

n개의 정수로 이루어진 수열이 있을 때, 크기가 양수인 부분수열 중에서 
그 수열의 원소를 다 더한 값이 S가 되는 경우의 수를 구하는 프로그램.

캐시의 유용성(한 번 계산한 값을 다시 사용하는 경우)가 떨어지므로
DP 최적화는 유의미한 성능 향상을 만들어내지 않는다.

접근법: 반으로 나누어 생각하기
1. 입력 수열을 반(A, B)으로 나눈다.
2. 반으로 나뉜 각각의 수열에서 전수 탐색을 통해 특정 합을
	가지는 부분수열의 개수를 모두 파악한다. (2 * 1<<20 ~= 2'000'000)
3. 두 결과를 가지고 합이 S가 되는 모든 경우의 수를 구한다.
	sum( A[i] * B[j] ) for (i+j==S)
*/

#include<iostream>
#include<vector>

using std::vector;
using ll = long long;
constexpr int SIZE = 3'000'000;

vector<int> memo(2*SIZE+1, 0);

void dfs(vector<int>& set, int i, int mid, int sum) {
	// base case
	if (i == mid) {
		++memo[sum + SIZE];
	}
	else {
	// recursive call
		dfs(set, i + 1, mid, sum);
		dfs(set, i + 1, mid, sum + set[i]);
	} 
} 

ll result = 0;

void dfs2(vector<int>& set, int i, int sum, int target) {
	// base case
	if (i == set.size()) {
		result += memo[target - sum + SIZE];
	}
	else {
	//recursive call
		dfs2(set, i + 1, sum, target);
		dfs2(set, i + 1, sum + set[i], target);
	} 
}
 
ll solve(vector<int>& set, int s) {

	int mid = set.size() / 2;
	// 반 탐색
	dfs(set, 0, mid, 0);

	// 반대쪽에서 반 탐색
	dfs2(set, mid, 0, s); 

	return result; 
}

int main(void) {
	int n, s;
	std::cin >> n >> s;
 
	vector<int> set(n);
	for (int i = 0; i < n; ++i) {
		std::cin >> set[i];
	}

	std::cout << solve(set, s) - (s==0?1:0); // 크기가 양수인 부분수열, 공집합은 포함하지 않음.
}

