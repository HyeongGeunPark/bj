#include<stdio.h>

int main(void){

	unsigned long long arr[100] = {1,1,1,2,2,3,4,5,7,9,0,};
	int t;
	int n;
	scanf("%d", &t);
	for(int i=0;i<t;i++){
		scanf("%d", &n);
		for(int j=9;j<n;j++){
			if(arr[j]==0)
				arr[j] = arr[j-1] + arr[j-5];
		}
		printf("%llu\n", arr[n-1]);
	}
	return 0;
}

