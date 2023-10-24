#include<stdio.h>

int main(void){
	int arr[1001] = {0, 1, 2, };
	int n;
	scanf("%d", &n);

	int i;
	for(i=3;i<=n;i++){
		arr[i] = (arr[i-1] + arr[i-2]) % 10007;
	}
	printf("%d", arr[n]);

	return 0;
}

