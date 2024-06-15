#include<iostream>
#include<vector>
#include<algorithm>
#include<limits>

struct interval {
	int l, r;
	friend std::ostream& operator<<(std::ostream& os, const interval& i) {
		os << i.l << ' ' << i.r;
		return os;
	}
};

int main(void) {
	int n;
	std::cin >> n;
	std::vector<interval> intervals(n);
	for (int i = 0; i < n; ++i) {
		std::cin >> intervals[i].l >> intervals[i].r; 
	}

	auto comp = [](const interval& a, const interval& b) {
		if (a.l == b.l) {
			return a.r < b.r;
		}
		return a.l < b.l;
		};

	std::sort(intervals.begin(), intervals.end(), comp);

	long long result = 0;
	for (auto iter = intervals.begin(); iter != intervals.end(); ++iter) {
		auto found = std::upper_bound(iter, intervals.end(),
			interval{ iter->r, std::numeric_limits<int>::max() }, comp);
		result += std::distance(iter, found-1);
	}

	std::cout << result;
}