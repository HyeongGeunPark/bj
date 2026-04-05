/*
bj31250 신제품 개발

핵심 아이디어.

1. c가 증가할수록 "사용 가능한 간선"만 늘어난다.
   따라서 어떤 시점의 c에 대해, 각 정점에서 실제로 선택되는 간선은
   "현재까지 활성화된 간선들 중 그 정점에서 b가 가장 큰 간선" 하나뿐이다.

2. 즉, 현재 c가 어떤 다음 임계값 B를 넘기 전까지는
   그래프 전체가 "각 정점에서 다음 정점이 하나로 정해진 함수 그래프"가 된다.

3. 함수 그래프에서 한 정점에서 출발한 경로는
   항상 "꼬리(tail) + 순환(loop)" 형태가 된다.

4. 따라서 매 phase마다
   - 현재 활성 간선들로 next_node[]를 만들고
   - 현재 정점 u에서 시작하는 tail + loop 구조를 분석한 뒤
   - 다음 간선이 활성화될 때까지 몇 step 갈 수 있는지 계산해서
   한 번에 점프한다.

5. c의 정확한 큰 값 전체는 들고 다닐 필요가 없다.
   우리는 다음 B를 넘는지만 알면 되므로
   c는 CAP = max(B) + 1 에서 saturate(포화) 시켜도 충분하다.
   다만 출력은 c mod MOD 이므로 mod 값은 따로 정확히 유지한다.

MSVC 주의.
- __int128 사용 안 함
- saturating arithmetic 유틸리티 사용
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

using ull = unsigned long long; // 64-bit unsigned integer

constexpr ull MODULO = 1'000'000'007ULL;
constexpr ull INF64 = std::numeric_limits<ull>::max();

namespace uint64_util {

  // limit에서 saturate되는 덧셈
  ull sat_add(ull a, ull b, ull limit) {
    if (a >= limit) {
      return limit;
    }

    if (b >= limit - a) {
      return limit;
    }

    return a + b;
  }

  // limit에서 saturate되는 곱셈
  ull sat_mul(ull a, ull b, ull limit) {
    if (a == 0 || b == 0) {
      return 0;
    }

    if (a > limit / b) {
      return limit;
    }

    return a * b;
  }

  // modulo 덧셈
  ull add_mod(ull a, ull b, ull modulo) {
    a %= modulo;
    b %= modulo;

    ull x = a + b;
    if (x >= modulo) {
      x -= modulo;
    }
    return x;
  }

  // modulo 곱셈
  // 여기서는 modulo = 1e9+7 이고, a,b는 먼저 modulo로 줄이므로
  // a*b < 1e18 정도라 ull 범위에서 안전하다.
  ull mul_mod(ull a, ull b, ull modulo) {
    a %= modulo;
    b %= modulo;
    return (a * b) % modulo;
  }

}

struct edge {
  edge() : src(0), dest(0), b(0) {}
  edge(int src, int dest, ull b) : src(src), dest(dest), b(b) {}

  int src;
  int dest;
  ull b;
};

struct route_info {
  // order[t] = t step 후의 정점 (단, t < order.size() 인 범위)
  // order[0] = 시작 정점
  std::vector<int> order;

  // loop_start = 순환이 시작되는 위치
  // loop_length = 순환 길이
  int loop_start;
  int loop_length;

  // prefix_sum[t] = 처음 t step 동안 증가한 c의 합 (CAP에서 포화)
  // prefix_sum_mod[t] = 위 값을 mod로 관리한 값
  //
  // 주의:
  // t step 동안 더해지는 것은 "도착한 정점의 A값"이다.
  // 따라서 prefix_sum[0] = 0 이고,
  // prefix_sum[1] = A[order[1]] 이다.
  std::vector<ull> prefix_sum;
  std::vector<ull> prefix_sum_mod;

  // loop_prefix_sum[s] = 순환에 진입한 뒤, 순환 안에서 s step 진행했을 때의 증가량
  // loop_prefix_sum[0] = 0
  std::vector<ull> loop_prefix_sum;
  std::vector<ull> loop_prefix_sum_mod;

  ull loop_sum;      // 순환 한 바퀴 증가량 (CAP에서 포화)
  ull loop_sum_mod;  // 순환 한 바퀴 증가량 mod
};

struct jump_result {
  jump_result() : vertex(0), add_sum_cap(0), add_sum_mod(0) {}

  int vertex;       // jump 후 도착 정점
  ull add_sum_cap;  // 증가한 c (cap_limit에서 포화)
  ull add_sum_mod;  // 증가한 c mod MODULO
};

// 현재 next_node[]가 고정되어 있을 때,
// start 정점에서 시작하는 함수 그래프 경로를 tail + loop 형태로 분석한다.
route_info build_route_info(int start, const std::vector<int>& next_node, const std::vector<ull>& a, ull cap) {
  route_info result;

  int n = static_cast<int>(next_node.size()) - 1;
  std::vector<int> first_visit_pos(n + 1, -1);

  int cursor = start;

  // 처음 반복 방문하는 정점을 찾을 때까지 전진
  while (first_visit_pos[cursor] == -1) {
    first_visit_pos[cursor] = static_cast<int>(result.order.size());
    result.order.push_back(cursor);
    cursor = next_node[cursor];
  }

  result.loop_start = first_visit_pos[cursor];
  result.loop_length = static_cast<int>(result.order.size()) - result.loop_start;

  int length = static_cast<int>(result.order.size());

  result.prefix_sum.assign(length, 0);
  result.prefix_sum_mod.assign(length, 0);

  // prefix_sum[i] = i step 후까지의 누적 증가량
  for (int i = 1; i < length; ++i) {
    int arrived_vertex = result.order[i];

    result.prefix_sum[i] =
      uint64_util::sat_add(result.prefix_sum[i - 1], a[arrived_vertex], cap);

    result.prefix_sum_mod[i] =
      uint64_util::add_mod(result.prefix_sum_mod[i - 1], a[arrived_vertex] % MODULO, MODULO);
  }

  result.loop_prefix_sum.assign(result.loop_length + 1, 0);
  result.loop_prefix_sum_mod.assign(result.loop_length + 1, 0);

  // 순환 시작점이 order[loop_start] 라고 할 때,
  // 순환 안에서의 이동 순서는
  // order[loop_start + 1], ..., order[last], order[loop_start]
  // 이 된다.
  for (int step = 1; step <= result.loop_length; ++step) {
    int index;
    if (step == result.loop_length) {
      index = result.loop_start;
    }
    else {
      index = result.loop_start + step;
    }

    int arrived_vertex = result.order[index];

    result.loop_prefix_sum[step] =
      uint64_util::sat_add(result.loop_prefix_sum[step - 1], a[arrived_vertex], cap);

    result.loop_prefix_sum_mod[step] =
      uint64_util::add_mod(result.loop_prefix_sum_mod[step - 1], a[arrived_vertex] % MODULO, MODULO);
  }

  result.loop_sum = result.loop_prefix_sum[result.loop_length];
  result.loop_sum_mod = result.loop_prefix_sum_mod[result.loop_length];

  return result;
}

// 현재 route_info가 나타내는 함수 그래프에서,
// "다음 간선 활성화 임계값"까지 도달하려면 최소 몇 step이 필요한지를 계산한다.
//
// need = (다음 threshold B) - 현재 c_cap
//
// 반환값:
// - 최소 step 수
// - 불가능하거나 남은 k 안에서 못 가면 INF64
ull find_cross_step(const route_info& info, ull need, ull remaining_k) {
  // 1) tail 구간에서 먼저 직접 확인
  ull tail_steps = std::min(remaining_k, static_cast<ull>(info.loop_start));

  for (ull step = 1; step <= tail_steps; ++step) {
    if (info.prefix_sum[static_cast<size_t>(step)] >= need) {
      return step;
    }
  }

  // tail 안에서 못 넘었고, 남은 step도 tail까지만 가능하면 실패
  if (remaining_k <= static_cast<ull>(info.loop_start)) {
    return INF64;
  }

  // 2) 이제 순환에 진입한 뒤를 본다.
  // tail을 지난 뒤에도 아직 need를 못 채운 상태다.
  ull need_after_tail = need - info.prefix_sum[info.loop_start];

  // 순환 증가량이 0이면, 이후로도 절대 threshold를 넘을 수 없다.
  if (info.loop_sum == 0) {
    return INF64;
  }

  // 남은 step 수 안에서 가능한 최대 full cycle 수
  ull max_cycle_by_k = (remaining_k - static_cast<ull>(info.loop_start)) / static_cast<ull>(info.loop_length);

  // 마지막 partial cycle 직전까지 몇 번 full cycle을 돌아야 하는가
  // (need_after_tail - 1) / loop_sum
  ull full_cycles_before_last = (need_after_tail - 1) / info.loop_sum;

  if (full_cycles_before_last > max_cycle_by_k) {
    return INF64;
  }

  // 이제 마지막 cycle 안에서 몇 step 더 가면 되는지 찾는다.
  ull remaining_need = need_after_tail - full_cycles_before_last * info.loop_sum;

  int partial_steps = 1;
  while (partial_steps <= info.loop_length && info.loop_prefix_sum[partial_steps] < remaining_need) {
    ++partial_steps;
  }

  ull total_steps =
    static_cast<ull>(info.loop_start) +
    full_cycles_before_last * static_cast<ull>(info.loop_length) +
    static_cast<ull>(partial_steps);

  if (total_steps > remaining_k) {
    return INF64;
  }

  return total_steps;
}

// 현재 route_info에서 t step 진행했을 때
// - 도착 정점
// - 증가한 c의 합 (cap_limit에서 포화)
// - 증가한 c mod MODULO
// 를 계산한다.
jump_result simulate_steps(const route_info& info, ull t, ull cap_limit) {
  jump_result result;

  int length = static_cast<int>(info.order.size());

  // 아직 첫 반복 전이라면 prefix 정보만으로 충분
  if (t < static_cast<ull>(length)) {
    result.vertex = info.order[static_cast<size_t>(t)];
    result.add_sum_cap = std::min(info.prefix_sum[static_cast<size_t>(t)], cap_limit);
    result.add_sum_mod = info.prefix_sum_mod[static_cast<size_t>(t)];
    return result;
  }

  // 순환에 진입한 뒤 처리
  ull remain = t - static_cast<ull>(info.loop_start);
  ull full_cycles = remain / static_cast<ull>(info.loop_length);
  int partial_steps = static_cast<int>(remain % static_cast<ull>(info.loop_length));

  if (partial_steps == 0) {
    result.vertex = info.order[info.loop_start];
  }
  else {
    result.vertex = info.order[info.loop_start + partial_steps];
  }

  // mod 누적 계산
  result.add_sum_mod = info.prefix_sum_mod[info.loop_start];
  result.add_sum_mod =
    uint64_util::add_mod(
      result.add_sum_mod,
      uint64_util::mul_mod(full_cycles, info.loop_sum_mod, MODULO),
      MODULO
    );
  result.add_sum_mod =
    uint64_util::add_mod(
      result.add_sum_mod,
      info.loop_prefix_sum_mod[partial_steps],
      MODULO
    );

  // cap_limit에서 saturate되는 실제 증가량 계산
  ull current = std::min(info.prefix_sum[info.loop_start], cap_limit);
  ull left = cap_limit - current;

  ull cycle_part = uint64_util::sat_mul(full_cycles, info.loop_sum, left);
  current += cycle_part;
  left = cap_limit - current;

  current += std::min(info.loop_prefix_sum[partial_steps], left);

  result.add_sum_cap = current;
  return result;
}

int main(void) {
  // c++ fast io
  std::cin.tie(0);
  std::ios_base::sync_with_stdio(false);

  // input 1
  int n;
  int m;
  ull k;

  std::cin >> n >> m >> k;

  // data structures
  std::vector<ull> a(n + 1);
  std::vector<edge> edges;
  edges.reserve(m);

  // input 2
  for (int i = 1; i <= n; ++i) {
    std::cin >> a[i];
  }

  ull max_b = 0;

  for (int i = 0; i < m; ++i) {
    int u, v;
    ull bb;

    std::cin >> u >> v >> bb;
    edges.emplace_back(u, v, bb);

    if (max_b < bb) {
      max_b = bb;
    }
  }

  // c는 max_b + 1 까지만 정확히 알면 충분하다.
  // 그 이상은 "모든 간선이 이미 활성화되었다"는 사실만 중요하다.
  ull cap = max_b + 1;

  // b 오름차순으로 간선을 정렬
  std::sort(edges.begin(), edges.end(), [](const edge& l, const edge& r) {
    return l.b < r.b;
  });

  // 현재 활성화된 간선들에 의해 각 정점에서 실제로 선택되는 다음 정점
  //
  // 간선이 하나도 활성화되지 않았다면 "이동하지 않음"인데,
  // 이것은 next_node[u] = u 인 self-loop 로 생각해도
  // 문제 동작과 완전히 같다.
  std::vector<int> next_node(n + 1);
  for (int i = 1; i <= n; ++i) {
    next_node[i] = i;
  }

  // 현재 상태
  int current_vertex = 1;
  ull c_cap = 0; // cap에서 포화시킨 c
  ull c_mod = 0; // c mod MODULO

  // 아직 활성화하지 않은 간선의 시작 위치
  int edge_cursor = 0;

  // 현재 c_cap 이하의 b를 가진 간선들을 모두 활성화
  auto unlock_edges = [&]() {
    while (edge_cursor < m && edges[edge_cursor].b <= c_cap) {
      // 같은 src에 대해 더 큰 b가 나중에 오므로
      // 지금 간선으로 덮어쓰면 "현재 사용되는 간선"이 된다.
      next_node[edges[edge_cursor].src] = edges[edge_cursor].dest;
      ++edge_cursor;
    }
  };

  // 초기 c = 0 에서 활성화되는 간선 반영
  unlock_edges();

  while (k > 0) {
    // 현재 phase의 고정 함수 그래프 분석
    route_info info = build_route_info(current_vertex, next_node, a, cap);

    // 더 이상 활성화될 간선이 없으면,
    // 이 함수 그래프가 끝까지 유지되므로 남은 k를 한 번에 처리할 수 있다.
    if (edge_cursor == m) {
      jump_result last = simulate_steps(info, k, cap - c_cap);

      current_vertex = last.vertex;
      c_cap = uint64_util::sat_add(c_cap, last.add_sum_cap, cap);
      c_mod = uint64_util::add_mod(c_mod, last.add_sum_mod, MODULO);

      k = 0;
      break;
    }

    // 다음으로 활성화될 간선의 임계값
    ull next_threshold = edges[edge_cursor].b;

    // unlock_edges()를 직전에 호출했으므로 항상 next_threshold > c_cap
    ull need = next_threshold - c_cap;

    // 다음 threshold를 처음 넘는 최소 step 수
    ull step_to_cross = find_cross_step(info, need, k);

    // 남은 k 안에서 threshold를 못 넘으면 그냥 끝까지 진행
    ull step_to_run = (step_to_cross == INF64 ? k : step_to_cross);

    jump_result jump = simulate_steps(info, step_to_run, cap - c_cap);

    current_vertex = jump.vertex;
    c_cap = uint64_util::sat_add(c_cap, jump.add_sum_cap, cap);
    c_mod = uint64_util::add_mod(c_mod, jump.add_sum_mod, MODULO);

    k -= step_to_run;

    // c가 증가했으니 새로 활성화되는 간선 반영
    unlock_edges();
  }

  // result print
  std::cout << current_vertex << ' ' << c_mod;
  return 0;
}