/*
bj34220 그래프 리뷰 유튜버

정점 4개 이상의 트리를 입력받아, 여기에 최소 개수의 간선을 추가해
chromatic number가 4 이상이 되는 그래프로 만들어라.

접근
1. 트리의 chromatic number는 2이다.
2. chromatic number가 4 이상이 되려면, 정점 4개의 완전 그래프가 subgraph로
있어야 함.
3. 점 4개의 subtree를 임의로 골라, 그 subtree에 3개의 간선을 추가해
완전 그래프로 만든다.
*/

#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>

int main(void) {
  // c++ fast io
  std::cin.tie(0);
  std::ios_base::sync_with_stdio(false);

  // input
  int n;
  std::cin >> n;

  std::unordered_multimap<int, int> edges;
  std::vector<std::pair<int, int>> adjacent_edges;
  edges.reserve(static_cast<size_t>(1.5l * n));


  for (int i = 0; i < n-1; ++i) {
    int v1, v2;
    std::cin >> v1 >> v2;
    edges.insert({v1, v2});
    edges.insert({v2, v1});

    if (edges.count(v1) == 3) {
      auto r = edges.equal_range(v1);
      adjacent_edges.insert(adjacent_edges.end(), r.first, r.second);
      goto print1; 
    } 
    if (edges.count(v2) == 3) {
      auto r = edges.equal_range(v2);
      adjacent_edges.insert(adjacent_edges.end(), r.first, r.second);
      goto print1;
    }
  }

  // 위에서 차수 3 이상 정점을 찾지 못하면 직선 그래프
  // 인접 4개 정점을 임의로 고른다.
  {
    int prev = 0;
    int current = 1;
    for (;; ++current) {
      if (edges.count(current) == 1) break;
    }
    while (adjacent_edges.size() != 3) {
      auto r = edges.equal_range(current);
      for (auto i = r.first; i != r.second; ++i) {
        if ((*i).second != prev) {
          prev = current;
          current = (*i).second;
          break;
        }
      }
      adjacent_edges.push_back({prev, current});
    }
    goto print2;
  }

print1:
  {
    int& a = adjacent_edges[0].second;
    int& b = adjacent_edges[1].second;
    int& c = adjacent_edges[2].second;
    std::cout << "3\n";
    std::cout << a << " " << b << '\n';
    std::cout << b << " " << c << '\n';
    std::cout << c << " " << a << '\n'; 
  }
  return 0;

print2:
  {
    int& a = adjacent_edges[0].first;
    int& b = adjacent_edges[1].first;
    int& c = adjacent_edges[1].second;
    int& d = adjacent_edges[2].second;
    std::cout << "3\n";
    std::cout << a << " " << d << '\n';
    std::cout << a << " " << c << '\n';
    std::cout << d << " " << b << '\n'; 
  }
  return 0;
}
