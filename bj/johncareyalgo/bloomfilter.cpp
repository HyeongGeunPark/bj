/*
블룸 필터

내부 자료구조
1. 다수의 해시 함수(최소 3개)
2. 충분히 큰 bool 배열

입력
1. 입력에 대해 모든 해시 함수를 이용하여 해시값을 구한다.
2. 해당하는 해시값의 인덱스의 bool 값을 true로 한다.

룩업
1. 입력에 대해 모든 해시값을 구한다.
2. 해당 해시값의 인덱스의 bool 값이 모두 true일 경우에만 true를 리턴한다.

* 따라서 false positive(없는데 있다고 하는 것)의 가능성이 있다.

*/

#include<iostream>
#include<vector>

class bloom_filter
{
	std::vector<bool> data;
	int nBits;

	int hash(int num, int key) const
	{
		switch (num)
		{
		case 0: return key % nBits;
		case 1: return (key / 7) % nBits;
		case 2: return (key / 11) % nBits;
		}
		return 0;
	}

public:
	bloom_filter(int n) : nBits(n)
	{
		data = std::vector<bool>(nBits, false);
	}

	bool lookup(int key) const
	{
		bool result = true;
		for (int i = 0; i < 3; ++i) {
			result &= data[hash(i, key)];
		}

		if (result) {
			std::cout << key << ": 있을 수 있음\n";
		}
		else {
			std::cout << key << ": 절대 없음\n";
		}
		return result;
	}

	void insert(int key)
	{
		for (int i = 0; i < 3; ++i) {
			data[hash(i, key)] = true;
		}
		std::cout << key << "를 삽입\n";

		test_print(); 
	}

	void test_print() {
		for (auto a : data)
			std::cout << a << ' ';
		std::cout << std::endl; 
	}

};

int main()
{
	bloom_filter bf(7);
	bf.insert(100);
	bf.insert(54);
	bf.insert(82);

	bf.lookup(5);
	bf.lookup(50);
	bf.lookup(20);
	bf.lookup(54);

}

