#include <algorithm>
#include <iostream>
#include <vector>

struct ccnt {
  char c;
  int n;
};

bool ccnt_less(const ccnt& a, const ccnt& b) { return a.n < b.n; }

int main(void) {
  std::string str;
  std::cin >> str;
  std::vector<ccnt> count;

  int cnt[26] = {
      0,
  };
  for (char c : str) {
    ++cnt[c - 'a'];
  }

  for (char i = 0; i < 26; ++i) {
    if (cnt[i]) {
      count.push_back(ccnt{i + 'a', cnt[i]});
    }
  }

  std::sort(count.begin(), count.end(), ccnt_less);

  int prevcount = 0;
  int ccc = 0;
  bool result = true;
  for (ccnt c : count) {
    if (ccc == 0) {
      prevcount = c.n;
      ccc = 1;
      continue;
    }
    if (prevcount != c.n) {
      if (ccc != 2) {
        result = false;
        break;
      }
      prevcount = c.n;
      ccc = 1;
    } else
      ccc++;
  }
  if (ccc != 2) {
    result = false;
  }

  if (result)
    std::cout << "Yes";
  else
    std::cout << "No";
}