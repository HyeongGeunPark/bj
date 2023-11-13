/*#pragma GCC optimize("O3")*/

#include<stdio.h>
#include<stdlib.h>

/***********************************************************************/
// MINHEAP

#define HEAPSIZE 20000
struct node{
    int value, key;
};

struct minheap{
    struct node *data;
    int size;
    int len;
};

#define minheap_init(name) struct minheap name = {.size = HEAPSIZE, .len = 0,\
            .data = malloc((HEAPSIZE+1) * sizeof(struct node))}
#define minheap_free(name) free(name.data)

static inline void minheap_add(struct minheap *h, int value, int key){
    // c is key, i is value
    int c = ++h->size;
    int p = c>>1;
    while(p){
        if(h->data[p].key > key){
            h->data[c] = h->data[p];
            c = p;
            p = c>>1;
        }
        else{
            break;
        }
    }
    h->data[c].key = key;
    h->data[c].value = value;
}

static inline struct node minheap_del(struct minheap *h){
    struct node r = h->data[1];
    struct node temp = h->data[h->size--];
    int p = 1;
    int c = 2;
    while(c<=h->size){
        if(c<h->size && h->data[c].key > h->data[c+1].key){
            c++;
        }
        if(h->data[c].key < temp.key){
            h->data[p] = h->data[c];
            p = c;
            c = p<<1;
        }
        else{
            break;
        }
    }
    h->data[p] = temp;
    return r;
}

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


/***********************************************************************/
void dijkstra(int start, unsigned char (*map)[1001], int n, struct minheap *h, int *minlen){
    // initialize heap
    h->size = 0;

    minlen[start] = 1;
    minheap_add(h, start, 1);

    while(h->size){
        struct node current = minheap_del(h);
        if(current.key > minlen[current.value]){
            continue;
        }
        for(int i=1;i<=n;i++){
            if(map[current.value][i]==0){
                continue;
            }
            int new_len = current.key + map[current.value][i];
            if(minlen[i]==0 || new_len < minlen[i]){
                minlen[i] = new_len;
                minheap_add(h, i, new_len);
            }
        }
    }
}

int main(void){

    int n, m, x;
    unsigned char map_come[1001][1001]  ={0};
    unsigned char map_back[1001][1001]  ={0};
    int i, j;
    int a, b, c;
    minheap_init(h);
    int maxlen;
    int temp;
    int minlen_come[1001] = {0};
    int minlen_back[1001] = {0};
    
    mymmap();

    readd(&n);
    readd(&m);
    readd(&x);

    for(i=0;i<m;i++){
        readd(&a);
        readd(&b);
        readd(&c);
        map_come[b][a] = c;
        map_back[a][b] = c;
    }

    dijkstra(x, map_come, n, &h, minlen_come);
    dijkstra(x, map_back, n, &h, minlen_back);

    maxlen = 0;
    for(i=1;i<=n;i++){
        temp = minlen_back[i] + minlen_come[i];
        if(maxlen < temp){
            maxlen = temp;
        }
    }

    printf("%d\n", maxlen - 2);
    
    return 0;
}
