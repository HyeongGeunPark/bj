/*#pragma GCC optimize("O3")*/

#include<stdio.h>

int main(void){

    int n, i;
    int temp;
    scanf("%d", &n);

    int mid = n/2;
    i = n;
    temp = 1;
    while(temp <= n){
        printf("%d ", temp);
        temp+=2;
    }
    if(temp== (n+2)){
        temp -=3;
    }
    else if(temp == (n+1)){
        temp -= 1;
    }
    while(temp>0){
        printf("%d ", temp);
        temp-=2;
    }


    printf("\n");

    return 0;
}