#pragma GCC optimize("O3")

#include<stdio.h>
#include<unistd.h>
#include<string.h>

#include<sys/stat.h>
#include<sys/mman.h>

char *RBUF;
char *rp;
#define WBUF_SIZE 1<<20
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

static inline void writes(char *c, char end){
    while(*c){
        *wp++ = *c++;
    }
    *wp++ = end;
}

#define max(a,b) ((a)>(b)?(a):(b))

int main(void){

    int lcs[1002] = {0};
    int i, j;
    int mm, t;
    int len_a, len_b;

    char a[1002];
    char b[1002];

    size_t filesize = mymmap();
    sscanf(RBUF, " %s\n %s\n", a+1, b+1);
    len_a = strlen(a+1)+1;
    len_b = strlen(b+1)+1;


    // lcs - DP
    for(i=1;i<len_a;i++){
        mm = 0;
        for(j=1;j<len_b;j++){
            t = lcs[j];
            if(a[i] == b[j]){
                lcs[j] = max(mm+1, lcs[j]);
            }
            else{
                lcs[j] = max(lcs[j], lcs[j-1]);
            }
            mm = t;
        }
    }
    printf("%d\n", lcs[len_b-1]);

    return 0;

}
