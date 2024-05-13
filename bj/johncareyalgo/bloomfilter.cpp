/*
��� ����

���� �ڷᱸ��
1. �ټ��� �ؽ� �Լ�(�ּ� 3��)
2. ����� ū bool �迭

�Է�
1. �Է¿� ���� ��� �ؽ� �Լ��� �̿��Ͽ� �ؽð��� ���Ѵ�.
2. �ش��ϴ� �ؽð��� �ε����� bool ���� true�� �Ѵ�.

���
1. �Է¿� ���� ��� �ؽð��� ���Ѵ�.
2. �ش� �ؽð��� �ε����� bool ���� ��� true�� ��쿡�� true�� �����Ѵ�.

* ���� false positive(���µ� �ִٰ� �ϴ� ��)�� ���ɼ��� �ִ�.

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
			std::cout << key << ": ���� �� ����\n";
		}
		else {
			std::cout << key << ": ���� ����\n";
		}
		return result;
	}

	void insert(int key)
	{
		for (int i = 0; i < 3; ++i) {
			data[hash(i, key)] = true;
		}
		std::cout << key << "�� ����\n";

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

