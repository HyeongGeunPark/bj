/*

bj12100 2048(easy)

2048 게임에서, 5번 움직여서 만들 수 있는 가장 큰 블록의 값을 구하여라.

접근법: 전수탐색(dfs)

경우의 수가 작기 때문에(4^5 * n^2 = 1024 * 20 * 20가지) 전부 탐색해도 된다.


*/
#include <iostream>
#include <queue>
#include <vector>

using mat2int = std::vector<std::vector<int>>;

enum direction { UP = 0, DOWN, RIGHT, LEFT };

void test_print(std::vector<std::vector<int>>& mat2d);

void move(std::vector<std::vector<int>>& board, direction dir) {
  if (dir == direction::UP) {
    for (int i = 0; i < board.size(); ++i) {
      std::queue<int> q;
      for (int j = 0; j < board.size(); ++j) {
        if (board[j][i] != 0) q.push(board[j][i]);
      }
      int idx = 0;
      bool flag = true;
      while (idx < board.size()) {
        if (q.empty()) {
          board[idx++][i] = 0;
          continue;
        }
        if (flag) {
          board[idx++][i] = q.front();
          q.pop();
          flag = false;
          continue;
        }
        if (board[idx - 1][i] == q.front()) {
          q.pop();
          board[idx - 1][i] <<= 1;
          flag = true;
          continue;
        }
        board[idx++][i] = q.front();
        q.pop();
      }
    }
  } else if (dir == direction::DOWN) {
    for (int i = 0; i < board.size(); ++i) {
      std::queue<int> q;
      for (int j = board.size() - 1; j >= 0; --j) {
        if (board[j][i] != 0) q.push(board[j][i]);
      }
      int idx = board.size() - 1;
      bool flag = true;
      while (idx < board.size()) {
        if (q.empty()) {
          board[idx--][i] = 0;
          continue;
        }
        if (flag) {
          board[idx--][i] = q.front();
          q.pop();
          flag = false;
          continue;
        }
        if (board[idx + 1][i] == q.front()) {
          q.pop();
          board[idx + 1][i] <<= 1;
          flag = true;
          continue;
        }
        board[idx--][i] = q.front();
        q.pop();
      }
    }
  }
  if (dir == direction::LEFT) {
    for (int i = 0; i < board.size(); ++i) {
      std::queue<int> q;
      for (int j = 0; j < board.size(); ++j) {
        if (board[i][j] != 0) q.push(board[i][j]);
      }
      int idx = 0;
      bool flag = true;
      while (idx < board.size()) {
        if (q.empty()) {
          board[i][idx++] = 0;
          continue;
        }
        if (flag) {
          board[i][idx++] = q.front();
          q.pop();
          flag = false;
          continue;
        }
        if (board[i][idx - 1] == q.front()) {
          q.pop();
          board[i][idx - 1] <<= 1;
          flag = true;
          continue;
        }
        board[i][idx++] = q.front();
        q.pop();
      }
    }
  }
  if (dir == direction::RIGHT) {
    for (int i = 0; i < board.size(); ++i) {
      std::queue<int> q;
      for (int j = board.size() - 1; j >= 0; --j) {
        if (board[i][j] != 0) q.push(board[i][j]);
      }
      int idx = board.size() - 1;
      bool flag = true;
      while (idx < board.size()) {
        if (q.empty()) {
          board[i][idx--] = 0;
          continue;
        }
        if (flag) {
          board[i][idx--] = q.front();
          q.pop();
          flag = false;
          continue;
        }
        if (board[i][idx + 1] == q.front()) {
          q.pop();
          board[i][idx + 1] <<= 1;
          flag = true;
          continue;
        }
        board[i][idx--] = q.front();
        q.pop();
      }
    }
  }
  // test_print(board);
}

void test_print(const mat2int& mat2d) {
  for (auto& v : mat2d) {
    for (auto i : v) {
      std::cout << i << ' ';
    }
    std::cout << '\n';
  }
}

int maxval = 0;
void find_max(const mat2int& board) {
  for (auto& v : board) {
    for (auto i : v) {
      maxval = std::max(maxval, i);
    }
  }
}

void dfs(mat2int board, int depth) {
  if (depth == 0) {
    find_max(board);
    // test_print(board);
    return;
  }
  for (direction d : {UP, DOWN, RIGHT, LEFT}) {
    auto b = board;
    move(b, d);
    dfs(b, depth - 1);
  }
  return;
}

int main(void) {
  int n;

  std::cin >> n;

  std::vector<std::vector<int>> board(n, std::vector<int>(n));

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      std::cin >> board[i][j];
    }
  }

  // 탐색
  dfs(board, 5);

  /*
  move(board, DOWN);
  test_print(board);
  */

  std::cout << maxval << '\n';
}