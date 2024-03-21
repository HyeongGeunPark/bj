/*#pragma GCC optimize("O3")*/
#include<stdio.h>
#include<stdlib.h>

#include<unistd.h>
#include<string.h>

#include<sys/stat.h>
#include<sys/mman.h>

char *RBUF;
char *rp;
#define WBUF_SIZE 1<<20
char WBUF[WBUF_SIZE];
char *wp = WBUF;
size_t filesize;

static inline size_t mymmap(){
    struct stat stat;
    filesize = fstat(STDIN_FILENO, &stat);
    RBUF = mmap(NULL, stat.st_size, PROT_READ, MAP_PRIVATE, STDIN_FILENO, 0);
    rp = RBUF;
    return stat.st_size;
}

static inline void mymunmap(){
    munmap(RBUF, filesize);
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


struct pos{
    // x, y ->coordinate
    short x, y;
};

struct state{
    struct pos p;
    // boom -> 0 means no wall is crushed, 1 means a wall is crushed
    char boom;
};

static inline int pos_equal(struct pos *a, int x, int y){
    return (a->x == x && a->y == y);
};

/********************************************************************/
// simple resizing queue
#define Q_SIZE 1000
struct queue{
    struct state *data;
    int size;
    int f, l;
};

#define queue_init(name) struct queue name = {.size=Q_SIZE, .f=0, .l=0,\
                .data = malloc(Q_SIZE * sizeof(struct state))}

#define queue_free(name) free(name.data)

static inline void queue_resize(struct queue *q){
    struct state *temp = q->data;
    q->size += (q->size>>1);
    q->data = malloc(q->size * sizeof(struct state));
    memcpy(q->data, temp+q->f, (q->l-q->f) * sizeof(struct state));
    free(temp);
    q->l -= q->f;
    q->f = 0;
}

static inline void queue_add_last(struct queue *q, int x, int y, int boom){
    if(q->l==q->size){
        queue_resize(q);
    }
    q->data[q->l].p.x = x;
    q->data[q->l].p.y = y;
    q->data[q->l++].boom = boom;

}

static inline struct state queue_del(struct queue *q){
    if(q->f==q->l){
        return (struct state){.boom=0, .p.x=0, .p.y=0};
    }
    return (q->data[q->f++]);
}

static inline int queue_len(struct queue *q){
    return q->l - q->f;
}

static inline int not_in_range(int x, int n){
    return (x<=0) || (x>n);
}

/********************************************************************/
int main(void){
    int n, m;
    int i, j;
    char map[1001][1002];
    char visited[1001][1002] = {0};
    int cnt;
    short dx[4] = {0, 0, 1, -1};
    short dy[4] = {1, -1, 0, 0};
    struct state current;
    queue_init(q);
    mymmap();


    // input
    readd(&n);
    readd(&m);
    for(i=1;i<=n;i++){
        reads(&(map[i][1]));
    }

    // bfs
    visited[1][1] = 3;
    queue_add_last(&q, 1, 1, 0);

    cnt = 0;
    while(i = queue_len(&q)){
        cnt++;
        while(i--){
            current = q.data[q.f++];
            if(pos_equal(&(current.p), n, m)){
                goto print;
            }
            for(j=0;j<4;j++){
                short x = current.p.x + dx[j];
                short y = current.p.y + dy[j];
                int boom = current.boom;
                if(not_in_range(x,n) || not_in_range(y,m)){
                    continue;
                }
                if(boom==0){
                    if(map[x][y]=='0' && (visited[x][y]==0 || visited[x][y]==2)){
                        visited[x][y]=3;
                        queue_add_last(&q, x, y, 0);
                    }
                    else if(map[x][y]=='1' && (visited[x][y]==0)){
                        visited[x][y]=2;
                        queue_add_last(&q, x, y, 1);
                    }
                }
                else{
                    if(map[x][y]=='0' && visited[x][y]==0){
                        visited[x][y]=2;
                        queue_add_last(&q, x, y, 1);
                    }
                }
            }
        }

    }

    print:
    printf("%d\n", visited[n][m]?cnt:-1);

    queue_free(q);
    mymunmap();
    
    return 0;
}