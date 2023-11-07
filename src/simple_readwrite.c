/*#pragma GCC optimize("O3")*/

#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>

/******************************************************************/

// simple buffered read / write
// line 8~87

#define RBUF_SIZE 2000000
#define WBUF_SIZE 2000000
char RBUF[RBUF_SIZE];
char WBUF[WBUF_SIZE];
char *rp = RBUF;
char *wp = WBUF;

static inline int is_num(char* c){
    return (*c>='0' && *c<='9');
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

    int n, l;
    int i, j;
    int cnt;
    char body[1002];
    int beauty[1000] = {0};
    int max_beauty = 0;
    body[0] = '0';

    read(STDIN_FILENO, RBUF, BUF_SIZE);
    readd(&n);
    readd(&l);

    for(i=0;i<n;i++){
        reads(&body[1]);
        // 줄무늬 찾기
        cnt = 0;
        for(j=0;j<l;j++){
            if(body[j]=='0' && body[j+1]=='1'){
                cnt++;
            }
        }
        beauty[i] = cnt;
        if(cnt>max_beauty){
            max_beauty = cnt;
        }
    }
    cnt = 0;
    for(i=0;i<n;i++){
        if(beauty[i] == max_beauty){
            cnt++;
        }
    }
    writed(max_beauty, ' ');
    writed(cnt, '\n');
    write(STDOUT_FILENO, WBUF, wp-WBUF);
    return 0;
}
