/*
세그먼트 트리 구현 예시
trivial segment tree
node with constant size

implicit representation
*/

#include<vector>
#include<iostream>
#include<algorithm>
#include<limits>
#include<random>
#include<fstream>
#include<array>



class segmentTree {
public:
	segmentTree(std::vector<int>& arr)
		: sz{ arr.size() }, nodes(arr.size() * 4)
	{
		int s = 0;
		int e = arr.size();
		init(s, e, 0, arr);
	}

	int query(int s, int e) const {
		// error case
		if (e > sz || s < 0 || s >= e) return 0;

		return query_internal(s, e, 0, 0, sz);
	}

private:
	std::vector<int> nodes; 
	const size_t sz;
	void init(int s, int e, int index, std::vector<int>& arr) {
		// base case, e == s+1
		if (e == s + 1) {
			nodes[index] = arr[s];
		}
		else {
			// other cases
			int mid = (s + e) / 2;
			init(s, mid, index * 2 + 1, arr);
			init(mid, e, index * 2 + 2, arr);
			nodes[index] = combine(nodes[index * 2 + 1], nodes[index * 2 + 2]);
		}
	}
	int combine(int a, int b) const {
		// this method defines the characteristic of this
		// segment tree

		// max value combine
		return std::max(a, b); 
	}
	int default_value() const {
		// default return value for query on empty array
		return std::numeric_limits<int>::min();
	}
	int query_internal(int s, int e, int i, int l, int r) const {
		if (r <= s || e <= l) {
			return default_value();
		}
		if (s <= l && r <= e) {
			return nodes[i];
		}
		int mid = (l + r) / 2;
		int lresult = query_internal(s, e, i * 2 + 1, l, mid);
		int rresult = query_internal(s, e, i * 2 + 2, mid, r);
		return combine(lresult, rresult);
	}
};

// test code

int get_max(int l_index, int r_index, std::vector<int>& arr) {
	int result = std::numeric_limits<int>::min();
	for (int i = l_index; i < r_index; ++i) {
		result = std::max(result, arr[i]);
	}
	return result;
}

#define RANDOM_TEST
#undef RANDOM_TEST
#ifdef RANDOM_TEST
#define RANDOM_TEST_ARRAY_SIZE 10000
#define RANDOM_TEST_QUERY_NUMBER 10000
#define RANDOM_TEST_ARRAY_MIN 0
#define RANDOM_TEST_ARRAY_MAX 10000000
#endif


int main() {
	int testArraySize;
	std::vector<int> testArray;
#ifdef RANDOM_TEST
	testArraySize = RANDOM_TEST_ARRAY_SIZE;
	std::random_device rd;
	std::default_random_engine rng(rd());
	std::uniform_int_distribution<int>
		uniformIntDist{ RANDOM_TEST_ARRAY_MIN, RANDOM_TEST_ARRAY_MAX };

	for (int i = 0; i < testArraySize; ++i) {
		testArray.push_back(uniformIntDist(rng));
	}
#else
	std::ifstream ifs("src/testcase.txt");
	ifs >> testArraySize;
	for (int i = 0; i < testArraySize; ++i) {
		int temp;
		ifs >> temp;
		testArray.push_back(temp);
	}
#endif

	std::cout << "Test Array\n";
	int c = 0;
	for (int i = 0; i < testArraySize; ++i) { 
		++c;
		std::cout << testArray[i] << ' ';
		if (c == 10) {
			std::cout << '\n';
			c = 0;
		}
	}
	std::cout << '\n';

	segmentTree segTree{ testArray };

	// test comparison
	int testNumber;
	std::vector<std::array<int, 4>> failedCases;
#ifdef RANDOM_TEST
	testNumber = RANDOM_TEST_QUERY_NUMBER;
#else
	ifs >> testNumber; 
#endif
	for (int i = 0; i < testNumber; ++i) {
#ifdef RANDOM_TEST
		std::uniform_int_distribution indexDist{ 0, RANDOM_TEST_ARRAY_SIZE };
		int s = indexDist(rng);
		int e;
		do {
			e = indexDist(rng);
		} while (s == e);
		if (s > e)
			std::swap(s, e);
#else
		int s;
		int e;
		ifs >> s >> e;
#endif
		int segmentTreeResult = segTree.query(s, e);
		int linearSearchResult = get_max(s, e, testArray);
		std::cout << "Test "
			<<(segmentTreeResult == linearSearchResult?"Success":"Fail")
			<<" : s == " << s << ", e == " << e << "\n";
		if (segmentTreeResult != linearSearchResult) {
			failedCases.push_back({ s,e,segmentTreeResult,linearSearchResult });
		}
	}


	// failed case repeated output
	std::cout << failedCases.size() << " failed cases\n";
	for (int i = 0; i < failedCases.size(); ++i) {
		auto& data = failedCases[i];
		std::cout << "Case " << i + 1 << " : "
			<< "query in [" << data[0] << ", " << data[1] << ") : "
			<< "segTree : " << data[2] << " , " << "Linear : " << data[3] << '\n';
	}

	return 0;
}