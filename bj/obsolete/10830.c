#pragma GCC optimize("O3")

#include<stdio.h>

int main(void){
    int n;
    unsigned long long b;
    int i, j, k;
    int p;

    int memo[38][5][5] = {0};
    int result[5][5] = {0};
    int temp[5][5] = {0};

    scanf("%d %llu", &n, &b);
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            scanf("%d", &memo[0][i][j]);
        }
    }
    for(i=0;i<n;i++){
        result[i][i] = 1;
    }
    
    p=0;
    while(b){
        if(b&1){
            for(i=0;i<n;i++){
                for(j=0;j<n;j++){
                    temp[i][j] = 0;
                    for(k=0;k<n;k++){
                        temp[i][j] += result[i][k] * memo[p][k][j];
                        temp[i][j] %= 1000;
                    }
                }
            }
            for(i=0;i<n;i++){
                for(j=0;j<n;j++){
                    result[i][j] = temp[i][j];
                }
            }
        }
        p++;
        // matrix power
        for(i=0;i<n;i++){
            for(j=0;j<n;j++){
                for(k=0;k<n;k++){
                    memo[p][i][j] += memo[p-1][i][k] * memo[p-1][k][j];
                    memo[p][i][j] %= 1000;
                }
            }
        }
        b>>=1;
    }

    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }

    return 0;
}