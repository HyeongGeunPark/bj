#include<iostream>
#include<vector>

/*
cuckoo hashing
�ؽ� ���̺� 2���� �ؽ� �Լ� 2���� �̿��Ѵ�.
1. ����
�ؽ����̺� 1�� �ؽ��Լ� 1�� �̿��� �ִ´�.
�� �ڸ��� �������� �� �ڸ��� �ִ� ���� �ؽ����̺� 2�� �ؽ��Լ� 2�� �̿��� �ִ´�.
���� �� �ڸ��� �� ������ �� �ڸ��� �ִ� ���� �ٽ� �ؽ����̺� 1�� �ִ´�.
�� �ڸ��� ���ö����� ��������� �ݺ�.

2. ���/����
�ؽ����̺� 1 Ȥ�� 2�� �����Ѵ�. �� �ڸ��� ã�ƺ��� �ȴ�.

����
1. �������� 0.5 ���Ϸ� �����ǵ��� �Ͽ��� ������ ������ �� �ִ�.
2. ��ȯ�� �߻��ϸ� ���ؽ��� �ؾ� �Ѵ�.
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
			std::cout << "1�� ���̺��� " << key << " �߰�" << '\n';
			return data1.begin() + hash_value1;
		}

		auto hash_value2 = hash2(key);
		if (data2[hash_value2] == key)
		{
			std::cout << "2�� ���̺��� " << key << " �߰�" << '\n';
			return data2.begin() + hash_value2;
		}

		return data2.end();  // ��ã��
	}

	void erase(int key)
	{
		auto position = lookup(key);
		if (position != data2.end())
		{
			*position = -1;
			std::cout << key << "�� �ش��ϴ� ���� ������" << '\n';
		}
		else
		{
			std::cout << key << "Ű�� ã�� ����" << '\n';
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
			std::cout << key << " ���� �� ��ȯ �߻�! ���ؽ� �ʿ�." << '\n';
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
			std::cout << table << "�� ���̺� " << key << " ����" << '\n';
			data[hash] = key;
		}
		else
		{
			int old = data[hash];
			data[hash] = key;
			std::cout << table << "�� ���̺� " << key << " ����: ������ " << old
				<< " �̵� ->";
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

	map.insert(2); //��ȯ �߻�!

}