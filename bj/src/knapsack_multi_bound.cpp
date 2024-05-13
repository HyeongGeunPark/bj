/*

�� ���� ������ �ִ� ���� ����.

���ѵ� â�� �뷮�� ���� ������ �ִ� ������ �����ϴ� ����.

�� ��ǰ�� �����Ѵٸ� ��ü ������ �����ؾ� �Ѵ�.

*/

#include<iostream>
#include<vector>
#include<exception> 

struct good {
	int quantity, cost, value;
};

class mat3d {
public:
	mat3d(int dimx, int dimy, int dimz) : sizex(dimx), sizey(dimy), sizez(dimz)
	{
		data = new int[sizex * sizey * sizez](); 
	}
	~mat3d() {
		delete[] data;
	}
	int& operator()(int x, int y, int z) {
		// access without boundary check
		return data[x * (sizey * sizez) + y * (sizez)+z];
	}
	int& at(int x, int y, int z) {
		// access with boundary check
		if (x >= sizez || y >= sizey || z >= sizez
			|| x<0 || y<0 || z<0) {
			throw std::out_of_range("mat3d out of range error");
		}
		return (*this)(x, y, z);
	}
private:
	int* data;
	int sizex, sizey, sizez;
};

int knapsack_2bound(std::vector<good>& goods, int budget, int capacity)
{
	mat3d DP(2, budget + 1, capacity + 1);
	
	DP(0, goods[0].cost, goods[0].quantity) = goods[0].value;
	int result = 0;

	for (int i = 1; i < goods.size(); ++i) {
		int cur = i % 2;
		int prev = (i + 1) % 2;

		for (int j = 0; j <= budget; ++j) {
			for (int k = 0; k <= capacity; ++k) {
				try {
					DP(cur, j, k) = std::max(
						DP.at(prev, j - goods[i].cost, k - goods[i].quantity) + goods[i].value,
						DP(prev, j, k)
					);
					result = std::max(result, DP(cur, j, k));
				}
				catch (std::out_of_range) {
					DP(cur, j, k) = DP(prev, j, k);
					continue;
				}
			}
		}
	} 
	return result;
}

int main(void) {

	int n, budget, capacity;

	std::cin >> n >> budget >> capacity;
	std::vector<good> goods;

	for (int i = 0; i < n; ++i) {
		int q, c, v;
		std::cin >> q >> c >> v;
		goods.push_back({ q,c,v });
	}

	std::cout<<knapsack_2bound(goods, budget, capacity); 
}