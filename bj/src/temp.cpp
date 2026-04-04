/*
bj31250 신제품 개발

신경망 - N개 정점과 M개 간선으로 이루어진 방향 그래프.
신경망 추론을 할 떄, 우리가 관심이 있는 u번 정점과 카운터 c가 있음.
u=1, c=0으로 초기화됨.

신경망의 i번 정점은 증분 Ai를 가지고 있다.
신경망의 i번 간선은 u_i번 정점에서 v_i번 정점으로 이으며, 두 정점은 서로 다르다.
신경망의 i번 간선은 특성값 B_i를 가지고 있는데, 그 값은 모두 다르다.

다음을 K번 반복한다.
1. 먼저 u번 정점에서 나가는 간선 중 c>=B_i 면서 B_i가 가장 큰 간선을 찾아 이를 i번 간선이라 하자.
  - u를 v_i로 업데이트한다. 즉, 우리의 시선을 i번 간선을 따라 '이동시켜'
    관심이 있는 정점을 바꾼다.
  - 그런 간선이 없으면 아무 것도 하지 않는다.
2. c의 값을 c + A_u로 업데이트한다.

K = 10^18일 때도 연산을 수행할 수 있도록 하라.

2 <= N <= 500
1 <= M <= 100'000
1 <= K <= 10^18
0 <= A_i <= 10^18
1 <= u_i, v_i <= N, u_i != v_i
(u_i, v_i) 쌍은 중복되어 주어질 수 있다. (같은 경로의 여러 간선 존재 가능)
0 <= B_i <= 10^18
B_i, ..., B_M은 서로 다르다.


접근.

1. 일단 10^18번 연산을 정직하게 하면 안된다.
2. 연산을 하다 보면 어느 순간 순환이 일어나게 될 것이다.
  순환이 일어나게 되면, 이후의 연산은 생략 가능하다.

전략.
1. 이동하면서 이동한 경로를 저장해야 한다. (경로 갱신이 일어나는 경우 모두 초기화)
2. 새롭게 이동한 정점을 이전에 방문한 것인지 빠르게 평가해야 한다.
3. 발견한 루프를 "빨리 돌기"를 시도해야 한다.
  - 루프는 c가 증가함에 따라 바뀔 수 있다.
4. 루프의 "갱신 가능 경로 후보"들을 유지하고, 그 중 최소값을 빠르게 찾아야 한다.
5. 그 값과 현재 c값의 차를 이용해, 루프가 몇 번 돌아가는지 파악하여
  "빠른 이동"을 한다.
  예시)
    남은 K = 10000
    현재 u = 1
    현재 c = 9
    감지된 루프 = 1-2-3-1
    루프 증분 = 1:1, 2:2, 3:3 -> 1+2+3 = 6
    갱신 가능 경로 후보 = 1:(1->3,200), 2:(2->1, 300), 3:(3->2, 100)
      그 중 최소는 3:(3->2, 100)
    c가 100을 넘지 않을 동안에는 경로 갱신이 일어나지 않는다.
    100 - c = 91, 91 / (1+2+3) = 15 -> 따라서 15회 루프 돌기
    15 * (루프 길이) = 45
    이를 계산하면 루프 순회 후 상태는 다음과 같아진다.
    K = 10000 - 45 = 9955
    u = 1
    c = 9 + 90 = 99
    이제 경로를 초기화하고 같은 과정을 반복한다.
*/

#include <iostream>
#include <vector>
#include <set>
#include <unordered_set>
#include <algorithm>

using ull = unsigned long long; // 64-bit unsigned integer

ull limited_product(ull a, ull b, ull limit) {
  // a < 2^32
  ull b_h = b >> 32;
  ull b_l = b & 0xFFFFFFFF;

  ull limit_h = limit >> 32;
  ull limit_l = limit & 0xFFFFFFFF;

  b_h *= a;
  b_l *= a;
  b_h += b_l >> 32;
  b_l &= 0xFFFFFFFF;

  if (limit_h < b_h) {
    return limit;
  }
  else if (limit_h == b_h) {
    if (limit_l < b_l) {
      return limit;
    }
    else {
      return (b_h << 32) | b_l;
    }
  }
  else {
      return ((b_h << 32) | b_l);
  }
}

ull modulo_product(ull a, ull b, ull modulo) {
  // do not consider overflow
  a %= modulo;
  b %= modulo;
  a *= b;
  a %= modulo;
  return a;
}

struct edge {
  edge(int dest, ull b) : dest(dest), b(b) {}
  int dest;
  ull b;
};

struct compare_increasing {
  using is_transparent = void;

  bool operator()(const edge& l, const edge& r) const {
    // b값이 중복되는 경우는 없음
    return l.b < r.b;
  }
  bool operator()(const edge& l, const ull b) const {
    return l.b < b;
  }
  bool operator()(const ull b, const edge& r) const {
    return b < r.b;
  }
};

