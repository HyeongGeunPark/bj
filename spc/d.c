/*#pragma GCC optimize("O3")*/

#include<stdio.h>

typedef long long int ll;

ll gcd(ll x, ll y){
    ll r = x%y;
    while(r){
        x = y;
        y = r;
        r = x%y;
    }

    return y;
}

ll lcm(ll x, ll y){
    return (x/gcd(x,y))*y;
}


int main(void){
    
    ll x, y;
    scanf("%lld %lld", &x, &y);
    ll g = gcd(x,y);
    ll l = x*y/g;

    if(x==y){
        printf("0\n");
    }
    else if(g==x){
        printf("1\n%lld\n", y-x);
    }
    else if(g==y){
        printf("1\n%lld\n", y-x);
    }
    else{
        printf("2\n%lld\n%lld\n", l-x, y-l);
    }

    return 0;
}