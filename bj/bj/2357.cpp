/*
bj2357 최솟값과 최댓값

N(<=100'000)개의 정수 배열에서,
M개의 구간 쿼리를 수행하라. (최소, 최댓값)

접근법: 간단한 세그먼트 트리(수정 없음)

최소값, 최대값을 따로 보관하는 세그먼트 트리를 구축하면 된다.

주의:
1. 입력이 많으므로 최대한 입력을 먼저 다 받고 연산을 한다.
  (연산, 입력, 출력을 번갈아가며 하지 않는다.)
2. std::cin.tie(0), std::ios_base::sync_with_stdio(0)를 사용한다.
3(optional). 백준 저지는 터미널에 연결된 표준 입출력을 사용하는 것이 아니라
  파일을 파이프로 입력하는 식으로 프로그램을 구동하므로,
  표준 입출력을 사용하는 것보다 메모리 시스템 콜을 사용하여
  입력 전체를 먼저 메모리에 올린 후 사용하는 것이
  압도적으로 빠르다.
*/

#include <cmath>
#include <iostream>
#include <limits>
#include <vector>

class SegmentTree {
 public:
  struct Data {
    int min = std::numeric_limits<int>::max();
    int max = std::numeric_limits<int>::min();
  };

  explicit SegmentTree(int sz)
      : height((int)std::ceil(std::log2(sz))),
        base{1 << height},
        data(base * 2) {
    get_n_from_stdin(sz);
    init();
  }

  Data query(int l, int r) { return _query(l, r, 0, base, 1); }

 private:
  int height;
  int base;
  std::vector<Data> data;

  Data _query(int l, int r, int s, int e, int idx) {
    if (l <= s && e <= r) {
      return data[idx];
    } else if (e <= l || r <= s) {
      return Data{};
    } else {
      int mid = (s + e) / 2;
      return calculate_minmax(_query(l, r, s, mid, idx * 2),
                              _query(l, r, mid, e, idx * 2 + 1));
    }
  }

  void get_n_from_stdin(int n) {
    for (int i = 0; i < n; ++i) {
      int temp;
      std::cin >> temp;
      data[base + i] = Data{temp, temp};
    }
  }

  void init() {
    for (int i = base - 1; i >= 0; --i) {
      data[i] = calculate_minmax(data[i * 2], data[i * 2 + 1]);
    }
  }

  Data calculate_minmax(const Data& a, const Data& b) {
    return Data{.min = std::min(a.min, b.min), .max = std::max(a.max, b.max)};
  }
};

int main() {
  std::cin.tie(0);
  std::ios_base::sync_with_stdio(0);

  int n, m;
  std::cin >> n >> m;
  SegmentTree st(n);

  std::vector<std::pair<int, int>> queries;
  queries.reserve(m);
  for (int i = 0; i < m; ++i) {
    int a, b;
    std::cin >> a >> b;
    queries.emplace_back(a, b);
  }

  std::vector<SegmentTree::Data> results;
  results.reserve(m);
  for (auto& [l, r] : queries) {
    // my SegmentTree uses 0-based index and half-close range
    // but input uses 1-based index and closed range
    results.push_back(st.query(l - 1, r));
  }

  for (auto& [min, max] : results) {
    std::cout << min << ' ' << max << '\n';
  }

  return 0;
}