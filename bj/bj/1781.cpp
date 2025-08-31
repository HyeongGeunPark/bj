/*
bj1781 컵라면
각 문제마다 데드라인이 있고, 문제를 풀면 컵라면을 받는다.
문제의 데드라인과 각 문제별로 받을 수 있는 컵라면의 개수가 주어진다.
받을 수 있는 컵라면의 최대 개수를 구하여라.

문제 수 1 <= n <= 200'000

접근법: 그리디
1. 라면 개수로 정렬되는 우선순위 큐를 만든다.
2. 문제(데드라인, 라면 수)를 데드라인으로 정렬한다.
3. 시간을 1씩 증가시키면서 해당 데드라인을 가진 문제를 우선순위 큐에 넣는다.
4. 우선순위 큐의 크기가 데드라인보다 큰 경우, 라면을 가장 적게 주는 문제를 차례로 버린다.
5. 문제의 순회가 끝나면 큐에 남아있는 문제들의 라면 개수를 합한다.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <queue>

struct problem {
    unsigned int deadline;
    unsigned int ramen;

    friend std::istream& operator>>(std::istream& is, problem& to) {
        is >> to.deadline >> to.ramen;
        return is;
    }
};

int main() {
	std::cin.tie(0);
	std::ios_base::sync_with_stdio(0);

	std::vector<problem> l;

    int n;
    std::cin >> n;


    l.reserve(n);
	// for loop을 돌려 임시 변수에 입력받고 emplace 하는 것과 차이는 없다.
	// (istream_iterator 내부 임시 공간에 먼저 입력된 후 vector에 복사됨)
	std::copy_n(std::istream_iterator<problem>(std::cin),
        n, std::back_inserter(l));

	std::ranges::sort(l, {}, &problem::deadline);

	// std::greater -> smallest element on top()
	std::priority_queue<unsigned int,
		std::vector<unsigned int>,
		std::greater<unsigned int>> pq;

	{
		auto it = l.begin();
		unsigned int time = 1;
		while (it != l.end())
		{
			while (it != l.end() && it->deadline <= time) {
				pq.push(it->ramen);
				++it;
			}

			while (pq.size() > time) {
				pq.pop();
			}
			// increment
			++time;
		}
	}

	int ramen_count = 0;
	while (pq.size()) {
		ramen_count += pq.top();
		pq.pop();
	}

	std::cout << ramen_count << '\n';
    return 0;
}