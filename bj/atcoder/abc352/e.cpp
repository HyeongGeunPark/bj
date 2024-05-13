#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>

class disjointset {
public:
	disjointset(int n) : data(n + 1, 0) {}
	int find_root(int v) {
		if (data[v] == 0) {
			data[v] = -1;
		}
		if (data[v] < 0) return v;

		data[v] = find_root(data[v]);
		return data[v];
	}
	bool merge(int v1, int v2) {
		v1 = find_root(v1);
		v2 = find_root(v2);
		if (v1 == v2) return false;
		if (data[v1] > data[v2]) {
			std::swap(v1, v2);
		}
		data[v1] += data[v2];
		data[v2] = v1;
		return true;
	}
private:
	std::vector<int> data;
};
 
int main(void) {
	std::cin.tie(0);
	std::ios_base::sync_with_stdio(0);
	int n, m;

	std::cin >> n >> m;

	std::vector<std::vector<int>> s(m);
	std::vector<std::pair<int, int>> c_i_pairs;
	for (int i = 0; i < m; ++i) {
		int k, c;
		std::cin >> k >> c;
		c_i_pairs.push_back(std::make_pair(c, i));
		for (int j = 0; j < k; ++j) {
			int temp;
			std::cin >> temp;
			s[i].push_back(temp);
		}
	}

	std::sort(c_i_pairs.begin(), c_i_pairs.end());
	long long result = 0;
	long long cnt = 0;
	disjointset ds(n + 1);
	for (int i = 0; i < m; ++i) {
		int index = c_i_pairs[i].second;
		auto& vertices = s[index];
		bool flag = false;
		int s = vertices[0];
		for (int j = 1; j < vertices.size();++j) {
			int d = vertices[j];
			if (ds.merge(s, d)) {
				++cnt;
				result += c_i_pairs[i].first;
			}
			if (cnt == n - 1) {
				std::cout << result;
				return 0;
			}
		}
	}
	std::cout << -1;


}
