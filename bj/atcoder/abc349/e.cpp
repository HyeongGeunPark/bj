#include<iostream>
#include<vector>

/*
gameboard index
0 1 2
3 4 5
6 7 8
*/
std::vector<std::vector<int>> lines{
	{0, 1, 2},
	{3, 4, 5},
	{6, 7 ,8},
	{0, 3, 6},
	{1, 4, 7},
	{2, 5, 8},
	{0, 4, 8},
	{2, 4 ,6}
};
using ll = long long;
constexpr ll INF = ((ll)1 << 60);
std::vector<int> scores(9);
bool game(int turn, ll s1, ll s2, std::vector<int>& state) {
	// check if game ends
	for (const auto& line : lines) {
		int& color = state[line[0]];
		if (color == 0) continue;
		if (state[line[0]] && state[line[0]] == state[line[1]]
			&& state[line[1]] == state[line[2]])
		{
			return color == 1 ? true : false;
		}
	} 

	// all tiles are painted, thus game ended
	if (turn == 9) {
		return s1 > s2;
	} 
	if (turn % 2 == 0) {
		// Takahashi turn
		for (int i = 0; i < 9; ++i) {
			if (state[i] != 0) continue;
			state[i] = 1; 
			if (game(turn + 1, s1 + scores[i], s2, state) == true) {
				state[i] = 0;
				return true;
			}
			state[i] = 0;
		}
		return false;
	}
	else {
		// Aoki turn
		for (int i = 0; i < 9; ++i) {
			if (state[i] != 0) continue;
			state[i] = 2;
			if (game(turn + 1, s1, s2 + scores[i], state) == false) {
				state[i] = 0;
				return false;
			}
			state[i] = 0;
		}
		return true;
	} 
}

int main(void) {

	for (int i = 0; i < 9; ++i) {
		std::cin >> scores[i];
	}

	std::vector<int> gamestate(9, 0);

	bool game_result = game(0, 0, 0, gamestate);

	if (game_result)
		std::cout << "Takahashi";
	else
		std::cout << "Aoki"; 
}