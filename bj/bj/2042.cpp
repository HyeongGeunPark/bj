/*
bj2042 구간 합 구하기

중간에 수의 변경이 빈번하게 일어나는 어레이에서
주어진 부분의 부분합을 구하는 문제.

접근: 간단한 세그먼트 트리
합을 유지하는 세그먼트 트리를 이용하면 된다.

주의
1. 입출력이 매우 빈번하므로 std::cin.tie(0), std::ios_base::sync_with_stdio(0)
등 고려가 필요하다.
2. 입력의 양이 매우 많으므로, 최대한 한 번에 몰아서 입력 받기를 끝낸 뒤
  자료 처리를 하는 것이 좋다.
*/

#include <cmath>
#include <iostream>
#include <vector>

// MOCKUP, implement later
class SegmentTree {
 public:
  explicit SegmentTree(int n)
      : sz{n},
        height{(int)std::ceil(std::log2(n))},
        base{1 << (height)},
        data(base * 2) {
    get_n_from_stream(std::cin, n);
    init();
  }

  void get_n_from_stream(std::istream& is, int count) {
    for (int i = 0; i < count; ++i) {
      is >> data[base + i];
    }
  }

  void update(int index, long long new_value) {
    index += base;
    long long difference = new_value - data[index];
    while (index) {
      data[index] += difference;
      index /= 2;
    }
  }

  long long query(int l, int r) const { return _query(l, r, 0, base, 1); }

 private:
  int sz;
  int height;
  int base;
  std::vector<long long> data;

  long long _query(int l, int r, int start, int end, int idx) const {
    if (r <= start || end <= l) {
      return 0;
    } else if (l <= start && end <= r) {
      return data[idx];
    } else {
      int mid = (start + end) / 2;
      return _query(l, r, start, mid, idx * 2) +
             _query(l, r, mid, end, idx * 2 + 1);
    }
  }

  void init() {
    for (int i = base - 1; i > 0; --i) {
      data[i] = data[2 * i] + data[2 * i + 1];
    }
  }
};

struct command_t {
  int command;
  long long arg1, arg2;
  friend std::istream& operator>>(std::istream& is, command_t& c) {
    is >> c.command >> c.arg1 >> c.arg2;
    return is;
  }
};

int main() {
  std::cin.tie(0);
  std::ios_base::sync_with_stdio(0);

  int n, m, k;
  std::cin >> n >> m >> k;

  SegmentTree st(n);

  // command input
  std::vector<command_t> commands(m + k);
  for (int i = 0; i < m + k; ++i) {
    std::cin >> commands[i];
  }

  // command execute
  for (auto& [command, arg1, arg2] : commands) {
    switch (command) {
      case 1: {
        // value update
        // input uses 1-based, closed range
        // my SegmentTree class uses 0-based, half-open range
        st.update(arg1 - 1, arg2);
      } break;
      case 2: {
        // partial sum query
        std::cout << st.query(arg1 - 1, arg2) << '\n';
      } break;
    }
  }
  return 0;
}