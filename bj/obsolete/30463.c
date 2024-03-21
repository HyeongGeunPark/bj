/*#pragma GCC optimize("O3")*/

#include<stdio.h>
#include<unistd.h>
#include<string.h>

#include<sys/stat.h>
#include<sys/mman.h>

char *RBUF;
char *rp;
#define WBUF_SIZE 1<<2
char WBUF[WBUF_SIZE];
char *wp = WBUF;

static inline size_t mymmap(){
    struct stat stat;
    fstat(STDIN_FILENO, &stat);
    RBUF = mmap(NULL, stat.st_size, PROT_READ, MAP_PRIVATE, STDIN_FILENO, 0);
    rp = RBUF;
    return stat.st_size;
}

static inline int is_num(char* c){
    return (*c>='0' && *c<='9');
}

static inline void write_f(void){
    write(STDOUT_FILENO, WBUF, wp-WBUF);
}

static inline int readd(int *n){
    int r = 0;
    int sign = 1;
    while(1){
        if(is_num(rp)){
            break;
        }
        else if(*rp=='-'){
            sign = 0;
            rp++;
            break;
        }
        rp++;
    }
    while(1){
        r *= 10;
        r += ((*rp++) - '0');
        if(!is_num(rp)){
            break;
        }
    }
    *n = sign?r:-r;
}

static inline int str2bit(){
    int r = 0;
    while(!is_num(rp)){
        rp++;
    }
    while(is_num(rp)){
        r |= 1<<(*rp-'0');
        rp++;
    }

    return r;
}

static inline int bitcount(int a){
    int i, r;
    i = 10;
    r = 0;
    while(i--){
        r += a&1;
        a>>=1;
    }
    return r;
}

static inline int bitcompare(int a, int b){
    return bitcount(a|b);
}


int main(void){

    int n, k;
    int i, j;
    long long cnt = 0;
    int temp;
    mymmap();
    readd(&n);
    readd(&k);
    int bits[1024] = {0};

    for(i=0;i<n;i++){
        temp = str2bit();
        bits[temp]++;
    }

    for(i=1;i<1024;i++){
        for(j=i;j<1024;j++){
            if(bitcompare(i,j)==k){
                if(i==j){
                    cnt += (long long)bits[i]*(bits[i]-1)/2;
                }
                else{
                    cnt += (long long)bits[i] * bits[j];
                }
            }
        }
    }

    printf("%lld\n", cnt);
    return 0;
}