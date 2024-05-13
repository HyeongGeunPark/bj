/*
priority queue for djikstra's algorithm

privides decreaseKey() operation
*/

#include<set>

namespace my {

	class priority_queue
	{
	public:
		priority_queue() {}
		void add_key(int v, int weight) {
			data.insert(std::make_pair(weight, v)); 
		}
		void delete_key(int v, int weight) {
			data.erase(data.find(std::make_pair(weight, v)));
		}
		void decrease_key(int v, int weight, int new_weight) {
			delete_key(weight, v);
			add_key(new_weight, v);
		}
		std::pair<int,int> top() {
			// set은 자동으로 원소를 정렬해 저장한다. 첫 번째 원소는 가장 작은 pair이다.
			return *data.begin();
		}
		void pop_first(void) {
			data.erase(data.begin());
		}
		bool empty() {
			return data.empty();
		}

	private:
		std::set<std::pair<int, int>> data;
	};

} // namespace my end

// test
using my::priority_queue;
#include<iostream>
#include<vector>
int main(void) {

	int map[5][5] = {
		{0, 0, 0 ,2, 0},
		{0, 0, 1, 0, 9},
		{0, 1, 0, 0, 0},
		{2, 0, 0, 0, 3},
		{0, 9, 0, 3, 0}
	};

	// djikstra
	priority_queue pq;
	int s = 3;
	constexpr int inf = 10000000;
	int min_d[5] = { inf, inf, inf, inf, inf }; // 결과 저장용
	int pred[5] = { -1, -1, -1, -1, -1 }; // 경로 저장용
	min_d[s] = 0;
	pred[s] = s;
	pq.add_key(s, 0);
	while (!pq.empty()) {
		std::pair<int, int> cur = pq.top();
		int& v = cur.second;
		int& w = cur.first;
		// first = weight, second = vertex index
		pq.pop_first();
		for (int i = 0; i < 5; ++i) {
			int& len = map[v][i];
			if (len == 0) continue;
			int new_w = w + len;
			if (new_w < min_d[i]) {
				if (min_d[i] == inf) 
					pq.add_key(i, new_w);
				else 
					pq.decrease_key(i, w, new_w); 
				min_d[i] = new_w;
				pred[i] = v;
			}
		}
	}

	std::cout << "minimum distance from vertex "<<s<<"\n";
	for (int i : min_d) {
		std::cout << i << '\t';
	}
	std::cout << "\npredecessor\n";
	for (int i : pred) {
		std::cout << i << '\t';
	} 
	std::cout << "shortest path\n";
	for (int i = 0; i < 5; ++i) {
		std::vector<int> rev_path;
		if (pred[i] == -1) {
			std::cout << "path to " << i << " does not exist\n";
			continue;
		}
		int j = i;
		while (pred[j] != j) {
			rev_path.push_back(j);
			j = pred[j];
		}
		std::cout << "path to " << i << " : ";
		std::cout << s;
		for (auto iter = rev_path.rbegin(); iter != rev_path.rend(); ++iter) {
			std::cout << "->" << *iter;
		}
		std::cout << '\n';
	}
}