/*#pragma GCC optimize("O3")*/

#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<unistd.h>
/*----------------------------------------------------------------------------*/

// variadic function support macros
// do not accept 0-adic function
// usage:
//	1. define a macro to use
//		#define myfunc(...) vrg(function_name, __VA__ARGS__)
//	2. defint macros corresponding each variable number
//		#define function_name1(a) <corresponding action 1>
//		#define function_name2(a,b) <corresponding action 2>
//		...
//	3. call the variadic function
//		myfunc(a); -> corresponding action 1
//		myfunc(a,b); -> corresponding action 2

// count the number of arguments
// i.e., vrg_argn(1,2) -> vrg_cnt(1,2,6,5,4,3,2,1,0) -> vrg3 = 6, vrg4 = 5, ..., vrgN = 2
#define vrg_cnt(vrg1, vrg2, vrg3, vrg4, vrg5, vrg6, vrgN, ...) vrgN
#define vrg_argn(...) vrg_cnt(__VA_ARGS__, 6, 5, 4, 3, 2, 1, 0)
#define vrg_cat0(x,y) x##y
#define vrg_cat(x, y) vrg_cat0(x,y)
#define vrg(vrg_f, ...) vrg_cat(vrg_f, vrg_argn(__VA_ARGS__))(__VA_ARGS__)

/*----------------------------------------------------------------------------*/

// buffered input output related things
#define BUF_SIZE (1<<20)  // size of input, output buffer for buffered IO functions

//check: all bulk read functions(reads, readu) removes delimeter automatically
//      all bulk write functions(writes, writeu) adds some end character(currently \n)

// static allocation version
char BUF[BUF_SIZE + 1];
char *p=BUF;  // input buffer handling pointer
char *pl = NULL;   // input buffer last pointer(be careful that the value of this pointer is  an invalid value)
char WBUF[BUF_SIZE+1];
char *wp=WBUF;

/* Dynamic allocation version
char *BUF;
char *p;  // input buffer handling pointer
char *pl = NULL;   // input buffer last pointer(be careful that the value of this pointer is  an invalid value)
char *WBUF;
char *wp;
#define RBUF_INIT(name) (name)=(char*)malloc(sizeof(char)*(BUF_SIZE+1));\
							   p = BUF
#define WBUF_INIT(name) (name)=(char*)malloc(sizeof(char)*(BUF_SIZE+1));\
							   wp = WBUF
#define BUF_INIT() RBUF_INIT(BUF);WBUF_INIT(WBUF)
#define BUF_FREE() free(BUF);free(WBUF)
*/


// writebuf_f: dump all available WBUF to stdout manually
static inline void writebuf_f(){
    write(STDOUT_FILENO, WBUF, (wp-WBUF));
    wp = WBUF;
}

// writebuf: if WBUF is full, dump all WBUF to stdout
// only for internal use, do not use it directly
static inline void __writebuf(){
    if(wp == WBUF+BUF_SIZE){
        writebuf_f();
    }
}

// write a character
static inline void writec(char c){
    __writebuf();
    *wp++ = c;
}

// write from \0 padded string to write buffer
// variadic function: second argument can be used to specify ending character
//						default value is '\n'
// do not check string size, so be careful with segfault
#define writes(...) vrg(writes_, __VA_ARGS__)
#define writes_1(cp) __writes(cp, '\n')
#define writes_2(cp, end) __writes(cp, end)
static inline void __writes(char *cp, char end){
    while(*cp != 0 ){
        writec(*cp++);
    }
    writec(end);
}

// convert an unsigned decimal to character string and write it
// variadic function: second argument can be used to specify ending character
//						default value is '\n'
#define writed(...) vrg(writed_, __VA_ARGS__)
#define writed_1(d) __writed(d, '\n')
#define writed_2(d, end) __writed(d, end)
#define WUD_SIZE 30
static inline void __writed(long long d, char end){
    int i;
    char sign = 0;
    char buf[WUD_SIZE];
    char *bp = buf + WUD_SIZE - 1;
    if(d<0){
        sign = 1;
        d = -d;
    }
	else if(d==0){
		*bp-- = '0';
	}
    while(d>0){
        i=d%10;
        *bp-- = i + '0';
        d/=10;
    }
    if(sign){
        writec('-');
    }
    while(bp < (buf + WUD_SIZE - 1)){
        writec(*(++bp));
    }
    writec(end);
}

// read from stdin to BUF manually
// this function should be called at the first
static inline void readbuf_f(void){
    p = BUF;
    int r_return = read(STDIN_FILENO, BUF, BUF_SIZE);
    if(r_return<0){
		r_return = 0;
    }
    pl = BUF + r_return;
    *pl = 0;
}

// check the BUF is already all used and if so,
// read available amount of characters from stdin to BUF
// only for internal use
static inline void __readbuf(void){
    if(p == pl){
        readbuf_f();
    }
}

