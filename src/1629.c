#pragma GCC optimize("O3")

#include<stdio.h>

int main(void){
    unsigned long long a, b, c;
    int i;
    unsigned long long powers[sizeof(unsigned long long)*8];
    unsigned long long result = 1;
    int len = 0;
    unsigned int temp;
    scanf("%llu %llu %llu", &a, &b, &c);

    powers[0] = a%c;
    temp = b;
    while(temp){
        len++;
        temp >>= 1;
    }
    for(i=1;i<len;i++){
        powers[i] = (powers[i-1] * powers[i-1])%c;
    }
    for(i=0;i<len;i++){
        if(b & (1<<i)){
            result = (result * powers[i])%c;
        }
    }
    printf("%lld\n", result);

    return 0;
}