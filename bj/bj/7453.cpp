/*
bj 7453 합이 0인 네 정수

1. 쉬운 방법
a+b, c+d를 저장한 n*n 크기 배열을 만든다.
c+d 배열만 정렬한다.
a+b 배열에서 원소 하나를 골라 x라고 할 때,
c+d 배열에서 -x의 갯수를 찾는다(upper_bound, lower_bound) 이용.
n*nlog(n*n).

2. 조금 개선된 방법
a+b배열, c+d배열 모두 정렬한다.
포인터 p가 a+b배열의 가장 작은 원소를 가리키게 한다.
포인터 q가 c+d배열의 가장 큰 원소를 가리키게 한다.
합이 0보다 크면 q를 왼쪽으로 옮긴다.
합이 0보다 작으면 p를 오른쪽으로 옮긴다.
합이 0이면 결과에 포함한다.  
O(N)은 위와 동일하다.

3. 더 개선된 방법.
두 수를 더해서 0이 된다는 것은 다음을 의미한다.
- 두 수 모두 0이거나, 한 수는 양수, 한 수는 음수이다.
- 두 수의 절대값은 같다.
	-> 따라서 두 수를 어떤 수로 나눈 나머지는 항상 같다.
이를 이용해 radix를 이용해 전체 배열을 나눌 수 있고,
탐색 역시 radix가 일치하는 두 배열 사이에서만 진행하면 된다.
radix만큼 수가 작아지므로, 카운팅 정렬도 가능하다.
O(N)=N^2
*/

#include<iostream>
#include<vector>
#include<algorithm>

constexpr int mypow(int base, int power) {
	int result = 1;
	while (power--) {
		result *= base;
	}
	return result;
}

constexpr int rn = 8;
constexpr int r = mypow(2, rn)-1; 
constexpr int len = mypow(2, 28 - rn) + 1;
int main(void) {
	std::cin.tie(0);
	std::ios_base::sync_with_stdio(0);
	int n;
	std::cin >> n;
	std::vector<int> arr1[r+1];
	std::vector<int> arr2[r+1];
	std::vector<int> arr3[r+1];
	std::vector<int> arr4[r+1];
	std::vector<int> a, b, c, d;
	a.resize(n);
	b.resize(n);
	c.resize(n);
	d.resize(n);

	for (int i = 0; i < n; ++i) {
		std::cin >> a[i] >> b[i] >> c[i] >> d[i];
	}
	for (auto aa : a) {
		for (auto bb : b) {
			int ab = aa + bb;
			if (ab >= 0)
				arr1[ab & r].push_back(ab>>rn);
			else {
				ab = -ab;
				arr3[ab & r].push_back(ab>>rn);
			}
		}
	}
	for(auto cc:c){
		for (auto dd : d) {
			int cd = cc + dd;
			if (cd > 0)
				arr2[cd & r].push_back(cd>>rn);
			else { 
				cd = -cd;
				arr4[cd & r].push_back(cd>>rn);
			} 
		}
	}
	// search 1-4, 2-3
	long long result = 0;
	std::vector<int> count(len, 0);
	std::vector<int> exists(len, 0);
	int excount = 0;
	for (int i = 0; i < r + 1; ++i) {
		excount++;
		for (int x : arr1[i]) {
			if (exists[x] < excount) {
				exists[x] = excount;
				count[x] = 1;
			}
			else {
				++count[x];
			}
		}
		for (int x : arr4[i]) {
			if (exists[x] == excount)
				result += count[x];
		}
		excount++;
		for (int x : arr2[i]) {
			if (exists[x] < excount) {
				exists[x] = excount;
				count[x] = 1;
			}
			else {
				++count[x];
			}
		}
		for (int x : arr3[i]) {
			if (exists[x] == excount)
				result += count[x];
		} 
	}

	/*
	std::vector<int> a(n), b(n), c(n), d(n);
	for (int i = 0; i < n; ++i) {
		std::cin >> a[i] >> b[i] >> c[i] >> d[i];
	}
	std::vector<int> ab, cd;
	ab.reserve(n * n);
	cd.reserve(n * n);

	for (auto aa : a) {
		for (auto bb : b) {
			ab.push_back(aa + bb);
		}
	}
	for (auto cc : c) {
		for (auto dd : d) {
			cd.push_back(cc + dd);
		}
	}

	std::sort(ab.begin(), ab.end());
	std::sort(cd.begin(), cd.end());
	*/
	/*
	long long result = 0;
	for (auto x : ab) {
		auto il = std::lower_bound(cd.begin(), cd.end(), -x);
		auto ir = std::upper_bound(cd.begin(), cd.end(), -x);
		result += ir - il;
	}
	*/
	/*
	long long result = 0;
	auto p = ab.begin();
	auto q = cd.rbegin();
	long long pnum, qnum;
	while (p!=ab.end() && q!=cd.rend()) {
		int x = *p;
		pnum = 0;
		while (p!=ab.end() && x==*p) {
			++pnum;
			++p;
		}
		qnum = 0;
		while (q!=cd.rend() && *q>-x) {
			++q;
		}
		while (q!=cd.rend() && *q==-x) {
			++qnum;
			++q;
		}
		result += pnum * qnum;
	}
	*/

	std::cout << result;
}