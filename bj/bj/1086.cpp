/*
bj1086 박성원

서로 다른 정수로 이루어진 집합이 있다.
이 집합의 순열을 합치면 큰 정수 하나를 만들 수 있다.
합친 수가 K로 나누어 떨어지는 순열을 구하려 한다.

랜덤으로 순열 하나를 정답이라고 출력했을 때,
이것이 정답일 확률을 구하여라.

집합의 수의 개수 1 <= N <= 15
1 <= 집합에 포함된 수 < 10^51 (최대 자릿수 50개)
1<= K <= 100

접근:
1. 확률 계산
	1. 모든 경우의 수는 P(N, N)
	2. 정답인 경우의 수를 M이라 하자.
	3. 랜덤으로 하나를 제시했을 때, 그것이 정답일 확률은 M / P(N, N)
	4. 기약분수로 출력한다.
	5. (주의) M이 1일 경우 답은 0/1이다.

2. 큰 수의 입력 처리
	1. 일단 원소를 문자열로 입력받는다.
	2. K를 입력받는다.
	3. 문자열로 입력받은 원소의 자릿수와 K로 나눈 나머지를 계산한다.
		3-1. 이 계산을 위해 10^k (0 <= k <= 50)를 K로 나눈 나머지를 먼저 계산한다.

3. 다이나믹 프로그래밍
	1. DP[i][j]를 다음과 같이 정의한다.
	i = 사용한 원소의 비트마스크
	j = k로 나눈 나머지
	DP[i][j] = 비트마스크 i로 표현되는 원소들을 사용해 만든 순열 중
				k로 나눈 나머지가 j인 경우의 수

	DP는 bottom-up 구조로 계산하는 쪽이 편하다.
	DP[0][0] = 1
	-> DP[0001][a] += DP[0][0]
		-> DP[0011][aa] += DP[0001][a]
		-> DP[0110][ab] += DP[0001][a]
		-> DP[1010][ac] += DP[0001][a]
	-> DP[0010][b] += DP[0][0]
		-> ...
	-> DP[0100][c] += DP[0][0]
	-> DP[1000][d] += DP[0][0]
		...
	이 계산에 미리 구해둔 10^n을 k로 나눈 나머지를 사용한다.

	2. 상태가 이동할 때, 다음과 같이 계산한다.
		1. 기본적으로 우측에 새 원소를 붙인다고 생각한다.
		j값은 다음과 같이 변한다.
		((j * (10^새 원소의 길이)%k) * (새 원소 % k)) % k

	3. 0 - 2^N-2까지 순회한 후, DP[2^N-1][0]이 답이 된다.

주의.
1. 오버플로우. 15! == 1'307'674'368'000
*/

#include<iostream>
#include<vector>
#include<string>
#include<array>
#include<numeric>

//#pragma comment(linker, "/STACK:33554432")

struct Data {
	int remainder;
	int r_of_exp10;
};

int main() {
	int n;
	std::cin >> n;

	std::vector<std::string> input_strings(n);

	for (int i = 0;i < n;++i) {
		std::cin >> input_strings[i];
	}

	int k;
	std::cin >> k;

	// modular process
	std::vector<Data> input_processed(n, {0,0});
	for (int i = 0;i < n;++i) {
		const std::string& str = input_strings[i];
		int& result = input_processed[i].remainder;
		int exp10 = 1;
		for (int j = str.size() - 1;j >= 0;--j) {
			result += (exp10 * (str[j] - '0')) % k;
			exp10 *= 10;
			exp10 %= k;
		}
		input_processed[i].r_of_exp10 = exp10;
	}

	// DP
	//std::vector<std::vector<long long>> mem(1 << n, std::vector<long long>(k, 0));
	std::array<std::array<long long, 100>, 1 << 15> mem{};
	mem[0][0] = 1;
	/*
	for (int i = 0; i < (1 << n) - 1; ++i) {
		for (int j = 0; j < k; ++j) {
			if (mem[i][j] == 0)
				continue;
			for(int m = 0; m < n; ++m)
			{
				int mask = 1 << m;
				if (i & mask)
					continue;

				int next_i = i | mask;
				Data& append = input_processed[m];
				int next_j = (j * append.r_of_exp10 + append.remainder) % k;
				mem[next_i][next_j] += mem[i][j];
			}
		}
	}
	*/

	// it is faster due to more frequent cash hit
	for (int i = 0; i < (1 << n) - 1; ++i) {
		for (int m = 0;m < n;++m) {
			// mem[i] and mem[next_i] are hot inside this loop
			int mask = 1 << m;
			if (i & mask)
				continue;
			int next_i = mask | i;
			for (int j = 0; j < k; ++j) {
				Data& append = input_processed[m];
				int next_j = (j * append.r_of_exp10 + append.remainder) % k;
				mem[next_i][next_j] += mem[i][j];
			}
		}
	}

	// probability calculation : to irreducible fraction
	long long& result = mem[(1 << n) - 1][0];
	if(result == 0){
		std::cout << "0/1\n";
	}
	else {
		long long divider = 1;
		for(int i=2; i<=n; ++i){
			divider *= i;
		}
		long long G = std::gcd(result, divider);
		std::cout << result / G << '/' << divider / G << '\n';
	}
	return 0;
}