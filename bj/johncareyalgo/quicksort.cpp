#include<iostream>
#include<vector>
#include<algorithm>

template<typename RandomIt>
void print_vector(RandomIt a, RandomIt b) {
	for (; a!=b; ++a)
		std::cout << *a << ' ';
	std::cout << std::endl;
}

template<typename RandomIt>
auto partition( RandomIt begin,
	 RandomIt end)
{
	auto pivot_val = *begin;
	auto left_iter = begin + 1;
	auto right_iter = end;


	while (true) {
		while (*left_iter <= pivot_val && std::distance(left_iter, right_iter) > 0)
			++left_iter;
		while (*right_iter > pivot_val && std::distance(left_iter, right_iter) > 0)
			--right_iter;
		if (left_iter == right_iter) break;
		else
			std::iter_swap(left_iter, right_iter);
	}

	if (pivot_val > *right_iter)
		std::iter_swap(begin, right_iter);
	print_vector(begin, end + 1);
	return right_iter; 
}


template<typename RandomIt>
void quick_sort( RandomIt begin,
	RandomIt last, std::ptrdiff_t rank)
{
	if (std::distance(begin, last) >= 1)
	{
		auto partition_iter = partition(begin, last);
		auto pivot_rank = std::distance(begin, partition_iter);
		quick_sort(begin, partition_iter - 1, rank); 
		if(pivot_rank < rank) // partial sort
			quick_sort(partition_iter, last, rank - pivot_rank);
	}
}


int main(void) {

	std::vector<int> aa;
	int n;
	std::cin >> n;
	for (int i = 0; i < n; ++i) {
		int temp;
		std::cin >> temp;
		aa.push_back(temp);
	}
	quick_sort(aa.begin(), aa.end()-1, 3);

	//print_vector(aa);

}