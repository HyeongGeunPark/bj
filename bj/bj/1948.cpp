/*
bj1948 임계경로

사이클이 없는 가중치 있는 단방향 그래프가 있다.
임의의 두 점을 출발점, 도착점이라고 한다.

출발점에서 시작해서 도착점으로 갈 때,
가장 시간이 오래 걸리는 경로에 포함된 도로의 수와 그 시간은?

접근법: 위상정렬

1. 출발점에서 도착점까지 모든 점을 위상정렬한다.
2. 정렬된 점들에 대해 순차적으로 다음을 수행한다.
  2-1. 정방향 최장 거리 구하기
    위상 정렬된 점을 차례로 순회하면서 다음 점의
    길이를 업데이트한다.
  2-2. 역방향 최장 거리 구하기
    반대 순서로 순회하면서 같은 작업을 한다.
3. 출발점에서 bfs를 한다.
  3-1. 다음 조건을 만족하는 간선을 찾는다.
    (현재 점까지의 정방향 최장 거리)
    + (간선 길이)
    + (다음 점까지의 역방향 최장 거리)
    == (도착점까지의 최장 길이)
  3-2. 만족하는 경우만 다음 점을 큐에 넣어 다음 탐색을
    진행하도록 한다. 또한 그러한 간선의 갯수를 센다.


*/

#include <algorithm>
#include <iostream>
#include <queue>
#include <ranges>
#include <vector>

struct edge {
  int dest, len;
};

struct num_and_time {
  int num, time;
};

constexpr int N_MAX = 10'000;

int main() {
  std::cin.tie(0);
  std::ios_base::sync_with_stdio(0);

  // input
  int n;
  int m;
  std::cin >> n >> m;

  std::vector<std::vector<edge>> adj(n + 1);
  std::vector<std::vector<edge>> adj_rev(n + 1);
  std::vector<int> in_degree(n + 1, 0);

  for (int i = 0; i < m; ++i) {
    int s, e, l;
    std::cin >> s >> e >> l;
    adj[s].emplace_back(e, l);
    adj_rev[e].emplace_back(s, l);
    ++in_degree[e];
  }

  // start point and end point
  int start_point;
  int end_point;
  std::cin >> start_point >> end_point;

  // Topology Sort
  // in this problem, start, end point are given
  // so It is possible to put only the start point int the queue
  std::queue<int> q;
  std::vector<int> sorted;
  sorted.reserve(n);
  q.push(start_point);
  while (!q.empty()) {
    int cur = q.front();
    q.pop();
    sorted.push_back(cur);

    for (auto [next, len] : adj[cur]) {
      // len is not used in this loop
      --in_degree[next];
      if (in_degree[next] == 0) {
        q.push(next);
      }
    }
  }

  // It is given that there is no cycle.
  // No need to check unvisited points.

  // forward critical path's cost
  std::vector<int> forward_cost(n + 1, 0);
  for (auto cur : sorted) {
    for (const auto& [next, len] : adj[cur]) {
      forward_cost[next] =
          std::max(forward_cost[next], forward_cost[cur] + len);
    }
  }

  // reverse critical path's cost
  std::vector<int> reverse_cost(n + 1, 0);
  for (auto cur : sorted | std::views::reverse) {
    for (const auto& [next, len] : adj_rev[cur]) {
      reverse_cost[next] =
          std::max(reverse_cost[next], reverse_cost[cur] + len);
    }
  }

  // bfs
  int count = 0;
  q.push(start_point);
  std::vector<bool> in_queue(n + 1, false);
  while (!q.empty()) {
    int cur = q.front();
    q.pop();
    for (const auto& [next, len] : adj[cur]) {
      if (forward_cost[cur] + reverse_cost[next] + len ==
          forward_cost[end_point]) {
        ++count;
        if (!in_queue[next]) {
          q.push(next);
          in_queue[next] = true;
        }
      }
    }
  }

  // print
  std::cout << forward_cost[end_point] << '\n' << count << '\n';

  return 0;
}
