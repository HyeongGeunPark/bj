/*
bj14588 Line Friends (Small)

수직선 위에 N개의 선분이 있고, 서로 겹치는 선분은 "친한" 선분이다.

"친함" 관계로 그래프를 만들고, 각 선분 사이의 거리를 구하여라.

선분 정보 입력 후 임의의 두 점 사이의 최단거리를 묻는 쿼리가 여러번 입력되면
그에 알맞은 답을 출력하라.

접근: 그래프 이론, 모든 점 사이의 최단거리 구하기 (플로이드-워셜)

* 플로이드-워셜 알고리즘의 시간복잡도가 n^3이므로 선분 사이의 친함 관계를
* 파악할 때 그냥 모든 선분 사이의 관계를 한 번씩 검토해 보는 것(n^2)으로
충분하다.
*/

#include <cstring>
#include <iostream>
#include <sstream>
#include <vector>

typedef std::pair<int, int> int_vec2;

class my_sstream : public std::basic_ostringstream<char> {
 public:
  ~my_sstream() { std::cout << this->str(); }
};

my_sstream log_out;

bool is_friend(const int_vec2& a, const int_vec2& b) {
  // a   -------
  // b           --------
  if (a.second < b.first
      // a               -------
      // b        -----
      || b.second < a.first)
    return false;
  else
    return true;
}

struct int_mat {
 public:
  int_mat(const int row, const int col)
      : row{row}, col{col}, data{new int[col * row]} {
    std::memset(data, 0x00, sizeof(int) * col * row);
  }

  int& operator()(int _row, int _col) { return data[_row * col + _col]; }

  ~int_mat() { delete[] data; }

  const int row;
  const int col;

 private:
  int* data;
};

void debug_out(int_mat& obj) {
  for (int i = 0; i < obj.row; ++i) {
    for (int j = 0; j < obj.col; ++j) {
      std::cerr << obj(i, j) << '\t';
    }
    std::cerr << '\n';
  }
}

int main(void) {
  // c++ fast io
  std::cin.tie(0);
  std::ios_base::sync_with_stdio(false);

  // input
  int n;
  std::cin >> n;

  std::vector<int_vec2> lines(n);

  for (int i = 0; i < n; ++i) {
    std::cin >> lines[i].first;
    std::cin >> lines[i].second;
  }

  // build connectivity graph
  int_mat g(n, n);

  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      if (is_friend(lines[i], lines[j])) {
        g(i, j) = g(j, i) = 1;
      } else {
        // 적당히 크지만 오버플로우는 나지 않는 값
        g(i, j) = g(j, i) = 1 << 20;
      }
    }
  }

  // floyd-warshall algorithm
  for (int k = 0; k < n; ++k) {
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        g(i, j) = std::min<int>(g(i, j), g(i, k) + g(k, j));
      }
    }
  }

  int q;
  std::cin >> q;

  for (int i = 0; i < q; ++i) {
    int a, b;
    std::cin >> a >> b;
    // 1-based index to 0-based index
    --a;
    --b;

    if (g(a, b) < 1 << 20) {
      log_out << g(a, b) << '\n';
    } else {
      log_out << -1 << '\n';
    }
  }
  return 0;
}