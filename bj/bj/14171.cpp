/*

bj14171 cities and states

N개의 도시 이름과 그 도시가 있는 주의 2글자 약자를 입력받는다.

다음과 같을 때 두 도시가 특별한 관계에 있다고 정의한다.
두 도시 A, B에 대해,
0. 두 도시는 다른 주에 있음. (주 코드가 서로 다름)
1. A의 도시 이름의 앞 두 글자가 B의 주와 같다.
2. B의 도시 이름의 앞 두 글자가 A의 주와 같다.

N (1<=N<=200'000)개의 도시에 대해 이 특별한 관계가 몇 쌍이나 있는지 계산한다.

도시 이름은 최소 2글자, 최대 10글자이다.
주 코드는 2글자이다.
동일 도시 이름이 존재할 수 있지만 모두 다른 주에 있을 것이다.

접근: 맵(unordered_map)

1. 모든 입력을 받는다.
	1-1. 단, 도시 이름 앞 2글자와 주 코드만 중요하므로, 이 4개 문자만 받는다.
2. 받은 입력을 {도시, 주}를 키로 하고, 갯수를 값으로 하는 맵에 저장한다.
3. 맵에서 모든 키를 꺼내서, 도시와 주를 바꾸어 만든 키로 검색하면
	모든 relation의 수를 구할 수 있다.
	3-1. 도시 첫 2글자와 주 코드가 동일한 경우를 고려해야 한다. (e.g. CALABASAS CA, CAMPBELL CA)
		이런 도시들은 서로 special relation이 아니다. (동일 주에 있으므로)
	3-2. 2로 나누기를 잊으면 안된다.

* 4개 문자로 정해지는 모든 경우의 수가 26*26 = 676이므로,
* unordered_map 대신 int[676][676]을 사용해도 된다.

*/

#include <iostream>
#include <unordered_map>
#include <array>

struct city {
	std::array<char, 2> name;
	std::array<char, 2> state;
};

bool operator==(const city& c1, const city& c2) {
	return c1.name == c2.name && c1.state == c2.state;
}

template<>
struct std::hash<city>
{
	std::size_t operator()(const city& c) const
	{
		// dirty hack which uses sizeof(city) == sizeof(int)
		static_assert(
			sizeof(int) == sizeof(city), 
			"This hack does not work since sizeof(int)!=sizeof(city)."
			);
		return std::hash<int>()(*((int*)(&c)));
	}
};

int main(void) {
	// c++ fast io
	std::cin.tie(0);
	std::ios_base::sync_with_stdio(false);



	int n;
	std::cin >> n;

	std::unordered_map<city, int> map;

	while (n--)
	{
		std::string name;
		std::string state;

		// operator>>() -> space-delimited string input
		std::cin >> name;
		std::cin >> state;

		city c;
		c.name[0] = name[0];
		c.name[1] = name[1];
		c.state[0] = state[0];
		c.state[1] = state[1];

		auto it = map.find(c);
		if (it == map.end()) {
			// new key
			map.insert({ c, 1 });
		}
		else {
			it->second += 1;
		}
	}

	unsigned long long result = 0;
	for (auto it = map.begin(); it != map.end(); ++it)
	{
		if (it->first.state == it->first.name)
			continue;

		city c2{ .name = it->first.state, .state = it->first.name };
		if (auto it2 = map.find(c2); it2 != map.end())
		{
			result += it->second * it2->second;
		}
	}

	std::cout << result / 2;

	return 0;
}