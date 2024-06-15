#include<iostream>
#include<vector>
#include<algorithm>

int main(void) {
	std::vector<std::pair<std::string, int>> participants;
	int n;
	std::cin >> n;
	int rating_sum = 0;
	for (int i = 0; i < n; ++i) {
		std::string name;
		int rating;
		std::cin >> name >> rating;
		rating_sum += rating;
		participants.push_back(std::make_pair(name, rating));
	}
	std::sort(participants.begin(), participants.end());

	rating_sum %= n;

	std::cout << participants[rating_sum].first; 
}