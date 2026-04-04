#include <bits/stdc++.h>

using namespace std;

using u64 = unsigned long long;
using u128 = __uint128_t;

static const u64 MOD = 1'000'000'007ULL;
static const u64 INF64 = numeric_limits<u64>::max();

struct Edge {
    int u, v;
    u64 b;
    bool operator<(const Edge& other) const {
        return b < other.b;
    }
};

struct Info {
    vector<int> order;              // order[t] = current vertex after t steps, until first repeat
    int mu, lam;                    // tail length, cycle length
    vector<u128> pref;              // pref[t] = sum of A after t steps, for t < order.size()
    vector<u64> prefMod;            // same mod MOD

    // cyclePref[j] = sum of first j steps inside one cycle traversal
    // cycle sequence is: order[mu+1], ..., order[last], order[mu]
    vector<u128> cyclePref;         // size lam+1
    vector<u64> cyclePrefMod;       // size lam+1
    u128 cycleSum;
    u64 cycleSumMod;
};

u64 sat_mul_cap(u64 q, u128 s, u64 limit) {
    if (limit == 0 || q == 0 || s == 0) return 0;
    if ((u128)q > (u128)limit / s) return limit;
    return (u64)((u128)q * s);
}

Info build_info(int start, const vector<int>& nxt, const vector<u64>& A) {
    int N = (int)nxt.size() - 1;
    vector<int> pos(N + 1, -1);

    Info info;
    int cur = start;
    while (pos[cur] == -1) {
        pos[cur] = (int)info.order.size();
        info.order.push_back(cur);
        cur = nxt[cur];
    }

    info.mu = pos[cur];
    int L = (int)info.order.size();
    info.lam = L - info.mu;

    info.pref.assign(L, 0);
    info.prefMod.assign(L, 0);

    for (int i = 1; i < L; ++i) {
        info.pref[i] = info.pref[i - 1] + (u128)A[info.order[i]];
        info.prefMod[i] = (info.prefMod[i - 1] + A[info.order[i]] % MOD) % MOD;
    }

    info.cyclePref.assign(info.lam + 1, 0);
    info.cyclePrefMod.assign(info.lam + 1, 0);

    for (int j = 1; j <= info.lam; ++j) {
        int idx = (j == info.lam ? info.mu : info.mu + j);
        int node = info.order[idx];
        info.cyclePref[j] = info.cyclePref[j - 1] + (u128)A[node];
        info.cyclePrefMod[j] = (info.cyclePrefMod[j - 1] + A[node] % MOD) % MOD;
    }

    info.cycleSum = info.cyclePref[info.lam];
    info.cycleSumMod = info.cyclePrefMod[info.lam];
    return info;
}

// 다음 임계값 D를 처음 만족하는 최소 step 수를 반환.
// 없거나 Krem 안에 못 하면 INF64.
u64 find_cross_step(const Info& info, u64 D, u64 Krem) {
    u64 upto = min<u64>(Krem, (u64)info.mu);

    for (u64 t = 1; t <= upto; ++t) {
        if (info.pref[(size_t)t] >= (u128)D) return t;
    }

    if (Krem <= (u64)info.mu) return INF64;
    if (info.cycleSum == 0) return INF64;

    u128 need = (u128)D - info.pref[info.mu]; // > 0
    u128 q = (need - 1) / info.cycleSum;      // full cycles before final partial cycle

    if (q > (u128)(Krem - (u64)info.mu) / (u128)info.lam) return INF64;

    u128 residual = need - q * info.cycleSum; // 1..cycleSum
    int rem = 1;
    while (rem <= info.lam && info.cyclePref[rem] < residual) ++rem;

    u128 t = (u128)info.mu + q * (u128)info.lam + (u128)rem;
    if (t > (u128)Krem) return INF64;
    return (u64)t;
}

struct StateRes {
    int endVertex;
    u64 addMod;
    u64 addCap; // capped by caller's limit
};

// t step 진행했을 때의 끝 정점, 증가량(mod), 증가량(cap)을 계산
StateRes state_after_steps(const Info& info, u64 t, u64 capNeed) {
    StateRes res{info.order[0], 0, 0};

    int L = (int)info.order.size();

    if (t < (u64)L) {
        res.endVertex = info.order[(size_t)t];
        res.addMod = info.prefMod[(size_t)t];
        res.addCap = (u64)min<u128>(info.pref[(size_t)t], (u128)capNeed);
        return res;
    }

    u64 r = t - (u64)info.mu;
    u64 q = r / (u64)info.lam;
    int rem = (int)(r % (u64)info.lam);

    res.endVertex = (rem == 0 ? info.order[info.mu] : info.order[info.mu + rem]);

    u128 modVal = 0;
    modVal += info.prefMod[info.mu];
    modVal += (u128)(q % MOD) * info.cycleSumMod;
    modVal += info.cyclePrefMod[rem];
    res.addMod = (u64)(modVal % MOD);

    u64 cap = (u64)min<u128>(info.pref[info.mu], (u128)capNeed);
    u64 left = capNeed - cap;

    u64 cycAdd = sat_mul_cap(q, info.cycleSum, left);
    cap += cycAdd;
    left = capNeed - cap;

    cap += (u64)min<u128>(info.cyclePref[rem], (u128)left);
    res.addCap = cap;

    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    u64 K;
    cin >> N >> M >> K;

    vector<u64> A(N + 1);
    for (int i = 1; i <= N; ++i) cin >> A[i];

    vector<Edge> edges(M);
    for (int i = 0; i < M; ++i) {
        cin >> edges[i].u >> edges[i].v >> edges[i].b;
    }
    sort(edges.begin(), edges.end());

    vector<int> nxt(N + 1);
    for (int i = 1; i <= N; ++i) nxt[i] = i; // 활성 간선 없으면 제자리

    u64 maxB = 0;
    for (auto &e : edges) maxB = max(maxB, e.b);
    u64 capLimit = maxB + 1; // 이 이상이면 모든 간선이 이미 활성화됨

    int curU = 1;
    u64 cCap = 0;   // 비교용: maxB+1에서 saturation
    u64 cMod = 0;   // 출력용 mod

    int ptr = 0;

    auto unlock = [&]() {
        while (ptr < M && edges[ptr].b <= cCap) {
            nxt[edges[ptr].u] = edges[ptr].v;
            ++ptr;
        }
    };

    unlock(); // 초기 c=0 에서 활성화되는 간선 반영

    u64 remK = K;
    while (remK > 0) {
        Info info = build_info(curU, nxt, A);

        // 더 이상 임계값이 없으면 마지막 phase
        if (ptr == M) {
            StateRes s = state_after_steps(info, remK, capLimit - cCap);
            curU = s.endVertex;
            cMod = (cMod + s.addMod) % MOD;
            remK = 0;
            break;
        }

        u64 nextB = edges[ptr].b;   // 다음 임계값
        u64 D = nextB - cCap;       // 이만큼 이상 증가하면 다음 phase로 넘어감

        u64 cross = find_cross_step(info, D, remK);
        u64 go = (cross == INF64 ? remK : cross);

        StateRes s = state_after_steps(info, go, capLimit - cCap);
        curU = s.endVertex;
        cMod = (cMod + s.addMod) % MOD;
        cCap += s.addCap;
        remK -= go;

        unlock();
    }

    cout << curU << ' ' << cMod % MOD << '\n';
    return 0;
}