struct node_mem {
  node_mem(ull inc, int dest, ull b) : inc(inc), e(dest, b) {}
  node_mem(ull inc, edge e) : inc(inc), e(e) {}
  ull inc;
  edge e;
};


int main(void) {
  // c++ fast io
  std::cin.tie(0);
  std::ios_base::sync_with_stdio(false);

  // input 1
  int n;
  int m;
  ull k;

  std::cin >> n >> m >> k;

  // data structures for vertices and edges
  std::vector<ull> a(n+1);
  std::vector<std::set<edge, compare_increasing>> b(n+1);

  // input 2

  for (int i = 0;i < n;++i) {
    std::cin >> a[i+1];
  }

  for (int i = 0;i < m;++i) {
    int u, v;
    ull bb;
    std::cin >> u >> v >> bb;

    b[u].emplace(v, bb);
  }

  // simulation start
  int u = 1;
  ull c = 0;
  ull c_mod = 0;
  constexpr ull maximum = 1'000'000'000'000'000'000ULL;
  constexpr ull MODULO = 1'000'000'007ULL;

  std::unordered_set<int> visited;
  std::vector<int> path;


  while (k > 0) {
    if (visited.count(u) == 0) {
      // loop not detected
      // find possible route and next route candidate
      auto& edges = b[u];

      // early termination condition: this node has no outgoing edge.
      if (edges.empty()) {
        k %= MODULO;
        c_mod += (k * (a[u] % MODULO)) % MODULO;
        c_mod %= MODULO;
        break;
      }

      auto route = edges.upper_bound(c);

      // save some information for loop detection
      visited.insert(u);
      path.push_back(u);

      // step 1. find possible route
      if (route != edges.begin()) {
        // there is a possible route


        route--;

        // we don't need these edges.
        edges.erase(edges.begin(), route);

        // we found a possible route.
        u = route->dest;
      }
      else {
        // there is no possible route
        // increment c to make an available route
        if (a[u] == 0) {
          break;
        }

        ull count = (route->b - c)/ a[u] + (((route->b - c)%a[u]==0)?0:1);
        if (k <= count) {
          // early termination
          c_mod += modulo_product(k, a[u], MODULO);
          c_mod %= MODULO;
          break;
        }
        else {
          k -= count;
          if (c <= maximum) {
            c += limited_product(count, a[u], maximum);
            if (c > maximum) {
              c = maximum + 1;
            }
          }
          c_mod += modulo_product(count, a[u], MODULO);
          c_mod %= MODULO;
          path.clear();
          visited.clear();
          continue;
        }
      }

      // step 2. accumulate c
      if (c <= maximum) {
        c += a[u];
        if (c > maximum) {
          c = maximum + 1;
        }
      }
      c_mod = (c_mod + (a[u] % MODULO)) % MODULO;
      --k;
    }
    else {
      // loop detected
      ull next_candidate = maximum + 1;
      ull loop_increment = 0;
      ull loop_increment_mod = 0;
      int i = path.size() - 1;
      for (; i >= 0; --i) {
        int cursor = path[i];
        if (loop_increment <= maximum) {
          loop_increment += a[cursor];
          if (loop_increment > maximum) {
            loop_increment = maximum + 1;
          }
        }
        loop_increment_mod = (loop_increment_mod + (a[cursor] % MODULO)) % MODULO;

        auto& edges = b[cursor];
        
        auto x = edges.begin(); // we can sure that 'edges' is not empty; see "early termination condition"
        x++;
        if (x != edges.end()) {
          next_candidate = std::min(next_candidate, x->b);
        }

        if (u == cursor) {
          // loop found
          break;
        }
      }

      int loop_length = path.size() - i;

      if (next_candidate == maximum + 1) {
        // permanent loop
        ull loop_count = k / loop_length;
        loop_count %= MODULO;
        k %= loop_length;
        // we don't have to care about accurate c value
        c = maximum + 1;
        c_mod += (loop_count * loop_increment_mod) % MODULO;
        c_mod %= MODULO;
      }
      else if (next_candidate < (loop_increment + c)) {
        // loop cannot be established
        // do nothing
      }
      else {

        if (k < loop_length) continue;

        // loop
        ull loop_count = (next_candidate - c) / loop_increment;
        k -= loop_count * loop_length;
        if (c <= maximum) {
          c += limited_product(loop_count, loop_increment, maximum);
          if (c > maximum) {
            c = maximum + 1;
          }
        }
        c_mod += (loop_count * loop_increment_mod) % MODULO;
        c_mod %= MODULO;
      }
      path.clear();
      visited.clear();
    }
  }

  // result print
  std::cout << u  << ' ' << c_mod;

  return 0;

}