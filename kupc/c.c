#pragma GCC optimize("O3")

#include<stdio.h>

int main(void){
    unsigned int n, l;
    int i;
    char buf[20];
    scanf("%d %d", &n, &l);

    for(i=0;i<(l-1);i++){
        buf[i] = '1';
    }
    buf[i++] = n+'0';
    buf[i] = 0;

    printf("%s\n", buf);

    return 0;
}