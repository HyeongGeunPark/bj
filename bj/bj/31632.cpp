/*

bj31632 가지 오이 당근

복잡한 분기에 주의.

*/

#include<iostream>
#include<string>
#include<vector>

struct wl_state {
	char w, l, d;
};
struct god_state {
	char g, o, d;
};

int main(void) {
	std::cin.tie(0);
	std::ios_base::sync_with_stdio(0);

	std::vector<char> wl(200000);
	std::vector<char> god(200000);

	std::cin >> std::skipws;

	int t, n;
	std::cin >> t;
	while (t--) {
		std::cin >> n;
		wl_state wls{ 0,0,0 };
		god_state gods{ 0,0,0 };

		for (int i = 0; i < n; ++i) {
			std::cin >> god[i];
			switch (god[i]) {
			case 'G':
				gods.g = 1;
				break;
			case 'O':
				gods.o = 1;
				break;
			case 'D':
				gods.d = 1;
				break;
			default:
				break; 
			}
		}
		for (int i = 0; i < n; ++i) {
			std::cin >> wl[i];
			switch (wl[i]) {
			case 'W':
				wls.w = 1;
				break;
			case 'D':
				wls.d = 1;
				break;
			case 'L':
				wls.l = 1;
				break;
			}
		}

		// evaluate the game
		if (wls.d && !wls.w && !wls.l) {
			// draw case, all symbols should be present
			// or all symbols should be same
			// all same case
			if (gods.d + gods.g + gods.o <= 1) {
				char draw_symbol;
				if (gods.d) draw_symbol = 'D';
				else if (gods.g) draw_symbol = 'G';
				else if (gods.o) draw_symbol = 'O';
				else draw_symbol = 'G';
				for (int i = 0; i < n; ++i) {
					if (god[i] == '?') god[i] = draw_symbol;
				} 
			}
			else {
				// all present case
				for (int i = 0; i < n; ++i) {
					if (god[i] == '?') {
						if (!gods.d) {
							god[i] = 'D';
							gods.d = 1;
						}
						else if (!gods.g) {
							god[i] = 'G';
							gods.g = 1;
						}
						else if (!gods.o){
							god[i] = 'O';
							gods.o = 1;
						}
						else {
							god[i] = 'D';
						}
					}
				}
				if (!(gods.g && gods.o && gods.d)) {
					// invalid
					goto print_no;
				} 
			}
		}
		else if(!wls.d && wls.w && wls.l){
			// win-lose case
			if (gods.d + gods.g + gods.o == 3) goto print_no;
			// find which symbol is win or lose
			char win_symbol = 0, lose_symbol = 0;
			for (int i = 0; i < n; ++i) {
				if (!win_symbol && wl[i] == 'W' && god[i]!='?') {
					win_symbol = god[i];
				}
				if (!lose_symbol && wl[i] == 'L' && god[i]!='?') {
					lose_symbol = god[i];
				}
			}

			// invalid win-lose
			if ((win_symbol == 'G' && lose_symbol == 'D')
				|| (win_symbol == 'D' && lose_symbol == 'O')

				|| (win_symbol == 'O' && lose_symbol == 'G'))
				goto print_no;

			// guess win-lose symbol
			if (!win_symbol && !lose_symbol) {
				win_symbol = 'G';
				lose_symbol = 'O';
			}
			if (!win_symbol) {
				switch (lose_symbol) {
				case 'G':
					win_symbol = 'D';
					break;
				case 'D':
					win_symbol = 'O';
					break;
				case 'O':
					win_symbol = 'G';
					break;
				}
			}
			if (!lose_symbol) {
				switch (win_symbol) {
				case 'G':
					lose_symbol = 'O';
					break;
				case 'D':
					lose_symbol = 'G';
					break;
				case 'O':
					lose_symbol = 'D';
					break;
				}
			}

			for (int i = 0; i < n; ++i) {
				if (god[i] == '?') {
					if (wl[i] == 'W') god[i] = win_symbol;
					else if (wl[i] == 'L') god[i] = lose_symbol;
				} 
				else {
					if (god[i] == win_symbol) {
						if (wl[i] != 'W') goto print_no;
					}
					else if (god[i] == lose_symbol) {
						if (wl[i] != 'L') goto print_no;
					}
					else {
						goto print_no;
					} 
				}
			} 
		}
		else {
			goto print_no;
		}


		std::cout << "YES\n";
		for (int i = 0; i < n; ++i) {
			std::cout << god[i];
		}
		std::cout << '\n'; 
		continue; 

	print_no:
		std::cout << "NO\n"; 
	}

}