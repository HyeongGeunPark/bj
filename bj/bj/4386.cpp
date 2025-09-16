/*

bj4386 별자리 만들기

접근법(최소 스패닝 트리)

별과 별 사이의 거리를 구하여 인접 행렬을 만든 뒤
Prim, Kruskal 중 하나를 이용해 최소 스패닝 트리를 만들면 된다.

*/

#include <cmath>
#include <iomanip>
#include <iostream>
#include <queue>
#include <vector>

struct Vec2 {
  double x, y;
};

struct Edge {
  int dst;
  double len;
};

struct edge_comp {
  bool operator()(const Edge& e1, const Edge& e2) { return e1.len > e2.len; };
};

double distance(const Vec2& v1, const Vec2& v2) {
  return std::sqrt(std::pow(v1.x - v2.x, 2) + std::pow(v1.y - v2.y, 2));
}

std::vector<Vec2> stars;
std::vector<std::vector<double>> adj;

int main(void) {
  std::cin.tie(0);
  std::ios_base::sync_with_stdio(0);

  int n;
  std::cin >> n;

  std::vector<Vec2> stars(n);
  std::vector<std::vector<double>> adj(n, std::vector<double>(n));

  for (int i = 0; i < n; ++i) {
    std::cin >> stars[i].x >> stars[i].y;
  }

  // 거리 구하기
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      adj[i][j] = adj[j][i] = distance(stars[i], stars[j]);
    }
  }

  // 간선 밀도가 높으므로 Prim's algorithm 사용
  std::vector<bool> included(n, false);
  std::priority_queue<Edge, std::vector<Edge>, edge_comp> edges;
  included[0] = true;
  int current = 0;
  int cnt = 1;
  double total_len = 0;

  while (cnt < n) {
    for (int i = 0; i < n; ++i) {
      if (!included[i]) edges.emplace(Edge{i, adj[current][i]});
    }

    while (included[edges.top().dst]) edges.pop();

    current = edges.top().dst;
    total_len += edges.top().len;
    included[current] = true;
    ++cnt;
  }

  std::cout << std::fixed << std::setprecision(2) << total_len;
}