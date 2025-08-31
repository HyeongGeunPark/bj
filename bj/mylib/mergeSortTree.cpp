/*
merge sort tree implementation example

quote from bj30467
*/
#include<iostream>
#include<algorithm>
#include<vector>
#include<limits>

class mergeSortTree {
public:
	mergeSortTree(std::vector<int>& arr)
		: sz{ arr.size() }, node(arr.size() * 4)
	{
		init(0, sz, 0, arr);
	}

	int queryLesser(int s, int e, int val){
		return queryLesser_internal(s, e, val, 0, 0, sz);
	}
	int queryGreater(int s, int e, int val) {
		return queryGreater_internal(s, e, val, 0, 0, sz); 
	}

private:
	std::vector<std::vector<int>> node;
	const size_t sz; 

	void init(int s, int e, int index, std::vector<int>& arr) {
		if (e == s + 1) {
			// base case
			node[index].push_back(arr[s]);
		}
		else {
			int mid = s + (e - s) / 2; // == (s+e)/2
			int leftIndex = index * 2 + 1;
			int rightIndex = index * 2 + 2;
			init(s, mid, leftIndex, arr); // left subnode
			init(mid, e, rightIndex, arr); // right subnode
			// merge
			node[index].resize(node[leftIndex].size() + node[rightIndex].size());
			std::ranges::merge(node[leftIndex], node[rightIndex], node[index].begin());
		}
	}
	
	int queryLesser_internal(int s, int e, int val, int index, int l, int r){
		if (r <= s || e <= l) {
			// query in empty array
			return default_value(); 
		}
		if (s <= l && r <= e) {
			// current node is in the query range
			return countLesser(val, index);
		}
		int mid = l + (r - l) / 2;
		int result = 0;
		result += queryLesser_internal(s, e, val, index * 2 + 1, l, mid);
		result += queryLesser_internal(s, e, val, index * 2 + 2, mid, r);
		return result;
	}
	int queryGreater_internal(int s, int e, int val, int index, int l, int r) {
		if (r <= s || e <= l) {
			// query in empty array
			return default_value(); 
		}
		if (s <= l && r <= e) {
			// current node is in the query range
			return countGreater(val, index);
		}
		int mid = l + (r - l) / 2;
		int result = 0;
		result += queryGreater_internal(s, e, val, index * 2 + 1, l, mid);
		result += queryGreater_internal(s, e, val, index * 2 + 2, mid, r);
		return result;

	}
	int default_value() {
		return 0;
	}
	int countLesser(int val, int index) {
		auto& arr = node[index];
		auto iter = std::ranges::lower_bound(arr, val);
		return std::distance(arr.begin(), iter);
	}
	int countGreater(int val, int index) {
		auto& arr = node[index];
		auto iter = std::ranges::upper_bound(arr, val);
		return std::distance(iter, arr.end());
	}
};
