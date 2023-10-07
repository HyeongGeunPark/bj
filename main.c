#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>


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
#define BUF_SIZE 100000   // size of input, output buffer for buffered IO functions
#define STDOUT_FD 1
#define STDIN_FD 0

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
    write(STDOUT_FD, WBUF, (wp-WBUF));
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
static inline void __writed(int d, char end){
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
    int r_return = read(STDIN_FD, BUF, BUF_SIZE);
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
// bitmap related things
//#include<stdlib.h>

// do not try to access the bitmap by its name directly
#define bit_to_long(bit) (((bit)>>6) + 1)  // 2^6 = 64, long is 64bits
#define bit_to_index(bit) ((bit)>>6)
#define bit_to_offset(bit) ((bit)&(0x3F))   // 0x3f = 0b111111 = 63(10)
#define bmap_init(name, bit) long name[bit_to_long(bit)] = {0,}
#define bmap_init_dynamic(name, bit) long *name = calloc(bit_to_long(bit), sizeof(long))
#define bmap_free_dynamic(name) free(name)
#define bmap_set(name, bit) name[bit_to_index(bit)] |= (((long)1)<<(bit_to_offset(bit)))
#define bmap_reset(name, bit) name[bit_to_index(bit)] &= ~(((long)1)<<(bit_to_offset(bit)))
#define bmap_toggle(name, bit) name[bit_to_index(bit)] ^= (((long)1)<<(bit_to_offset(bit)))
#define bmap_get(name, bit) ((name[bit_to_index(bit)]>>(bit_to_offset(bit))) & ((long)1))
#define bmap_set_long(name, bit) name[bit_to_index(bit)] |= (long)0xffffffff
#define bmap_reset_long(name, bit) name[bit_to_index(bit)] &= 0
#define bmap_set_all(name, bit) memset(name, 0, sizeof(long)*bit_to_long(bit))
#define bmap_reset_all(name, bit) memset(name, (char)0xFF, sizeof(long)*bit_to_long(bit))

// 2D bitmap

struct bmap2_size{
	int m;
	int len;
};

const static struct bmap2_size bmap2_size_zero = {.m=0, .len=0};

#define __bmap2_size_init(name, a, b) struct bmap2_size name_size = {.m = (b), .len=(a)*(b)}
#define bmap2_init(name, n, m) __bmap2_size_init(name,n,m);bmap_init(name, name_size.len)
#define bmap2_init_dynamic(name, n, m) __bmap2_size_init(name,n,m);bmap_init_dynamic(name, name_size.len)
#define bmap2_free(name) free(name);name_size = bmap2_size_zero
#define bmap2_index_to_bit(name,i,j) ((i)*(name_size.m)+(j))
#define bmap2_set(name, i, j) bmap_set(name, bmap2_index_to_bit(name,i,j))
#define bmap2_reset(name, i, j) bmap_reset(name, bmap2_index_to_bit(name,i,j))
#define bmap2_toggle(name, i, j) bmap_toggle(name, bmap2_index_to_bit(name,i,j))
#define bmap2_get(name, i, j) bmap_get(name, bmap2_index_to_bit(name,i,j))
#define bmap2_set_all(name) memset(name, (char)0xFF, ((name_size.len>>3)+1))
#define bmap2_reset_all(name) memset(name, 0, ((name_size.len>>3)+1))
#define bmap2_toggle_all(name) for(int i=0;i<(bit_to_long(name_size.len));i++) name[i]^=(long)0xffffffff

/*----------------------------------------------------------------------------*/

// hashtable related things
// hashtable with linked list(collision handle)
#include<string.h>
#define BUCKET_SIZE 150001 // this thing should be preferably bigger than x1.3 of total data number
#define HASH_VAL 29
struct hashitem{
    char *key;
    char *value;
    struct hashitem *next;
};

struct hashtable{
    struct hashitem **items;
    int size;
    int count;
};

#define hashtable_init(name) struct hashtable name =\
{.items=calloc(BUCKET_SIZE, sizeof(struct hashitem*)), .size=BUCKET_SIZE, .count=0}

static inline int hash(char *s){
    
    int result = 0;
    while(*s != 0){
        result *= HASH_VAL;
        result += ((*s++)-32);
        result %= BUCKET_SIZE;
    }
    return result;
}

// initialize an item
static inline struct hashitem *hashitem_init(char *key, char *value){
    struct hashitem *i = calloc(1, sizeof(struct hashitem));
    int len = strlen(key)+1;
    i->key = malloc(len+1);
    memcpy(i->key, key, len+1);
	len = strlen(value)+1;
    i->value = malloc(len+1);
	memcpy(i->value, value, len+1);
    i->next = NULL;
    return i;
}
// add an element
static inline void hashtable_add(struct hashtable *t, char *key, char *value){
    struct hashitem *n = hashitem_init(key, value);
    int i = hash(key);
    if(t->items[i] == NULL){    // bucket is empty
        t->items[i] = n;
        t->count++;
    }
    else{ // collision control
        struct hashitem *temp = t->items[i];
		while(temp->next != NULL){
            if(strcmp(key, temp->key)==0) return;   // ignore input with same key
            temp = temp->next;
        }
        temp->next = n;
        t->count++;
    }
}
// delete an element
static inline void hashtable_del(struct hashtable *t, char *key){
    int i = hash(key);
    
    struct hashitem *temp = t->items[i];
    struct hashitem *prev = NULL;
    while(temp != NULL){
        if(strcmp(key, temp->key)==0){   // key found
            if(prev == NULL){
                // element in first
                t->items[i] = temp->next;
                free(temp->key);
				free(temp->value);
                free(temp);
                t->count--;
            }
            else{
                prev->next = temp->next;
                free(temp->key);
				free(temp->value);
                free(temp);
                t->count--;
            }
            return;
        }
        else{
            prev = temp;
            temp = temp->next;
        }
    }
}
// find an element with key and return its value
static inline char *hashtable_find(struct hashtable *t, char *key){
    int i = hash(key);
    struct hashitem *temp = t->items[i];
    while(temp != NULL){
        if(strcmp(key, temp->key)==0){  // key found
            return temp->value;
        }
        temp = temp->next;
    }
    // not found
    return NULL;
}
// delete all elements in the hashtable
static inline void hashtable_del_all(struct hashtable *t){
    int i;
    for(i=0;i<t->size;i++){
        struct hashitem *temp = t->items[i];
        t->items[i] = NULL;
        while(temp!=NULL){
            struct hashitem *next = temp->next;
            free(temp->key);
			free(temp->value);
            free(temp);
            temp = next;
        }
    }
    t->count = 0;
}
// delete hashtable
static inline void hashtable_free(struct hashtable *t){
    free(t->items);
}

/*----------------------------------------------------------------------------*/

// linked list related things
// windows default stack size : 1MB
// use dynamic allocation for big data structures

//#include<stdlib.h>
//#include<string.h>

/*
struct linkedlist{
	int len;
	struct llnode *next;
};

struct llnode{
	char *data;
	struct llnode *next;
};

#define ll_init(name) struct linkedlist (name) = {.len = 0, .next = NULL}

// initialize a node, only for internal use
static inline struct llnode *__llnode_init(char *data){
	struct llnode *newnode = (struct llnode*)malloc(sizeof(struct llnode));
	newnode->next = NULL;
	newnode->data = (char*)malloc(sizeof(char)*(strlen(data)+1));
	strcpy(newnode->data, data);
	return newnode;
}

// add a node
static inline void ll_add(struct linkedlist *head, char *data){
	struct llnode *pos = head->next;
	if(pos == NULL){
		head->next = __llnode_init(data);
		head->len++;
	}
	else{
		while(pos->next!=NULL)
			pos = pos->next;
		pos->next = __llnode_init(data);
		head->len++;
	}
}

// return the length of the linked list
static inline int ll_len(struct linkedlist *head){
	return head->len;
}

// access all nodes
#define ll_for_each(head, pos)\
	struct llnode *(pos);\
	for((pos) = (&head)->next; (pos)!=NULL; (pos)=(pos)->next)

// delete all nodes
static inline void ll_del_all(struct linkedlist *head){
	struct llnode *pos = head->next;
	struct llnode *next = NULL;
	while(pos!=NULL){
		next = pos->next;
		free(pos);
		pos = next;
	}
	head->len = 0;
	head->next = NULL;
}
*/
/*----------------------------------------------------------------------------*/
/*
// wrapper of strcmp for qsort
int mystrcmp(const void *a, const void *b){
	return strcmp(*(char**)a, *(char**)b);
}

// int compare function for qsort (ascending)
static inline int mycmp(const void *a, const void *b){
	return (*(int*)a)-(*(int*)b);
}
*/
/*----------------------------------------------------------------------------*/

// some macros

#define max(a,b) (((a)>(b))?(a):(b))
#define min(a,b) (((a)<(b))?(a):(b))

/*----------------------------------------------------------------------------*/

int main()
{
	return 0;
}

