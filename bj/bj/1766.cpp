/*

bj1766 문제집

접근법: 위상 정렬, Kahn's algorithm

1. 인접 리스트를 구축한다.
2. 동시에 진입차수를 구한다.
3. kahn's algorithm
  3-1. 진입차수가 0인 노드를 큐에 넣는다.
  3-2. 큐에서 노드를 하나씩 꺼내면서 그 노드에 연결된 노드의 진입차수를 하나씩
줄인다. 인접 리스트를 이용하되 먼저 정렬해야 한다. 이 때 진입차수가 0이 된
노드는 큐에 넣는다. 3-3. 큐가 완전히 빌 때까지 반복한다. (3-4. 큐를 거쳐 나간
노드의 수가 전체 노드의 수보다 적으면 cycle이 있음.)

  우선순위 큐를 이용하면 문제의 조건(쉬운 문제부터 풀기)을 만족할 수 있다.

큐에서 꺼낸 순서대로 그대로 출력하면 된다.

*/

#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

std::vector<std::vector<int>> adj;
std::vector<int> degree;
std::priority_queue<int, std::vector<int>, std::greater<int>> q;

int main(void) {
  std::cin.tie(0);
  std::ios_base::sync_with_stdio(0);

  int n, m;
  std::cin >> n >> m;

  adj.resize(n + 1);
  degree.resize(n + 1, 0);

  for (int i = 0; i < m; ++i) {
    int s, d;
    std::cin >> s >> d;
    adj[s].push_back(d);
    ++degree[d];
  }

  // kahn's algorithm
  for (int i = 1; i <= n; ++i) {
    if (degree[i] == 0) q.push(i);
  }
  while (!q.empty()) {
    int cur = q.top();
    q.pop();
    auto& pred = adj[cur];
    std::sort(pred.begin(), pred.end());
    for (int p : pred) {
      --degree[p];
      if (degree[p] == 0) q.push(p);
    }
    std::cout << cur << ' ';
  }
}