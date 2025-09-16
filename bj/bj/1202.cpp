/*

bj1202 보석 도둑

접근법: 그리디

가장 작은 가방부터 채워 나간다.
해당 가방에 담을 수 있는 가장 값진 보석을 담는다.

1. 가방을 정렬한다.
2. 보석을 무게순으로 정렬한다.
3. 우선순위 큐를 준비한다. 이 큐는 보석 가치로 정렬된다.

4. 가방을 작은 것부터 채워 나간다.
  4-1. 우선순위 큐에 이 가방에 담을 수 있는 보석을 모두 담는다.
  4-2. 우선순위 큐에서 가장 가치있는 보석을 꺼낸다. 이 보석의 가치를 결과에
더한다. 4-3. 모든 가방에 대해 위를 반복한다.

보석/가방 최대값이 300'000, 보석 가치의 최대값이 100'000'000이므로
오버플로우에 주의한다.

*/

#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

struct gem {
  int m, v;
};

bool gem_compare(const gem& g1, const gem& g2) { return g1.m < g2.m; }

struct pq_compare {
  bool operator()(const gem& g1, const gem& g2) { return g1.v < g2.v; }
};

int main(void) {
  std::cin.tie(0);
  std::ios_base::sync_with_stdio(0);

  int n, k;
  std::cin >> n >> k;

  std::vector<gem> gems;
  for (int i = 0; i < n; ++i) {
    int mm, vv;
    std::cin >> mm >> vv;
    gems.emplace_back(gem{mm, vv});
  }

  std::vector<int> bags;
  for (int i = 0; i < k; ++i) {
    int temp;
    std::cin >> temp;
    bags.push_back(temp);
  }

  std::sort(gems.begin(), gems.end(), gem_compare);
  std::sort(bags.begin(), bags.end());

  std::priority_queue<gem, std::vector<gem>, pq_compare> p;

  int gem_index = 0;
  long long result = 0;
  for (int i = 0; i < k; ++i) {
    while (gem_index < n) {
      if (gems[gem_index].m > bags[i]) break;
      p.push(gems[gem_index++]);
    }
    if (!p.empty()) {
      result += p.top().v;
      p.pop();
    }
  }

  std::cout << result;
}