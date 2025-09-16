/*
bj28707 배열 정렬
길이 2~8의 배열 A를 정렬한다.
i번째, j번째 수의 위치를 바꾸는 비용 c의 연산이
M(~10)종류가 있다.
이 연산들을 사용해 A를 정렬하는 최소 비용을 구하여라.
불가능하다면 -1 출력.

접근: 최단거리 탐색.
배열의 현재 상태를 적당한 수로 나타낼 방법만 만들면 된다.
맵 자료구조를 사용하면 편하다.
*/

#include <algorithm>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>

int main(void) {
  int n;
  std::cin >> n;
  std::string seq;
  for (int i = 0; i < n; ++i) {
    int temp;
    std::cin >> temp;
    seq.push_back('A' - 1 + temp);
  }
  std::string goal = seq;
  std::sort(goal.begin(), goal.end());
  std::unordered_map<std::string, int> mem;
  mem.reserve(100'000);
  int m;
  std::cin >> m;
  std::vector<std::vector<int>> oper(m, std::vector<int>(3));
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < 3; ++j) {
      std::cin >> oper[i][j];
    }
  }

  std::priority_queue<std::pair<int, std::string>,
                      std::vector<std::pair<int, std::string>>,
                      std::greater<std::pair<int, std::string>>>
      pq;
  pq.push({0, seq});
  mem[seq] = 0;
  while (pq.size()) {
    auto [cost, cur] = pq.top();
    if (cur == goal) break;
    pq.pop();
    for (int i = 0; i < m; ++i) {
      std::swap(cur[oper[i][0] - 1], cur[oper[i][1] - 1]);
      int newcost = cost + oper[i][2];
      if (mem.contains(cur) && newcost >= mem[cur]) {
        std::swap(cur[oper[i][0] - 1], cur[oper[i][1] - 1]);
        continue;
      }
      mem[cur] = newcost;
      pq.push({newcost, cur});
      std::swap(cur[oper[i][0] - 1], cur[oper[i][1] - 1]);
    }
  }
  if (mem.contains(goal))
    std::cout << mem[goal];
  else
    std::cout << -1;
}