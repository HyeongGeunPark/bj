#define N_MAX 50000
#include<stdio.h>

#define min(a,b) (((a)>(b))?(b):(a))

int arr[N_MAX+1] = {0, 1, };

void solve(int n){
	int temp;
	arr[n] = 5;
	for(int i=1; (temp = n-i*i)>=0; i++){
		if(temp==0){
			arr[n] = 1;
			return;
		}
		if(arr[temp] == 0){
			solve(temp);
		}
		arr[n] = min(arr[n], arr[temp]+1);
	}
}

int main(void){
	int n;
	scanf("%d", &n);
	solve(n);

	printf("%d", arr[n]);

	return 0;
}

