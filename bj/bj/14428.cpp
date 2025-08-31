/*
bj14428 수열과 쿼리16

주어진 구간에서
가장 작은 값의 인덱스(같은 값인 경우 인덱스가 작은 값)을 구하는 쿼리.
(원소 변경 있음)

접근법: 간단한 세그먼트 트리(값 변경 있음)
최소값의 인덱스를 유지하는 세그먼트 트리를 구축하여 풀이.

주의.
1. 입력의 양이 매우 많은 것을 감안하고, 입출력 시간을 줄일 방법을 적용.
*/

#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <string>

class SegmentTree
{
public:
	struct Data {
		int value = std::numeric_limits<int>::max();
		int index = -1;
		friend bool operator<(const Data& a, const Data& b)
		{
			if (a.value == b.value)
				return a.index < b.index;
			else
				return a.value < b.value;
		}
	};
	explicit SegmentTree(int n, std::istream& is)
		: height{ (int)std::ceil(std::log2(n)) }
		, base{1 << height}, data(base * 2)
	{
		get_n(n, is);
		init();
	}

	int query(int l, int r) {
		return _query(l, r, 0, base, 1).index;
	}

	void update(int idx, int newValue) {
		idx += base;
		data[idx].value = newValue;
		idx /= 2;

		while (idx) {
			data[idx] = std::min(data[idx * 2], data[idx * 2 + 1]);
			idx /= 2;
		}
	}

private:
	int height;
	int base;
	std::vector<Data> data;

	Data _query(int l, int r, int s, int e, int idx) {
		if (l <= s && e <= r) {
			return data[idx];
		}
		else if (e <= l || r <= s) {
			return Data{};
		}
		else {
			int mid = (s + e) / 2;
			return std::min(
				_query(l, r, s, mid, idx * 2)
				, _query(l, r, mid, e, idx * 2 + 1));
		}
	}

	void get_n(int n, std::istream& is)
	{
		// 0-based index, half-close range
		int i = 0;
		while (i < n) {
			is >> data[base + i].value;
			data[base + i].index = i;
			++i;
		}
	}

	void init()
	{
		for (int i = base - 1; i > 0; --i)
		{
			data[i] = std::min(data[i * 2], data[i * 2 + 1]);
		}
	}



};

struct Query {
	int command;
	int arg1;
	int arg2;
};


int main() {
	std::cin.tie(0);
	std::ios_base::sync_with_stdio(0);

	int n;
	std::cin >> n;
	SegmentTree st{ n, std::cin };

	// first, get all query commands
	int m;
	int outCount = 0;
	std::cin >> m;
	std::vector<Query> q(m);
	for (int i = 0;i < m;++i) {
		std::cin >> q[i].command >> q[i].arg1 >> q[i].arg2;
		if (q[i].command == 2)
			++outCount;
	}

	// execute query commands
	std::string result;
	for (auto [command, arg1, arg2] : q)
	{
		switch (command)
		{
		case 1:
			st.update(arg1 - 1, arg2);
			break;

		case 2:
			result += std::to_string(st.query(arg1 - 1, arg2) + 1);
			result += '\n';
			break;

		default:
			break;
		}
	}

	// print result
	std::cout << result;

	return 0;
}