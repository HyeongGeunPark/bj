/*
bj22993 서든어택 3

n명의 플레이어가 있고 각각의 공격력이 있다.
전투가 시작되면 누구나 누구든 공격할 수 있다.
(죽은 사람은 공격하거나 공격받지 못하고, 두 사람이 동시에 공격하는 일은
일어나지 않는다.)

공격력이 X인 플레이어 A가 공격력이 Y인 플레이어 B를 공격하면,
1. X>Y이면, B가 죽고 A의 공격력은 X+Y가 된다.
2. X<Y이면, A가 죽고 B의 공격력은 X+Y가 된다.
3. X==Y이면, 아무 일도 일어나지 않는다.

1번 플레이어가 최후의 승자가 될 수 있는 좋은 전투 순서가 존재하면 Yes,
아니면 No를 출력한다.

N:플레이어의 수:[1,100'000]
A_i:각 플레이어의 공격력:[1,1'000'000'000]

접근: 그리디?

여튼 가장 공격력이 약한 플레이어부터 공격해 나가면 된다.
그런 전략으로 최후 승자가 되는 것이 불가능하면 어떤 방법으로도 안된다.

*/

#include <iostream>
#include <algorithm>
#include <vector>

namespace my {
  // similar function exists in <numerics> since C++26
  int saturating_add(int a, int b, int cap) {
    using ll = long long;
    ll aa = static_cast<ll>(a);
    ll bb = static_cast<ll>(b);
    if (aa + bb > cap) {
      return cap;
    }
    else {
      return static_cast<int>(aa + bb);
    }
  }
}

constexpr int CAP = 1'000'000'001;

int main(void) {
  // c++ fast io
  std::cin.tie(0);
  std::ios_base::sync_with_stdio(false);

  int n;
  std::cin >> n;

  long long a;
  std::cin >> a;

  std::vector<int> v(n-1);
  for (int i = 0;i<n-1;++i) {
    std::cin >> v[i];
  }

  std::sort(v.begin(), v.end());

  for (int i = 0;i < n-1;++i) {
    if (a <= v[i]) {
      std::cout << "No";
      return 0;
    }
    else {
      a = my::saturating_add(a, v[i], CAP);
    }
  }

  std::cout << "Yes";
  return 0;

}
