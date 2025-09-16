/*
bj11505 구간 곱 구하기

변경이 빈번하게 일어나는 배열에서 구간의 곱을 구하라.

접근법: 간단한 세그먼트 트리(곱)
*/

#include <cmath>
#include <iostream>
#include <vector>

class SegmentTree {
  using ll = long long;

 public:
  explicit SegmentTree(int n)
      : height{static_cast<int>(std::ceil(std::log2(n)))},
        base{1 << height},
        data(base * 2, 1) {
    get_from_stdcin(n);
    init();
  }

  ll query(int l, int r) { return _query(l, r, 0, base, 1); }

  void update(int idx, ll newValue) {
    idx += base;
    data[idx] = newValue;
    idx /= 2;
    while (idx) {
      data[idx] = (data[idx * 2] * data[idx * 2 + 1]) % MOD;
      idx /= 2;
    }
  }

 private:
  void get_from_stdcin(int n) {
    for (int i = 0; i < n; ++i) {
      std::cin >> data[base + i];
    }
  }

  void init() {
    for (int i = base - 1; i >= 0; --i) {
      data[i] = data[2 * i] * data[2 * i + 1];
      data[i] %= MOD;
    }
  }

  ll _query(int l, int r, int s, int e, int idx) {
    if (l <= s && e <= r) {
      return data[idx];
    } else if (e <= l || r <= s) {
      return 1;
    } else {
      int mid = (s + e) / 2;
      return (_query(l, r, s, mid, idx * 2) *
              _query(l, r, mid, e, idx * 2 + 1)) %
             MOD;
    }
  }

  int height;
  int base;
  std::vector<ll> data;
  static constexpr ll MOD = 1'000'000'007;
};

struct Command {
  int command, arg1;
  long long arg2;
};

int main() {
  std::cin.tie(0);
  std::ios_base::sync_with_stdio(0);

  int n, m, k;
  std::cin >> n >> m >> k;

  // array input and segment tree init
  SegmentTree st(n);

  // command and arguments input
  std::vector<Command> commands;
  commands.reserve(m + k);
  for (int i = 0; i < m + k; ++i) {
    int c, a1;
    long long a2;
    std::cin >> c >> a1 >> a2;
    commands.emplace_back(c, a1, a2);
  }

  // execute commands
  std::vector<int> results;
  results.reserve(k);
  for (auto& [command, arg1, arg2] : commands) {
    switch (command) {
      case 1: {
        // update
        st.update(arg1 - 1, arg2);
      } break;
      case 2: {
        // query
        results.push_back(st.query(arg1 - 1, arg2));
      } break;
    }
  }

  // output
  for (int i : results) {
    std::cout << i << '\n';
  }

  return 0;
}