#include<cstdio>
#include<vector>
using namespace std;

int t, n, m, w, s, e, c;
vector<pair<int, int>> adj[501];

bool bellmanford(int src) {
	vector<int> dist(n + 1, 1e9);
	bool update;
	dist[src] = 0;
	for (int k = 1; k <= n; ++k) {
		update = 0;
		for (int here = 1; here <= n; ++here) {
			for (auto there : adj[here]) {
				if (dist[there.first] > dist[here] + there.second) {
					if (there.first == src) return 1;
					dist[there.first] = dist[here] + there.second;
					update = 1;
				}
			}
		}
		if (!update) return 0;
	}
	return update;
}
int main() {
	scanf("%d", &t);
	while (t--) {
		scanf("%d%d%d", &n, &m, &w);
		for (int i = 1; i <= n; ++i)
			adj[i].clear();
		while (m--) {
			scanf("%d%d%d", &s, &e, &c);
			adj[s].push_back({ e, c });
			adj[e].push_back({ s, c });
		}
		while (w--) {
			scanf("%d%d%d", &s, &e, &c);
			adj[s].push_back({ e, -c });
		}
		if (bellmanford(1)) puts("YES");
		else puts("NO");
	}
}