// read a character from buffered input
static inline char readc(void){
    __readbuf();
    return *p++;
}

// return the first character in input buffer
static inline char readbuf_first(){
    return *p;
}

// ignore n characters
static inline void readn_ignore(int n){
    int valid_chars = pl - p;
    while(n>valid_chars){
        n -= valid_chars;
        readbuf_f();
        valid_chars = pl-p;
    }
    p += n;
}

// same function with isalpha(char) from string.h
static inline int isalp(char c){
    return ( c >= 'a' && c <= 'z') || ( c >= 'A' && c <= 'Z');
}

// check if the character is an arabic number
static inline int isnum(char c){
    return (c >= '0' && c <= '9');
}

// read an integer from buffered input
static inline int readd(int *up){
    char c;
    int result = 0;
    char negative = 0;
    *up = 0;
    while (1) {
        c = readc();
        if (isnum(c)) {
            break;
        }
        else if (c == '-') {
            negative = 1;
            c = readc();
            break;
        }
    }
	do{
        result = (result*10) + (c-'0');
	}while(isnum(c=readc()));
	if(negative) result = -result;
    *up = result;
    return result;
}

// read a string, consisted with non-control characters(>32), from buffered input
// make null-padded string
static inline void reads(char *dest){
    char c;
    //readbuf_flush();
    while(33>(c=readc())){
	}
    do{
        *dest++ = c;
    }while(32<(c=readc()));
    *dest=0;
}

/*----------------------------------------------------------------------------*/

// generic min heap
struct minheap{
    void *data;
    int size;
};


/*----------------------------------------------------------------------------*/

// min heap for Dijkstra's Algorithm
#define MINHEAP_SIZE 100000
struct node{
    int index;
    int cost;
};

#define minheap_init(name) struct minheap name = {\
                .data = malloc(sizeof(struct node)*(MINHEAP_SIZE+1)), .size=0}

#define minheap_free(name) free(name.data);

static inline void minheap_add(struct minheap *h, struct node *new){
    struct node *data = (struct node *)(h->data);

    int p, c;
    c = ++h->size;
    p = c>>1;

    while(p){
        if(data[p].cost > new->cost){
            data[c] = data[p];
            c = p;
            p = c>>1;
        }
        else{
            break;
        }
    }
    data[c] = *new;
}

static inline struct node minheap_del(struct minheap *h){
    struct node *data = (struct node *)(h->data);
    int p, c;
    struct node r = {0,0};
    if(h->size==0){
        return r;
    }
    r = data[1];
    
    struct node temp = data[h->size--];

    p = 1;
    c = 2;

    while(c<=h->size){
        if(c<h->size && data[c].cost > data[c+1].cost){
            c++;
        }
        if(data[c].cost < temp.cost){
            data[p] = data[c];
            p = c;
            c = p<<1;
            continue;
        }
        break;
    }
    data[p] = temp;
    return r;
}




/*----------------------------------------------------------------------------*/

int main(void){
    int n, m;
    int i, j;
    int dep, dest, cost;
    int **map;
    int *mcost;
    int *visited;
    struct node temp, current;
    minheap_init(h);

    readbuf_f();
    readd(&n);
    readd(&m);
    n++;
    map = malloc(sizeof(int*)*n);
    for(i=0;i<n;i++){
        map[i] = malloc(n*sizeof(int));
    }
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            map[i][j] = INT_MAX;
        }
    }
    mcost  = malloc(n*sizeof(int));
    for(i=0;i<n;i++){
        mcost[i] = INT_MAX;
    }
    visited = calloc(n, sizeof(int));

    for(i=0;i<m;i++){
        readd(&dep);
        readd(&dest);
        readd(&cost);
        if(map[dep][dest] > cost){
            map[dep][dest] = cost;
        }
    }

    readd(&dep);
    readd(&dest);
    if(dep == dest){
        printf("0\n");
        goto free;
    }
    // Dijkstra's Algorithm, using min heap
    temp.index = dep;
    temp.cost = 0;
    mcost[dep] = 0;
    minheap_add(&h, &temp);
    while(h.size!=0){
        current = minheap_del(&h);
        if(current.index == dest){
            break;
        }
        if(visited[current.index]){
            continue;
        }
        visited[current.index] = 1;
        for(i=1;i<n;i++){
            if(map[current.index][i]==INT_MAX){
                continue;
            }
            if(mcost[i] > (mcost[current.index]+map[current.index][i])){
                mcost[i] = mcost[current.index]+map[current.index][i];
                temp.index=i;
                temp.cost = mcost[i];
                minheap_add(&h, &temp);
            }
        }
    }

    printf("%d\n", mcost[dest]);

    free:

    for(i=0;i<n;i++){
        free(map[i]);
    }
    free(map);
    free(mcost);
    free(visited);
    return 0;
}