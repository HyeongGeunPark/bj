#include<stdio.h>

int main(void){

    int n, r, c;
    scanf("%d %d %d", &n, &r, &c);

    n = (1<<n);
    int result = 0;

    while(n>1){
        n>>=1;
        int cnt=0;

        if(r>=n){
            // 2 or 3
            r -= n;
            cnt+=2;
        }
        if(c>=n){
            // 1 or 3
            c -= n;
            cnt+=1;
        }
        result += n*n*cnt;
    }

    printf("%d\n", result);

    return 0;
}