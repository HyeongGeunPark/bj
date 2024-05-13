/*
linear selection algorithm

in <algorithm>

template<class RandomIt>
std::nth_element(RandomIt first, RandomIt nth, Randomit last)

template<class RandomIt, class Compare>
std::nth_element(RandomIt first, RandomIt nth, Randomit last, Compare comp)

nth가 가리키는 원소가 range [first, last)를 완전히 정렬 한 후 그 위치에 있을 원소가 된다. O(n).
partial 정렬된다.

*/
#include<iostream>
#include<vector>
#include<algorithm>

template<typename RandomIt>
RandomIt find_median(RandomIt begin, RandomIt end)
{
	std::sort(begin, end);
	return begin + (std::distance(begin, end) / 2);
}

template<typename RandomIt>
RandomIt partition_using_given_pivot(RandomIt begin, RandomIt end, RandomIt pivot)
{
	auto left_iter = begin;
	auto right_iter = end - 1;

	while (true)
	{
		while (left_iter != right_iter && *left_iter < *pivot)
			++left_iter;
		while (left_iter != right_iter && *right_iter >= *pivot)
			--right_iter;
		if (left_iter == right_iter) break;
		else
			std::iter_swap(left_iter, right_iter);
	}

	if (*pivot > *right_iter)
		std::iter_swap(pivot, right_iter);

	return right_iter;
}

template<typename RandomIt>
RandomIt linear_time_select(RandomIt begin, RandomIt end, size_t i)
{
	auto size = std::distance(begin, end);
	if (size > 0 && i < size) {
		auto num_Vi = (size+4) / 5;
		size_t j = 0;

		std::vector<typename RandomIt::value_type> M;
		for (; j < size / 5; ++j)
		{
			auto b = begin + (j * 5);
			auto e = begin + (j * 5) + 5;
			M.push_back(*find_median(b, e));
		}

		if (j * 5 < size)
		{
			auto b = begin + (j * 5);
			auto e = end;
			M.push_back(*find_median(b, e));
		}

		auto median_of_medians = (M.size() == 1) ? M.begin() : linear_time_select(M.begin(), M.end(), M.size() / 2);

		auto partition_iter = partition_using_given_pivot(begin, end, median_of_medians);
		auto k = std::distance(begin, partition_iter);
		if (i == k)
			return partition_iter;
		else if (i < k)
			return linear_time_select(begin, partition_iter, i);
		else if (i > k)
			return linear_time_select(partition_iter+1, end, i - k - 1);
	}
	else
	{
		return begin;
	}

}
std::vector<int> arr{ 1,6,2,3,5,9,7,8,10 ,4};

int main(void) {
	std::cout << *linear_time_select(arr.begin(), arr.end(), 10);
}