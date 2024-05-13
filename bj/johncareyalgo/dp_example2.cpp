/*

0-1 배낭 문제

*/

#include<iostream>
#include<vector>
#include<algorithm>

int knapsack_01(int items, int capacity, std::vector<int> values, std::vector<int> weight) {
	
	std::vector<std::vector<int>> dp(items + 1, std::vector<int>(capacity + 1, 0));

	for (int i = 1; i <= items; ++i) {
		int currentweight = weight[i - 1];
		int currentvalue = values[i - 1];
		for (int totalweight = 1; totalweight <= capacity; ++totalweight)
		{
			if (totalweight < currentweight)
			{
				dp[i][totalweight] = dp[i - 1][totalweight];
			}
			else
			{
				dp[i][totalweight] = std::max(dp[i - 1][totalweight],
					dp[i - 1][totalweight - currentweight] + currentvalue);
			}
		}
	}

	return dp[items][capacity];
}

int knapsack_inf0(int items, int capacity, std::vector<int> values, std::vector<int> weight) {
	// 작동하지만 효율적인 방법은 아니다.
	std::vector<std::vector<int>> dp(items + 1, std::vector<int>(capacity + 1, 0));

	for (int i = 1; i <= items; ++i) {
		int currentweight = weight[i - 1];
		int currentvalue = values[i - 1];
		for (int totalweight = 1; totalweight <= capacity; ++totalweight)
		{
			if (totalweight < currentweight)
			{
				dp[i][totalweight] = dp[i - 1][totalweight];
			}
			else
			{
				dp[i][totalweight] = std::max({ dp[i - 1][totalweight],
					dp[i - 1][totalweight - currentweight] + currentvalue,
					dp[i][totalweight - currentweight] + currentweight });
			}
		}
	}

	return dp[items][capacity];
}

int knapsack_inf1(int items, int capacity, std::vector<int> values, std::vector<int> weight) {
	// 상태를 시뮬레이션하기 위해 필요한 차원과 상태를 표현하는데 필요한 차원이
	// 반드시 같아야 하는 것은 아니다.

	/*
	0-1 배낭 문제에서는 i번째 물건을 고려할 때 물건을 하나밖에 쓸 수 없기 때문에
	1~i-1번째 물건만을 사용한 경우의 결과만 사용해야 한다.
	하지만 무한 배낭 문제에서는 물건을 여러 번 쓸 수 있기 때문에
	모든 경우의 결과를 가져다 쓰면 된다.
	따라서 캐시를 저장할 때 물건 인덱스에 관한 상태 정보는 필요하지 않다.  
	*/
	std::vector<int> DP(capacity + 1, 0);
	for (int w = 0; w <= capacity; ++w) {
		for (int i = 0; i < items; ++i) {
			if (weight[i] <= w) {
				DP[w] = std::max(DP[w], DP[w - weight[i]] + values[i]);
			}
		}
	}

	return DP[capacity]; 
}

int main(void) {
	int items, capacity;

	//std::cin >> items >> capacity;
	items = 30;
	capacity = 335;

	std::vector<int> values(items), weight(items);

	values = { 91,81,86,64,24,61,13,57,60,25,94,54,39,62,5,34,95,12,63,33,63,3,42,75,65,1,84,38,46,62 };
	weight = { 40,13,4,17,16,36,5,33,35,16,25,29,6,28,12,37,26,27,32,27,7,26,5,28,39,15,38,37,15,40 };

	/*
	for (auto& v : values) std::cin >> v;
	for (auto& w : weight) std::cin >> w;
	*/

	//int result = knapsack_01(items, capacity, values, weight);

	int result = knapsack_inf1(items, capacity, values, weight);

	std::cout << result; 
}