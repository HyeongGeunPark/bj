/*
bj14626 ISBN
조건문, 모듈러 연산, 문자열
*/
#include <stdio.h> 

int main(void) {

	char buf[20] = { 0, };
	int erased_idx;
	int sum = 0;
	int erased_num;
	scanf("%s", buf);

	for (int i = 0; i < 13; ++i) {
		if (buf[i] != '*') {
			sum += (buf[i] - '0') * ((i%2 == 0)? 1 : 3);
		}
		else {
			erased_idx = i;
		}
	}

	erased_num = (10 - (sum % 10)) % 10;
	if (erased_idx % 2 != 0) {
		while(erased_num % 3 != 0) {
			erased_num += 10;
		}
		erased_num /= 3;
	}

	printf("%d\n", erased_num); 

	return 0;
}