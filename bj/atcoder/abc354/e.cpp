#include <algorithm>
#include <iostream>
#include <vector>

struct card {
  int front, back;
};

std::vector<card> cards;

std::vector<char> memo(2 << 18, -1);

int solve(int iter, int used_cards) {
  // return 1 if takahashi wins
  // return 0 if aoki wins

  // base case
  if (memo[used_cards] != -1) {
    return memo[used_cards];
  }

  // find pair, remove pair and recursively call solve
  // return (iter+1)%2 if the result of called solve equals to (iter+1)%2
  // could not found pair or winning situation -> return iter%2
  for (int i = 0; i < cards.size(); ++i) {
    if ((1 << i) & used_cards) continue;
    for (int j = i + 1; j < cards.size(); ++j) {
      if ((1 << j) & used_cards) continue;
      if (cards[i].front == cards[j].front || cards[i].back == cards[j].back) {
        int new_used_cards = used_cards | (1 << i) | (1 << j);
        if (solve(iter + 1, new_used_cards) == (iter + 1) % 2) {
          memo[used_cards] = (iter + 1) % 2;
          return (iter + 1) % 2;
        }
      }
    }
  }
  memo[used_cards] = iter % 2;
  return iter % 2;
}

int main(void) {
  int n;
  std::cin >> n;
  for (int i = 0; i < n; ++i) {
    int front, back;
    std::cin >> front >> back;
    cards.push_back(card{front, back});
  }

  std::cout << (solve(0, 0) == 1 ? "Takahashi" : "Aoki");
}