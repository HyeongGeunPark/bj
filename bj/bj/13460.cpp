/*
bj13460 구슬 탈출 2
구슬 탈출 게임.

접근: 넓이 우선 탐색
*/

#include <iostream>
#include <queue>
#include <tuple>
#include <vector>

struct vec2 {
  int x, y;
  bool operator==(const vec2&) const = default;
};

char map[4][10][10];
int n, m;

void rotate(char from[][10], char to[][10], int dir) {
  int n = ::n;
  int m = ::m;
  if (dir & 1) {
    std::swap(n, m);
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      to[j][n - 1 - i] = from[i][j];
    }
  }
}

vec2 rotate(vec2 v, int dir) {
  int n = ::n;
  if (dir & 1) {
    n = ::m;
  }
  return {v.y, n - 1 - v.x};
}

int result = 11;

enum { SUCCESS = 1, FAIL = 2, NOT_DETERMINED = 3 };

inline std::tuple<int, vec2, vec2> slide(vec2 r, vec2 b, int dir) {
  auto map = ::map[dir];
  int n = ::n;
  int m = ::m;
  if (dir & 1) {
    std::swap(n, m);
  }
  bool blue_first = r.y < b.y;
  while (true) {
    ++b.y;
    if (map[b.x][b.y] == 'O') {
      return {FAIL, r, b};
    }
    if (map[b.x][b.y] != '.') {
      --b.y;
      break;
    }
  }
  while (true) {
    ++r.y;
    if (map[r.x][r.y] == 'O') {
      return {SUCCESS, r, b};
    }
    if (map[r.x][r.y] != '.') {
      --r.y;
      break;
    }
  }
  if (r == b) {
    if (blue_first)
      --r.y;
    else
      --b.y;
  }
  return {NOT_DETERMINED, r, b};
}

void solve(vec2 rr, vec2 bb) {
  std::queue<std::tuple<vec2, vec2, int, int>> q;

  for (int i = 0; i < 4; ++i) {
    q.push(std::tuple{rr, bb, 1, i});
    rr = rotate(rr, i);
    bb = rotate(bb, i);
  }

  while (q.size()) {
    auto [r, b, depth, dir] = q.front();
    q.pop();

    // slide
    auto [s, r_next, b_next] = slide(r, b, dir);
    if (r_next == r && b_next == b) continue;

    // test
    switch (s) {
      case SUCCESS:
        result = depth;
        return;
      case FAIL:
        break;
      case NOT_DETERMINED:
        // max depth
        if (depth >= 10) break;
        // rotate and push
        for (int i = (dir + 1 == 4 ? 0 : dir + 1); i != dir;
             i = (i + 1 == 4 ? 0 : i + 1)) {
          r_next = rotate(r_next, i - 1);
          b_next = rotate(b_next, i - 1);
          if ((i ^ dir) & 1) q.push(std::tuple{r_next, b_next, depth + 1, i});
        }
    }
  }
}

int main(void) {
  std::cin >> n >> m;

  vec2 red, blue;
  std::cin >> std::skipws;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      std::cin >> map[0][i][j];
      if (map[0][i][j] == 'R') {
        red = {i, j};
        map[0][i][j] = '.';
      }
      if (map[0][i][j] == 'B') {
        blue = {i, j};
        map[0][i][j] = '.';
      }
    }
  }
  for (int i = 0; i < 3; ++i) {
    rotate(map[i], map[i + 1], i);
  }

  solve(red, blue);

  std::cout << (result == 11 ? -1 : result);
}