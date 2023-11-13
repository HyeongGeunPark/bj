/*#pragma GCC optimize("O3")*/

#include<stdio.h>

typedef long long int ll;

int main(void){
    
    ll n;
    ll i, j;
    ll memo[100001];
    memo[0] = 0; // initial point
    ll t[100001] = {-1};
    ll b[100001] = {0};
    ll c[100001] = {0};

    scanf("%lld", &n);
    for(i=1;i<=n;i++){
        scanf("%lld", t+i);
    }
    for(i=1;i<=n;i++){
        scanf("%lld", b+i);
    }
    for(i=1;i<=n;i++){
        scanf("%lld", c+i);
    }

    for(i=1;i<=n;i++){
        ll tt = t[i]-b[i];
        // binary search
        int l = 0;
        int r = i;
        int mid;
        while(l<r){
            // l becomes leftmost element which is greater than or equal to tt
            mid = (l+r)/2;
            if(t[mid]<tt){
                l = mid+1;
            }
            else{
                r = mid;
            }
        }
        l--;    // rightmost element which is lesser than or equal to tt

        if(memo[i-1] > memo[l]+c[i]){
            memo[i] = memo[i-1];
        }
        else{
            memo[i] = memo[l]+c[i];
        }



    }


    printf("%lld\n", memo[n]);

    return 0;
}