#include<stdio.h>

int main(void){

	int t;
	int n;
	scanf("%d", &t);

	int arr[11]={0};
	arr[0] = 1;
	arr[1] = 2;
	arr[2] = 4;
	for(int j=0;j<t;j++){
		scanf("%d", &n);
		for(int i=3;i<n;i++){
			if(arr[i]==0)
				arr[i] = arr[i-3] + arr[i-2] + arr[i-1];
		}
		printf("%d\n", arr[n-1]);
	}
	return 0;
}

