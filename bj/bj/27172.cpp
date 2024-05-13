#include<iostream>

constexpr int card_max = 1'000'000;
constexpr int player_max = 100'000;

int cards[player_max];
int score[card_max+1];
int exists[card_max+1];

int main() {

	std::cin.tie(0);
	std::ios_base::sync_with_stdio(0);

	int n;
	int m = 0;

	std::cin >> n;
	for (int i = 0; i < n; ++i) {
		std::cin >> cards[i];
		exists[cards[i]] = 1;
		m = std::max(m, cards[i]);
	}
 
    for(int i=1;i<=m;++i){
        if(!exists[i]) continue;
        for(int j = i*2; j<=m; j+=i){
            if(exists[j]){
                --score[j];
                ++score[i];
            }
        }
    }

	for (int i = 0; i < n; ++i) {
		std::cout << score[cards[i]] << ' ';
	}
	//std::cout << score[cards[n-1]] << '\n';

}