#pragma GCC optimize("O3")

#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>

/******************************************************************/

// simple buffered read / write

#define BUF_SIZE 2000000
char RBUF[BUF_SIZE];
char WBUF[BUF_SIZE];
char *rp = RBUF;
char *wp = WBUF;

static inline int is_num(char* c){
    return (*c>='0' && *c<='9');
}

static inline char readc(){
    return *rp++;
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

static inline void reads(char *c){
    while(1){
        if(*rp>32){
            break;
        }
        rp++;
    }
    while(1){
        *(c++) = *(rp++);
        if(*rp == '\n' || *rp == 0){
            break;
        }
    }
}

static inline void writed(int n, char end){
    char buf[20];
    int sign = 1;
    int i = 0;
    if(n<0){
        sign = 0;
        n = -n;
    }
    while(1){
        buf[i++] = n%10 + '0';
        n /= 10;
        if(n==0){
            break;
        }
    }
    if(sign==0){
        buf[i++] = '-';
    }
    while(i>0){
        *(wp++) = buf[--i];
    }
    *wp++ = end;
}


/******************************************************************/

// some macros

#define max(a, b) ((a)>(b)?(a):(b))

int main(void){

    int n;
    int half;
    int i;
    int alpha[26] = {0};
    char temp;
    int res;

    read(STDIN_FILENO, RBUF, BUF_SIZE);
    readd(&n);
    readc();
    half = n/2;

    for(i=0;i<half;i++){
        temp = readc();
        alpha[temp-'a']++;
    }
    if(n%2){
        readc();
    }
    for(i=0;i<half;i++){
        temp = readc();
        alpha[temp-'a']++;
    }

    res = 0;
    for(i=0;i<26;i++){
        if(alpha[i]%2){
            res = 1;
        }
    }

    if(res){
        printf("No\n");
    }
    else{
        printf("Yes\n");
    }
    return 0;
}
