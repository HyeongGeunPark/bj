/*
bj1948 임계경로

사이클이 없는 가중치 있는 단방향 그래프가 있다.
임의의 두 점을 출발점, 도착점이라고 한다.

출발점에서 시작해서 도착점으로 갈 때,
가장 시간이 오래 걸리는 경로의 수와 그 시간은?

접근법: 위상정렬

1. 출발점에서 도착점까지 모든 점을 위상정렬한다.
2. 정렬된 점들에 대해 순차적으로 다음을 수행한다.
	2-1. 각 점에는 이 점까지 오는 가장 오래 걸리는 경로의 수와
		그 시간이 저장되어 있다. (경로 수, 시간)
	2-2. 시작점을 (1, 0)으로 초기화한다.
	2-3. 시작점부터 도착점 제외 마지막 점까지 다음을 반복.
		2-3-1. 현재 점에 연결된 다음 점들을 찾는다.
		2-3-2. 다음 점까지 가는 시간을 계산한다.
			(다음 시간) = (현재 시간) + (현재-다음 점 경로 길이)
		2-3-3. 다음 점에 이미 저장된 시간과 계산된 시간을 비교.
			2-3-3-1. 같은 경우
				(다음 경로 수) += (현재 경로 수)
			2-3-3-2. 계산된 시간이 더 큰 경우
				(다음 경로 수, 다음 시간) = (현재 경로 수, 계산된 시간)
			2-3-3-3. 계산된 시간이 더 작은 경우
				아무것도 하지 않는다.
3. 도착점에 저장된 (경로 수, 시간)이 정답이다.

주의.
1. 위상정렬을 먼저 하지 않고, 바로 그래프 탐색 알고리즘을
	사용하는 식으로도 풀 수는 있지만 이 경우 가장 긴 경로를
	찾는 것이므로 이미 방문한 점의 거리 가중치가 빈번하게 갱신되어 다시 큐에 들어가게 되므로 상당히 비효율적일 것으로
	보인다.
*/

#include <iostream>
#include <vector>
#include <array>
#include <queue>

struct edge {
	int dest, len;
};

struct num_and_time {
	int num, time;
};

constexpr int N_MAX = 10'000;

int main(){
	std::cin.tie(0);
	std::ios_base::sync_with_stdio(0);

	// input
	int n;
	int m;
	std::cin >> n >> m;

	std::vector<std::vector<edge>> adj;

	std::vector<int> in_degree(n + 1, 0);
	adj.reserve(n);

	for (int i = 0;i < m;++i) {
		int s, e, l;
		std::cin >> s >> e >> l;
		adj[s].emplace_back(e, l);
		++in_degree[e];
	}

	// start point and end point
	int start_point;
	int end_point;
	std::cin >> start_point >> end_point;

	// Topology Sort
	// in this problem, start, end point are given
	// so It is possible to put only the start point int the queue
	std::queue<int, std::vector<int>> q;
	q.push(start_point);
	while (!q.empty())
	{
		int cur = q.front();
		q.pop();

		for (auto [next, len] : adj[cur]) {
			// len is not used in this loop

		}
	}


	// It is given that there is no cycle.
	//No need to check unvisited points.


	return 0;
}