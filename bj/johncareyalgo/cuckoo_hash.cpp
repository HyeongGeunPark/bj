#include<iostream>
#include<vector>

/*
cuckoo hashing
해시 테이블 2개와 해싱 함수 2개를 이용한다.
1. 삽입
해시테이블 1에 해시함수 1을 이용해 넣는다.
그 자리가 차있으면 그 자리에 있는 것을 해시테이블 2에 해시함수 2를 이용해 넣는다.
만일 그 자리도 차 있으면 그 자리에 있던 것을 다시 해시테이블 1에 넣는다.
빈 자리가 나올때까지 재귀적으로 반복.

2. 룩업/삭제
해시테이블 1 혹은 2에 존재한다. 두 자리만 찾아보면 된다.

주의
1. 부하율이 0.5 이하로 유지되도록 하여야 성능을 보장할 수 있다.
2. 순환이 발생하면 재해싱을 해야 한다.
*/

class hash_map
{
	std::vector<int> data1;
	std::vector<int> data2;
	int size; 

	int hash1(int key) const
	{
		return key % size;
	}

	int hash2(int key) const
	{
		return (key / size) % size;
	}

public:
	hash_map(int n) : size(n)
	{
		data1 = std::vector<int>(size, -1);
		data2 = std::vector<int>(size, -1);
	}

	std::vector<int>::iterator lookup(int key)
	{
		auto hash_value1 = hash1(key);
		if (data1[hash_value1] == key)
		{
			std::cout << "1번 테이블에서 " << key << " 발견" << '\n';
			return data1.begin() + hash_value1;
		}

		auto hash_value2 = hash2(key);
		if (data2[hash_value2] == key)
		{
			std::cout << "2번 테이블에서 " << key << " 발견" << '\n';
			return data2.begin() + hash_value2;
		}

		return data2.end();  // 못찾음
	}

	void erase(int key)
	{
		auto position = lookup(key);
		if (position != data2.end())
		{
			*position = -1;
			std::cout << key << "에 해당하는 원소 삭제함" << '\n';
		}
		else
		{
			std::cout << key << "키를 찾지 못함" << '\n';
		}
	}

	void insert(int key)
	{
		insert_impl(key, 0, 1);
	}

	void insert_impl(int key, int cnt, int table)
	{
		if (cnt >= size)
		{
			std::cout << key << " 삽입 시 순환 발생! 재해싱 필요." << '\n';
			return;
		}

		auto datap = &data1;
		auto hashf = &hash_map::hash1;
		int other_table = 2;
		if (table == 2) {
			datap = &data2;
			hashf = &hash_map::hash2; 
			other_table = 1;
		}

		int hash = (this->*hashf)(key);
		auto& data = *datap;
		
		if (data[hash] == -1)
		{
			std::cout << table << "번 테이블에 " << key << " 삽입" << '\n';
			data[hash] = key;
		}
		else
		{
			int old = data[hash];
			data[hash] = key;
			std::cout << table << "번 테이블에 " << key << " 삽입: 기존의 " << old
				<< " 이동 ->";
			insert_impl(old, cnt + 1, other_table);
		}
	}

	void print()
	{
		std::cout << "Index: ";
		for (int i = 0; i < size; ++i)
			std::cout << i << '\t';
		std::cout << std::endl;

		std::cout << "Data1: ";
		for(auto i: data1)
			std::cout << i << '\t';
		std::cout << std::endl;

		std::cout << "Data2: ";
		for(auto i: data2)
			std::cout << i << '\t';
		std::cout << std::endl; 
	}

};

int main(void) {

	hash_map map(7);
	map.print();

	std::cout << std::endl;

	map.insert(10);
	map.insert(20);
	map.insert(30);
	std::cout << std::endl; 

	map.insert(104);
	map.insert(2);
	map.insert(70);
	map.insert(9);
	map.insert(90);
	map.insert(2);
	map.insert(7);
	std::cout << std::endl;

	map.print();
	std::cout << std::endl;

	map.insert(2); //순환 발생!

}