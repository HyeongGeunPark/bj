#include<stdio.h>
int gcd(int a, int b){
    int c;
    while((c = a%b) != 0){
        a = b;
        b = c;
    }
    return b;
}

int lcm(int a, int b){
    return (a*b/gcd(a,b));
}



int main(void){
    printf("%d\n", gcd(4, 12));
    return 0;
}