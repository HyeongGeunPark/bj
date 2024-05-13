/*

bj20040 사이클 게임

풀이 접근법
1. disjoint set에서 게임 상황을 관리한다.
2. 플레이어가 선분 하나를 줄 때마다 두 점을 이으려고 시도한다.
	2-1. 두 점이 한 개의 root를 공유하면 사이클 완성을 감지할 수 있다.
	2-2. 그렇지 않은 경우, 두 점이 포함된 두 개의 set을 merge한다.
		그 후 게임을 계속한다.

*/

#include<iostream>
#include<cstring>

class DisjointSet {
public:
	DisjointSet(int n);	// n은 점의 갯수
	~DisjointSet(void);

	int find_root(int v);
	bool merge(int v1, int v2);

private:
	int* root; // root[i] means the root vertex of set in which i-th vertex is included
				// if root[i]<0, i-th vertex is root and -root[i] is 
				// the size of the set
};

DisjointSet::DisjointSet(int n) {
	root = new int[n];
	std::memset(root, 0xff, n * sizeof(int));
}
DisjointSet::~DisjointSet(void) {
	delete[] root;
}

int DisjointSet::find_root(int v) {
	if (root[v] < 0) return v;
	// path compression
	root[v] = find_root(root[v]);
	return root[v];
}

bool DisjointSet::merge(int v1, int v2) {
	v1 = find_root(v1);
	v2 = find_root(v2);
	if (v1 == v2) return false;
	if (root[v1] > root[v2]) std::swap(v1, v2);
	// now set v1 is bigger than set v2
	// merge set v2 to set v1
	root[v1] += root[v2];
	root[v2] = v1;
	return true;
}


int main() {
	int n, m;
	scanf("%d%d", &n, &m);
	DisjointSet djs(n);
	int i;
	for (i = 1; i <= m; ++i) {
		int v1, v2;
		scanf("%d%d", &v1, &v2);
		if (!djs.merge(v1, v2)) {
			break;
		}
	}

	if (i == (m + 1)) {
		printf("0\n"); 
	}
	else {
		printf("%d\n", i);
	} 

	return 0; 
}