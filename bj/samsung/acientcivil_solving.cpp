#include <array>
#include <iostream>
#include <vector>

using std::array;
using std::cin;
using std::cout;
using std::vector;

array<array<int, 5>, 5> map;
vector<int> relic_pieces;

void rotate(int i, int j);

struct vec2 {
  int x, y;
};

int main() {
  int k, m;

  cin >> k >> m;

  relic_pieces.resize(m);

  // map input
  for (int i = 0; i < 5; ++i) {
    for (int j = 0; j < 5; ++j) {
      cin >> map[i][j];
    }
  }

  // relic piece input
  for (int i = 0; i < m; ++i) {
    cin >> relic_pieces[i];
  }

  // search start
  int relic_value_total = 0;
  for (int turn = 0; turn < k; ++turn) {
    int relic_value_this_turn = 0;

    for (int i = 1; i <= 3; ++i) {
      for (int j = 1; j <= 3; ++j) {
        // (i, j) is selected coordinate
        // 90, 180, 270 degree rotate
        for (int rotate = 0; rotate < 3; ++rotate) {
          rotate(i, j);
        }
      }
    }
  }

  return 0;
}

void rotate(int i, int j) {}
