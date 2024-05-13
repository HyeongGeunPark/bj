/*

bj1208 �κм����� �� 2

n���� ������ �̷���� ������ ���� ��, ũ�Ⱑ ����� �κм��� �߿��� 
�� ������ ���Ҹ� �� ���� ���� S�� �Ǵ� ����� ���� ���ϴ� ���α׷�.

ĳ���� ���뼺(�� �� ����� ���� �ٽ� ����ϴ� ���)�� �������Ƿ�
DP ����ȭ�� ���ǹ��� ���� ����� ������ �ʴ´�.

���ٹ�: ������ ������ �����ϱ�
1. �Է� ������ ��(A, B)���� ������.
2. ������ ���� ������ �������� ���� Ž���� ���� Ư�� ����
	������ �κм����� ������ ��� �ľ��Ѵ�. (2 * 1<<20 ~= 2'000'000)
3. �� ����� ������ ���� S�� �Ǵ� ��� ����� ���� ���Ѵ�.
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
	// �� Ž��
	dfs(set, 0, mid, 0);

	// �ݴ��ʿ��� �� Ž��
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

	std::cout << solve(set, s) - (s==0?1:0); // ũ�Ⱑ ����� �κм���, �������� �������� ����.
}

