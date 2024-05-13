#pragma GCC optimize("O3")

#include<stdio.h>


int cnt;
int col[15];
int diag1[29];
int diag2[29];


void queen(int d, int n){

    int i, j;
    int d1, d2;
    for(i=0; i<n; i++){
        d1 = d-i+n-1;
        d2 = d+i;
        
        if(col[i]==0 && diag1[d1]==0 && diag2[d2]==0){
            if(d==n-1){
                cnt++;
                continue;
            }
            col[i] = diag1[d1] = diag2[d2] = 1;
            queen(d+1, n);
            col[i] = diag1[d1] = diag2[d2] = 0;
        }
    }
}

int main(void){

    int n;
    scanf("%d", &n);
    queen(0,n);
    printf("%d\n", cnt);
    return 0;

}