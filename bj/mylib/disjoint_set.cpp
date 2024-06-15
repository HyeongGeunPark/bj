#pragma once

#include<cstring>
#include<algorithm>

/*
disjoint set을 빠르게 하는 방법
1. 경로 압축:
	find_root 작업마다 지나는 모든 경로의 점의 root를 재설정
2. 유니온 바이 랭크:
	랭크가 큰 root에 랭크가 작은 root를 붙인다.
	랭크는 다음과 같이 정의 가능하다.
	1. size: 트리에 속한 점의 갯수
	2. height: 트리의 높이 
*/

class disjoint_set {
public:
	disjoint_set(int v);
	~disjoint_set();
	int find_root(int v);
	bool union_merge(int v1, int v2);

private:
	int* root;
	int* rank; 
};

disjoint_set::disjoint_set(int v) {
	/*
	root = new int[v + 1];
	rank = new int[v + 1];
	for (int i = 0; i < v + 1; ++i) {
		root[i] = i;
	}
	std::memset(rank, 0xFF, (v + 1) * sizeof(int));
	*/
	root = new int[v + 1];
	std::memset(root, 0xFF, (v + 1) * sizeof(int));
}

disjoint_set::~disjoint_set() {
	delete[] root;
	//delete[] rank;
}

int disjoint_set::find_root(int v) {
	/*
	if (v == root[v]) return v;

	// path compression
	root[v] = find_root(root[v]);
	return root[v]; 
	*/
	if (root[v] < 0) return v;
	else return find_root(root[v]);
}

bool disjoint_set::union_merge(int v1, int v2) {
	v1 = find_root(v1);
	v2 = find_root(v2);
	if (v1 == v2) return false;

	/*
	// rank by size
	if (rank[v1] > rank[v2]) {
		std::swap(v1, v2);
	}
	rank[v1] += rank[v2];
	root[v2] = v1;
	return true; 
	*/

	if (root[v1] > root[v2]) {
		std::swap(v1, v2);
	}
	root[v1] += root[v2]; root[v2] = v1;
	return true;
}

