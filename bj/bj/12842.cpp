/*
bj12842 튀김 소보루

1. 튀소 n개를 001에 둔다.
2. 001에는 m명의 사람이 있다.
3. 이 사람들은 영선이가 떠나자 마자 튀소를 집어 먹기 시작한다.
4. 튀소를 다 먹으면 바로 다음 튀소를 집어 먹기 시작한다.
5. 사람들이 동시에 새로운 튀소를 집으려 할 때, 번호가 작은 사람이 우선적으로 튀소를 집는다.

영선이가 다시 돌아왔을 때 s개의 온전한 튀소가 남아 있었다고 한다.
(사람들이 먹으려고 집은 튀소는 온전한 튀소가 아니다.)

마지막으로 튀소를 집은 사람의 번호를 구하여라.
(영선이는 각 사람이 튀소를 먹는 데 걸리는 시간을 알고 있다.)

1 <= s < n <= 100'000
1 <= m <= 100'000
1 <= t_i <= 1000 // i번째 사람이 튀소를 먹는데 걸리는 시간


접근: 우선순위 큐

1. 현재 빵을 집을 수 있는 사람을 우선순위 큐에 넣는다.
	1. 일단 모든 사람이 들어갈 것이다.
	2. 한 명씩 넣으면서 남은 빵 수를 하나씩 줄인다.
	3. key 값은 다음 빵을 집는 시간으로 한다.
2. 우선순위 큐에서 한 명을 제거하고 다음에 다 먹는 시간을 업데이트하여 다시 넣는다.

1, 2의 과정에서 현재 남은 빵 개수가 s가 되면 언제든 종료하고 답을 출력한다.

시간복잡도: (n-s) * log(m)



*/

#include<iostream>
#include<queue>
#include <vector>



int main(void) {
	std::cin.tie(0);
	std::ios_base::sync_with_stdio(false);

	int s, n, m;
	std::cin >> n >> s;
	std::cin >> m;

	std::vector<int> time;
	time.reserve(m);
	for (int i = 0; i < m; ++i) {
		int temp;
		std::cin >> temp;
		time.push_back(temp);
	}

	std::priority_queue<
		std::pair<int, int>,
		std::vector<std::pair<int,int>>,
		std::greater<std::pair<int,int>>
		> pq;

	for (int i = 0; i < m; ++i) {
		pq.push(std::pair{ time[i], i });
		--n;
		if (n == s) {
			std::cout << i + 1;
			return 0;
		}
	}

	while (!pq.empty()) {
		auto [cur_time, man_idx] = pq.top();
		pq.pop();
		--n;
		if (n == s) {
			std::cout << man_idx + 1;
			return 0;
		}
		pq.push(std::pair{ cur_time + time[man_idx], man_idx });
	}

	return 0; 
}



