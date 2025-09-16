/*

bj2623 음악프로그램

가수의 수: 최대 1000
보조 pd의 수: 최대 100

접근법(위상 정렬)

1. 입력을 이용해 인접 리스트로 선후관계를 저장한다.

2. Kahn의 알고리즘 적용.


*/

#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <vector>

int main(void) {
  int n, m;

  std::cin >> n >> m;
  std::cin >> std::ws;

  std::vector<std::vector<int>> adj;
  std::vector<int> degree;
  adj.resize(static_cast<size_t>(n) + 1);
  degree.resize(static_cast<size_t>(n) + 1, 0);

  // input
  for (int i = 0; i < m; ++i) {
    int nn;
    std::cin >> nn;
    if (!nn) continue;

    int prev, next;
    std::cin >> prev;

    for (int j = 1; j < nn; ++j) {
      std::cin >> next;
      adj[prev].push_back(next);
      ++degree[next];
      prev = next;
    }
  }

  // Kahn's algorithm
  std::vector<int> obuf;
  std::queue<int> q;

  for (int i = 1; i <= n; ++i) {
    if (degree[i] == 0) q.push(i);
  }

  while (!q.empty()) {
    int prev = q.front();
    obuf.push_back(prev);
    q.pop();

    for (int next : adj[prev]) {
      --degree[next];
      if (degree[next] == 0) {
        q.push(next);
      }
    }
  }

  if (obuf.size() != n) {
    std::cout << '0';
  } else {
    for (int i : obuf) {
      std::cout << i << '\n';
    }
  }
}