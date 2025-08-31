/*
bj31876 자존심 강한 두 천재의 대결

같은 길이의 U진법과 V진법으로 표기된 수의 대소를 비교하자.

2 <= U, V <= 10이다.
수의 길이는 최대 3'000'000이다.

접근:
unsigned long long으로 입력받을 수 있는 최대 숫자는 
18'446'744'073'709'551'615
즉, 10^19-1, 19자리까지는 안전하게 입력이 된다.
 9'999'999'999'999'999'999

그런데 19자리의 가장 작은 10진수는 
 1'000'000'000'000'000'000 == 10^18
19자리의 가장 큰 9진수는 9^19 - 1 == 
 1,350,851,717,672,992,088

20자리의 가장 작은 10진수는
10'000'000'000'000'000'000 == 10^19
20자리의 가장 큰 9진수는 9^20 - 1 ==
12,157,665,459,056,928,800

21자리의 가장 작은 10진수는
100'000'000'000'000'000'000 == 10^20
20자리의 가장 큰 9진수는 9^21 - 1 ==
109'418'989'131'512'359'208 

22자리의 가장 작은 10진수는
1'000'000'000'000'000'000'000 == 10^21
22자리의 가장 큰 9진수는 9^22 - 1 ==
  984'770'902'183'611'232'880

  -> 22자리부터는 그냥 진법이 큰 쪽이 크다.

어떻게든 10^23 범위가 표현 가능한 정수형이 있으면 쉽게 풀 수 있다.



편법: 사실 임의 크기, 임의 진법 수의 입출력을 지원하는 언어/라이브러리를 사용하면
바로 해결된다.

*/

#include <iostream>
#include <cmath>
#include <string>

int main(void) {
	// c++ fast io
	std::cin.tie(0); 
	std::ios_base::sync_with_stdio(false);

	int u, v;
	std::cin >> u >> v;
	std::string ras;
	std::string auq;

	std::cin >> ras;
	std::cin >> auq;

	__int128

	if (u == v) {
		for (int i = 0; i < ras.length(); ++i) {
			if (ras[i] > auq[i]) {
				goto ras_won;
			}
			else if (ras[i] < auq[i]) {
				goto auq_won;
			}
		}
		goto tied; 
	}
	else if (u > v) {
		double ras_log = 0.0l;
		double auq_log = 0.0l;

	}
	else {

	}




	std::cout << "something not good happened.";
	return 0;

ras_won:
	std::cout << "ras";
	return 0;

auq_won:
	std::cout << "auq";
	return 0; 

tied:
	std::cout << "rasauq";
	return 0;
}