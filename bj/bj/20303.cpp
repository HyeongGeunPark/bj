/*

bj20303 할로윈의 양아치

접근법
1. 친구 관계를 이용하여 disjoint set을 구하고,
  동시에 각 서로소 집합의 아이 수와 사탕 양을 구한다.

2. 아이 수 K 미만, 최대 사탕 조합을 구한다.(가방 문제)

*/
#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>

int candies[30001];
int root[30001];

int mem[2][3000];

int find_root(int v) {
  if (root[v] < 0) return v;
  root[v] = find_root(root[v]);
  return root[v];
}

void merge(int v1, int v2) {
  v1 = find_root(v1);
  v2 = find_root(v2);
  if (v1 == v2) return;

  if (root[v1] > root[v2]) std::swap(v1, v2);
  candies[v1] += candies[v2];
  root[v1] += root[v2];
  root[v2] = v1;
}

int main(void) {
  std::cin.tie(0);
  std::ios_base::sync_with_stdio(0);

  int n, m, k;
  std::cin >> n >> m >> k;

  std::memset(root, 0xff, sizeof(int) * (n + 1));

  for (int i = 1; i <= n; ++i) {
    std::cin >> candies[i];
  }
  for (int i = 0; i < m; ++i) {
    // disjoint set
    int v1, v2;
    std::cin >> v1 >> v2;
    merge(v1, v2);
  }

  // 가방 문제
  auto prev = mem[0];
  auto current = mem[1];
  std::memset(prev, 0, sizeof(int) * k);
  for (int i = 1; i <= n; ++i) {
    if (root[i] > 0) continue;
    for (int j = 0; j < k; ++j) {
      if (j >= (-root[i])) {
        current[j] = prev[j - (-root[i])] + candies[i];
      }
      current[j] = std::max(current[j], prev[j]);
    }
    std::swap(current, prev);
  }

  std::cout << prev[k - 1];
}
