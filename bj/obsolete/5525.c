#include<stdio.h>
#include<stdlib.h>

#define M_MAX 1000000

int main(void){

    int n, m;
    scanf("%d %d ", &n, &m);

    char *buf = malloc(sizeof(char) * (m+1));
    fread(buf, m--, sizeof(char), stdin);

    int cnt = 0;
    int length;

    if(buf[0] == 'I'){
        length = 1;
    }
    else{
        length = 0;
    }
    for(int i=0;i<m;i++){
        // find IOIOI... series
        if(buf[i] != buf[i+1]) length++;
        else{
            // calculate and restart
            // number of Pa in Pb(b>=a) = b-a+1
            // length -> b calculation: b = (length-1)/2
            // e. g) 1->0, 2->0, 3->1, 4->1, ......
            if(length > (2*n))
                cnt = cnt + ((length-1)/2) - n + 1;
            if(buf[i+1] == 'I') length = 1;
            else length = 0;
        }
    }
    if(length > (2*n))
        cnt = cnt + ((length-1)/2) - n + 1;
    printf("%d\n", cnt);

    free(buf);
    return 0;
}
