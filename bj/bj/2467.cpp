#include <iostream>
#include <limits>
#include <vector>

struct answer {
  int l, r, sum;
};

int main() {
  std::vector<int> a;
  a.reserve(100'000);
  std::cin.tie(0);
  std::ios_base::sync_with_stdio(0);
  int n;

  std::cin >> n;

  for (int i = 0; i < n; ++i) {
    int temp;
    std::cin >> temp;
    a.push_back(temp);
  }

  int lp = 0;
  int rp = n - 1;
  answer ans{0, 0, std::numeric_limits<int>::max()};

  while (lp < rp) {
    int sum = a[lp] + a[rp];
    if (std::abs(sum) < ans.sum) {
      ans.l = a[lp];
      ans.r = a[rp];
      ans.sum = std::abs(sum);

      if (ans.sum == 0) {
        goto print;
      }
    }

    if (sum > 0) {
      --rp;
    } else if (sum < 0) {
      ++lp;
    } else {
      break;
    }
  }
print:
  std::cout << ans.l << ' ' << ans.r << '\n';
}
