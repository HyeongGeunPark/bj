#pragma once

#include<cstring>
#include<algorithm>

/*
disjoint set�� ������ �ϴ� ���
1. ��� ����:
	find_root �۾����� ������ ��� ����� ���� root�� �缳��
2. ���Ͽ� ���� ��ũ:
	��ũ�� ū root�� ��ũ�� ���� root�� ���δ�.
	��ũ�� ������ ���� ���� �����ϴ�.
	1. size: Ʈ���� ���� ���� ����
	2. height: Ʈ���� ���� 
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

