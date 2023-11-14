// baekjoon gcc optimize options
/*#pragma GCC optimize("O3")*/
//#pragma GCC target("arch=haswell")

#include <stdio.h> 
#include <math.h>
#include <stdlib.h>
#include <unistd.h>

// 12~222 fastio

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
// bitmap related things
//#include<stdlib.h>
// do not try to access the bitmap by its name directly
// check os
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
   #ifdef _WIN64
		#define BIT_MASK (size_t)0x3F
		#define BIT_SHIFT 6
		#define BIT_FULL (size_t)0xFFFFFFFFFFFFFFFF
   #else
		#define BIT_MASK (size_t)0x1F
		#define BIT_SHIFT 5
		#define BIT_FULL (size_t)0xFFFFFFFF
   #endif
#elif __linux__
	#if defined(__LP64__) || defined(__LP64)
		#define BIT_MASK (size_t)0x3F
		#define BIT_SHIFT 6
		#define BIT_FULL (size_t)0xFFFFFFFFFFFFFFFF
	#else
		#define BIT_MASK (size_t)0x1F
		#define BIT_SHIFT 5
		#define BIT_FULL (size_t)0xFFFFFFFF
	#endif
#endif

#define bit_to_long(bit) (((bit)>>BIT_SHIFT) + 1)
#define bit_to_index(bit) ((bit)>>BIT_SHIFT)
#define bit_to_offset(bit) ((bit)&(BIT_MASK))   
#define bmap_init(name, bit) size_t name[bit_to_long(bit)] = {0,}
#define bmap_init_dynamic(name, bit) size_t *name = calloc(bit_to_long(bit), sizeof(size_t))
#define bmap_free(name) free(name)
#define bmap_set(name, bit) name[bit_to_index(bit)] |= (((size_t)1)<<(bit_to_offset(bit)))
#define bmap_reset(name, bit) name[bit_to_index(bit)] &= ~(((size_t)1)<<(bit_to_offset(bit)))
#define bmap_toggle(name, bit) name[bit_to_index(bit)] ^= (((size_t)1)<<(bit_to_offset(bit)))
#define bmap_get(name, bit) ((int)((name[bit_to_index(bit)]>>((size_t)bit_to_offset(bit))) & ((size_t)1)))
#define bmap_set_long(name, bit) name[bit_to_index(bit)] |= BIT_FULL
#define bmap_reset_long(name, bit) name[bit_to_index(bit)] &= 0
#define bmap_reset_all(name, bit) memset(name, 0, sizeof(size_t)*bit_to_long(bit))
#define bmap_set_all(name, bit) memset(name, (char)0xFF, sizeof(size_t)*bit_to_long(bit))
#define bmap_toggle_all(name, bit) for(int i=0;i<(bit_to_long(bit);i++) name[i]^=BIT_FULL

// 2D bitmap

struct bmap2_size{
	int m;
	int len;
};

const static struct bmap2_size bmap2_size_zero = {.m=0, .len=0};

#define __bmap2_size_init(name, a, b) struct bmap2_size name_size = {.m = (b), .len=(a)*(b)}
//#define bmap2_init(name, n, m) __bmap2_size_init(name,n,m);bmap_init(name, name_size.len)
#define bmap2_init_dynamic(name, n, m) __bmap2_size_init(name,n,m);bmap_init_dynamic(name, name_size.len)
#define bmap2_resize(name,a,b) name_size.m=(b);name_size.len=((a)*(b));free(name);name=calloc(bit_to_long(name_size.len))
#define bmap2_free(name) free(name);name_size = bmap2_size_zero
#define bmap2_index_to_bit(name,i,j) ((i)*(name_size.m)+(j))
#define bmap2_set(name, i, j) bmap_set(name, bmap2_index_to_bit(name,i,j))
#define bmap2_reset(name, i, j) bmap_reset(name, bmap2_index_to_bit(name,i,j))
#define bmap2_toggle(name, i, j) bmap_toggle(name, bmap2_index_to_bit(name,i,j))
#define bmap2_get(name, i, j) bmap_get(name, bmap2_index_to_bit(name,i,j))
#define bmap2_set_all(name) memset(name, (char)0xFF, ((name_size.len>>3)+1))
#define bmap2_reset_all(name) memset(name, 0, ((name_size.len>>3)+1))
#define bmap2_toggle_all(name) for(int i=0;i<(bit_to_long(name_size.len));i++) name[i]^=BIT_FULL


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

// hashtable with integer value

struct hashitem_i{
    char *key;
    int value;
    struct hashitem_i *next;
};

struct hashtable_i{
    struct hashitem_i **items;
    int size;
    int count;
};

#define hashtable_init_i(name) struct hashtable_i name =\
{.items=calloc(BUCKET_SIZE, sizeof(struct hashitem_i*)), .size=BUCKET_SIZE, .count=0}

// initialize an item
static inline struct hashitem_i *hashitem_init_i(char *key, int value){
    struct hashitem_i *i = calloc(1, sizeof(struct hashitem_i));
    int len = strlen(key)+1;
    i->key = malloc(len+1);
    memcpy(i->key, key, len+1);
	i->value = value;
    i->next = NULL;
    return i;
}
// add an element
static inline void hashtable_add_i(struct hashtable_i *t, char *key, int value){
    struct hashitem_i *n = hashitem_init_i(key, value);
    int i = hash(key);
    if(t->items[i] == NULL){    // bucket is empty
        t->items[i] = n;
        t->count++;
    }
    else{ // collision control
        struct hashitem_i *temp = t->items[i];
		while(temp->next != NULL){
            if(strcmp(key, temp->key)==0) return;   // ignore input with same key
            temp = temp->next;
        }
        temp->next = n;
        t->count++;
    }
}
// delete an element
static inline void hashtable_del_i(struct hashtable_i *t, char *key){
    int i = hash(key);
    
    struct hashitem_i *temp = t->items[i];
    struct hashitem_i *prev = NULL;
    while(temp != NULL){
        if(strcmp(key, temp->key)==0){   // key found
            if(prev == NULL){
                // element in first
                t->items[i] = temp->next;
                free(temp->key);
                free(temp);
                t->count--;
            }
            else{
                prev->next = temp->next;
                free(temp->key);
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
static inline int *hashtable_find_i(struct hashtable_i *t, char *key){
    int i = hash(key);
    struct hashitem_i *temp = t->items[i];
    while(temp != NULL){
        if(strcmp(key, temp->key)==0){  // key found
            return &(temp->value);
        }
        temp = temp->next;
    }
    // not found
    return NULL;
}
// delete all elements in the hashtable
static inline void hashtable_del_all_i(struct hashtable_i *t){
    int i;
    for(i=0;i<t->size;i++){
        struct hashitem_i *temp = t->items[i];
        t->items[i] = NULL;
        while(temp!=NULL){
            struct hashitem_i *next = temp->next;
            free(temp->key);
            free(temp);
            temp = next;
        }
    }
    t->count = 0;
}
// delete hashtable
static inline void hashtable_free_i(struct hashtable_i *t){
    free(t->items);
}

/*----------------------------------------------------------------------------*/

// generic circular double linked list
// define a structure, which contains struct list_head as a member
// and define create/delete(free) functions for the structure.
// then the structure can be used as a list node,
// using list access functions below

#define _offsetof(type, member) ((char*) &( ((type*)0)->member ))
#define container_of(ptr, type, member) (type*)( (char*)ptr - _offsetof(type, member) )

struct list_head{
	struct list_head *prev, *next;
};

// declare a list_head structure
// e.g: LIST_HEAD(name);
#define LIST_HEAD_INIT(name) { &(name), &(name) }
#define LIST_HEAD(name) struct list_head name = LIST_HEAD_INIT(name)

// initialize a list_head structure
static inline void INIT_LIST_HEAD(struct list_head *list){
	list->next = list;
	list->prev = list;
}

// insert a new entry
// for internal use, do not need to do WRITE_ONCE,
// since this code would not be optimized
static inline void __list_add(struct list_head *new, struct list_head *prev, struct list_head *next){
	next->prev = new;
	new->next = next;
	new->prev = prev;
	prev->next = new;
}

// add a new entry in first place
static inline void list_add(struct list_head *new, struct list_head *head){
	__list_add(new, head, head->next);
}

// add a new entry in last place
static inline void list_add_tail(struct list_head *new, struct list_head *head){
	__list_add(new, head->prev, head);
}

// delete an entry between 2 entries
// for internal use, do not need to do WRITE_ONCE,
// since this code would not be optimized
static inline void __list_del(struct list_head *prev, struct list_head *next){
	next->prev = prev;
	prev->next = next;
}

// delete an entry, the entry becomes undefined state
static inline void list_del(struct list_head *entry){
	__list_del(entry->prev, entry->next);
	entry->next = NULL;
	entry->prev = NULL;
}

// delete & initialize
static inline void list_del_init(struct list_head *entry){
	list_del(entry);
	INIT_LIST_HEAD(entry);
}

// replace: delete an entry, and insert new entry in that place
static inline void list_replace(struct list_head *old, struct list_head *new){
	new->next = old->next;
	new->next->prev = new;
	new->prev = old->prev;
	new->prev->next = new;
}

// replace & initialize old entry
static inline void list_replace_init(struct list_head *old, struct list_head *new){
	list_replace(old, new);
	INIT_LIST_HEAD(old);
}

// swap: replace entry1 with entry2 and add entry1 at entry2's position
static inline void list_swap(struct list_head *entry1, struct list_head *entry2){
	struct list_head *pos = entry2->prev;
	list_del(entry2);
	list_replace(entry1, entry2);
	if(pos==entry1)	// the case when entry1 is prev of entry2
		pos=entry2;	// list_add(entry1, entry1) does not make sense
	list_add(entry1, pos);
}

// move: delete from one list and add as another's head
static inline void list_move(struct list_head *list, struct list_head *head){
	list_del(list);
	list_add(list,head);
}

// move_tail: delete from one list and add as another's tail
static inline void list_move_tail(struct list_head *list, struct list_head *head){
	list_del(list);
	list_add_tail(list, head);
}

// bulk_move_tail: move a subsection of a list to its tail
// should be in state like: head ... first ... last ... head
// first can be the same as last
static inline void list_bulk_move_tail(struct list_head *head, struct list_head *first, struct list_head *last){
	first->prev->next = last->next;
	last->next->prev = first->prev;

	head->prev->next = first;
	first->prev = head->prev;

	last->next = head;
	head->prev = last;
}

// is_first
static inline int list_is_first(const struct list_head *list, const struct list_head *head){
	return list->prev == head;
}

// is_last
static inline int list_is_last(const struct list_head *list, const struct list_head *head){
	return list->next == head;
}

// is_head
static inline int list_is_head(const struct list_head *list, const struct list_head *head){
	return list==head;
}

// is_empty
static inline int list_empty(const struct list_head *head){
	return head->next == head;
}

// entry access macros
// ptr: pointer to struct list_head in the generic struct
// type: the type of generic struct
// member: the variable name of the struct list_head in the generic struct
#define list_entry(ptr, type, member) container_of(ptr,type,member)
#define list_first_entry(ptr, type, member) list_entry((ptr)->next, type, member)
#define list_last_entry(ptr, type, member) list_entry((ptr)->prev, type, member)

#define list_first_entry_or_null(ptr, type, member) ({\
		struct list_head *head__ = (ptr);\
		struct list_head *pos__ = (head__0>next);\
		pos__!=head__ ? list_entry(pos__,type,member) : NULL;\
		})
#define list_next_entry(pos, member) \
	list_entry((pos)->member.next, typeof(*(pos)), member)
#define list_next_entry_circular(pos, head, member) \
	(list_is_last(&(pos)->member, head) ? \
	 list_first_entry(head, typeof(*(pos)), member) : list_next_entry(pos, member))
#define list_prev_entry(pos, member) \
	list_entry((pos)->member.prev, typeof(*(pos)), member)
#define list_prev_entry_circular(pos, head, member) \
	(list_is_first(&(pos)->member, head) ? \
	 list_last_entry(head, typeof(*(pos)), member) : list_prev_entry(pos,member))


// iteration
#define list_for_each(pos, head)\
	for(pos = (head)->next; !list_is_head(pos, (head)); pos=pos->next)
#define list_for_each_continue(pos, head)\
	for(pos = pos->next; !list_is_head(pos, (head)); pos=pos->next)

// count node
static inline int list_count_nodes(struct list_head *head){
	struct list_head *pos;
	int count=0;
	list_for_each(pos, head)
		count++;
	return count;
}

// entry access macros&functions
// pos: type * to use as a loop pointer
// head: the head for the list
// member: the name of the list_head within the struct
#define list_entry_is_head(pos,head,member) \
	(&pos->member == (head))
#define list_for_each_entry(pos, head, member) \
	for(pos=list_first_entry(head, typeof(*(pos)), member); \
			!list_entry_is_head(pos, head, member); \
			pos = list_next_entry(pos, member))


/*----------------------------------------------------------------------------*/

// int list

struct ilist{
	int data;
	struct list_head list;
};

struct list_head *ilist_create(int data){
	struct ilist *n = malloc(sizeof(struct ilist));
	n->data = data;
	return &(n->list);
}

// int 2 list (coordinate)

struct i2list{
	int x;
	int y;
	struct list_head list;
};

struct list_head *i2list_create(int x, int y){
	struct i2list *n = malloc(sizeof(struct i2list));
	n->x = x;
	n->y = y;
	return &(n->list);
};


/*----------------------------------------------------------------------------*/

// heap related things
// min heap, max heap, abs-min heap, min-max heap

#define MM_HEAP_SIZE 1000001
#define MIN_HEAP 0
#define MAX_HEAP 1
#define ABSMIN_HEAP 2

struct mm_heap{
    int *data;
    int size;
};

#define mm_heap_init(name) struct mm_heap name={\
                .data=malloc(sizeof(int)*MM_HEAP_SIZE),\
                .size=0}
#define max_heap_init(name) mm_heap_init(name)
#define min_heap_init(name) mm_heap_init(name)
#define absmin_heap_init(name) mm_heap_init(name)
#define minmax_heap_init(name) mm_heap_init(name)

#define mm_heap_free(name) free((name.data))
#define max_heap_free(name) mm_heap_free(name)
#define min_heap_free(name) mm_heap_free(name)
#define absmin_heap_free(name) mm_heap_free(name)
#define minmax_heap_free(name) mm_heap_free(name);

// return value
// 0: max level
// 1: min level
#define MINMAX_HEAP_MAX_LEVEL 0
#define MINMAX_HEAP_MIN_LEVEL 1
static inline int __minmax_heap_level(struct mm_heap *h){
    int a = h->size;
    int l = 0;
    while(a){
        a>>=1;
        l++;
    }
    return l%2;
}

// minmax heap, add
static inline void minmax_heap_add(struct mm_heap *h, int data){
    int c = ++(h->size);
    int p, gp;
    int l = __minmax_heap_level(h);
    while(1){
        // min level-> make gp min, make p max
        // max level-> make gp max, make p min
        p = c>>1;
        if(p>0 && ((data > h->data[p] && l==MINMAX_HEAP_MIN_LEVEL)
        ||(data < h->data[p] && l==MINMAX_HEAP_MAX_LEVEL))){
            h->data[c] = h->data[p];
            c = p;
            l = !l;
            continue;
        }
        gp = p>>1;
        if(gp>0 && ((data < h->data[gp] && l==MINMAX_HEAP_MIN_LEVEL)
        ||(data > h->data[gp] && l==MINMAX_HEAP_MAX_LEVEL))){
            h->data[c] = h->data[gp];
            c = gp;
            continue;
        }
        h->data[c] = data;
        break;
    }
}

// minmax heap, del min
static int __minmax_heap_del(struct mm_heap *h, int minmax){
    // check if the heap is empty
    if(h->size == 0){
        return 0;
    }
    int r, p, c, gc, temp, l, m;
    int i;
    int idx[6];
    if(minmax == MIN_HEAP){
        // find min, min value is root
        r = h->data[1];
        // last value becomes new root, push down it
        temp = h->data[(h->size)--];
        p = 1;
        l = MINMAX_HEAP_MIN_LEVEL; // root is min level
    }
    else if(minmax == MAX_HEAP){
        // find max, max value is one of 2 children of root
        if(h->size == 1){
            r = h->data[1];
            h->size--;
            return r;
        }
        else if(h->size == 2){
            r = h->data[2];
            h->size--;
            return r;
        }
        else{
            if( h->data[2] > h->data[3]){
                r = h->data[2];
                p = 2;
            }
            else{
                r = h->data[3];
                p = 3;
            }
            temp = h->data[(h->size)--];
            l = MINMAX_HEAP_MAX_LEVEL;
        }
    }
    m=p;
    while(1){
        if((c=p<<1) > h->size){
            h->data[p] = temp;
            break;
        }
        // select a min/max among its children and grandchildren
        // l == MINMAX_MIN_LEVEL -> min
        // l== MINMAX_MAX_LEVEL -> max
        for(i=0;i<2;i++){
            idx[i] = c+i;
        }
        gc = c<<1;
        for(i=0;i<4;i++){
            idx[i+2] = gc + i;
        }
        m = c;
        i = 1;
        while( i<6 && idx[i] <= h->size ){
            if(l==MINMAX_HEAP_MAX_LEVEL){
                if(h->data[m] < h->data[idx[i]]){
                    m = idx[i];
                }
            }
            else if(l==MINMAX_HEAP_MIN_LEVEL){
                if(h->data[m] > h->data[idx[i]]){
                    m = idx[i];
                }
            }
            i++;
        }

        // parant is min/max: already a heap, break
        if(l==MINMAX_HEAP_MAX_LEVEL){
            if(h->data[m] <= temp){
                h->data[p] = temp;
                break;
            }
            else{
                if(m < (c+2)){
                    // child case
                    h->data[p] = h->data[m];
                    h->data[m] = temp;
                    break;
                }
                else{
                    // grandchild case
                    h->data[p] = h->data[m];
                    if(temp < h->data[m>>1]){
                        int t2 = temp;
                        temp = h->data[m>>1];
                        h->data[m>>1] = t2;
                    }
                    p = m;
                    continue;
                }
            }
        }
        else{
            if(h->data[m] >= temp){
                h->data[p] = temp;
                break;
            }
            else{
                if(m < (c+2)){
                    // child case
                    h->data[p] = h->data[m];
                    h->data[m] = temp;
                    break;
                }
                else{
                    // grandchild case
                    h->data[p] = h->data[m];
                    if(temp > h->data[m>>1]){
                        int t2 = temp;
                        temp = h->data[m>>1];
                        h->data[m>>1] = t2;
                    }
                    p = m;
                    continue;
                }
            }
        }
    }
    return r;
}
#define minmax_heap_del_min(h) __minmax_heap_del(h, MIN_HEAP)
#define minmax_heap_del_max(h) __minmax_heap_del(h, MAX_HEAP)


/*  max_heap_add: add a number in the max heap
    m_heap_add: add a number in the max heap
*   h: address of a max heap
*   data: an integer to add
*/
static inline void __mm_heap_add(struct mm_heap *h, int data, int minmax){
    int c = ++(h->size);
    int p = c/2;
    while(p>0){
        if(minmax==MIN_HEAP){
            if(data >= h->data[p]) break;
        }
        else if(minmax==MAX_HEAP){
            if(data <= h->data[p]) break;
        }
        else if(minmax == ABSMIN_HEAP){
            if(abs(data) > abs(h->data[p])) break;
            else if(abs(data) == abs(h->data[p])){
                if(data > h->data[p]) break;
            }
        }

        h->data[c] = h->data[p];
        
        // update c and p
        c = p;
        p = c/2;
    }
    h->data[c] = data;
}
#define min_heap_add(h, data) __mm_heap_add(h, data, MIN_HEAP)
#define max_heap_add(h, data) __mm_heap_add(h, data, MAX_HEAP)
#define absmin_heap_add(h, data) __mm_heap_add(h, data, ABSMIN_HEAP)

/*  max_heap_del: delete a number in the max heap and return it
*   min_heap_del: delete a number in the min heap and return it
*   h: address of a max heap
*/
static inline int __mm_heap_del(struct mm_heap *h, int minmax){
    if(h->size == 0){
        return 0;
    }
    int r = h->data[1];
    int temp = h->data[(h->size)--];

    int p = 1;
    int c = 2;
    while(c <= h->size){
        if(c < h->size){
            // max heap, select bigger child
            if(minmax==1){
                if(h->data[c] < h->data[c+1])
                    c++;
            }
            // min heap, select smaller child
            else if(minmax==0){
                if(h->data[c] > h->data[c+1]){
                    c++;
                }
            }
            // abs min heap
            else if(minmax==2){
                if(abs(h->data[c]) > abs(h->data[c+1])){
                    c++;
                }
                else if(abs(h->data[c] == abs(h->data[c+1]))){
                    if(h->data[c] > h->data[c+1]){
                        c++;
                    }
                }
            }
        }

        // exit condition, parent(temp) is smaller/bigger than child
        if(minmax==1){  // max heap
            if(temp >= h->data[c]){
                break;
            }
        }
        else if(minmax==0){ // min heap
            if(temp <= h->data[c]){
                break;
            }
        }
        else if(minmax==2){ // abs min heap
            if(abs(temp) < abs(h->data[c])){
                break;
            }
            else if( abs(temp) == abs(h->data[c])){
                // same abs value -> negative is smaller
                if(temp < h->data[c]){
                    break;
                }
            }
        }

        // non-exit
        h->data[p] = h->data[c];
        p = c;
        c *= 2;
    }

    h->data[p] = temp;
    return r;
}
#define max_heap_del(h) __mm_heap_del(h, 1)
#define min_heap_del(h) __mm_heap_del(h, 0)
#define absmin_heap_del(h) __mm_heap_del(h, 2)

/*----------------------------------------------------------------------------*/

// resizable circular queue

#define QUEUE_SIZE 10000

struct queue{
    int *data;
    int size;
    int f;
    int r;
};

#define queue_init(name) struct queue name={\
        .data=malloc(sizeof(int)*(QUEUE_SIZE+1)), .size=QUEUE_SIZE,\
        .f=0, .r=0}

#define queue_free(name) free(name.data)

static inline int queue_is_empty(struct queue *q){
    return (q->f==q->r);
}

static inline int queue_is_full(struct queue *q){
    int n = (q->r-q->f);
    return n==1 || n==-q->size;
}

#define queue_len(name) ((name.f-name.r)>=0?\
        (name.f-name.r):(name.f-name.r+name.size+1))

static inline void queue_resize(struct queue *q){
    if(q->f>q->r){
        q->size += QUEUE_SIZE;
        q->data = realloc(q->data, sizeof(int)*(q->size+1));
        return;
    }
    else{
        int *dest = malloc(sizeof(int)*(q->size+QUEUE_SIZE+1));
        int to_end = (q->size+1)-(q->r);
        memcpy(dest, q->data+q->r, sizeof(int)*to_end);
        memcpy(dest + to_end, q->data, sizeof(int)*q->f);
        free(q->data);
        q->data = dest;
        q->r = 0;
        q->f = q->size;
        q->size += QUEUE_SIZE;
    }
    return;
}

static inline void queue_add_last(struct queue *q, int n){
    if(queue_is_full(q)){
        queue_resize(q);
    }

    q->data[q->f] = n;

    if(q->f==q->size){
        q->f=0;
    }
    else{
        q->f++;
    }
}

static inline int queue_del(struct queue *q){
    if(queue_is_empty(q)){
        printf("queue error: queue is empty\n");
        return 0;
    }
    int r = q->data[q->r];
    if(q->r==q->size){
        q->r=0;
    }
    else{
        q->r++;
    }
    return r;
}

static inline void queue_del_all(struct queue *q){
    q->f = 0;
    q->r = 0;
}

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
#define abs(a) ((a)<0?-(a):(a))

//#define down(a) ((a)==0?0:(a)-1)
//#define up(a,n) ((a)==((n)-1)?(n)-1:(a)+1)
/*----------------------------------------------------------------------------*/
/*
// 2 dimensional integer array

struct int2{
    int n;
    int m;
    int *data;
};

#define int2_init(name, nn, mm) struct int2 name={\
        .n=(nn), .m=(mm),\
        .data=calloc((nn)*(mm), sizeof(int))}

#define int2_free(name) free(name.data);

#define __int2_index(s, x, y) ((x)*(s->m) + (y))

static inline void int2_set(struct int2 *s, int data, int x, int y){
    if(!(x<s->n && y<s->m)){
        printf("array error: invalid index\n");
        return;
    }
    s->data[__int2_index(s,x,y)] = data;
}

static inline int int2_get(struct int2 *s, int x, int y){
    if(!(x<s->n && y<s->m)){
        printf("array error: invalid index\n");
        return 0;
    }
    return s->data[__int2_index(s,x,y)];
}

static inline int int2_get_col_sum(struct int2 *s, int col){
    if(col>=s->m){
        printf("array error: invalid index\n");
        return 0;
    }
    int sum=0;
    int stop = (s->m)*(s->n);
    for(int i=col;i<stop;i+=(s->m)){
        sum += s->data[i];
    }
    return sum;
}

static inline int int2_get_row_sum(struct int2 *s, int row){
    if(row>=s->n){
        printf("array error: invalid index\n");
        return 0;
    }
    int sum=0;
    int stop = (row+1)*(s->m);
    for(int i=(row)*(s->m);i<stop;i++){
        sum += s->data[i];
    }
    return sum;
}
*/

/*----------------------------------------------------------------------------*/
/*
// number theory

// euclidean algorithm
// returns greatest common divider of a and b
int gcd(int a, int b){
    int c;
    while((c = a%b) != 0){
        a = b;
        b = c;
    }
    return b;
}

// lcm: returns least common multiple
int lcm(int a, int b){
    return (a*b/gcd(a,b));
}

struct xgcd_r{
    long long gcd;
    // x and y that satisfies a*x + b*y = gcd(a,b)
    long long x;
    long long y;
};
// extended euclidean algorithm
int xgcd(int a, int b, struct xgcd_r* result){
    if( a<0 || b<0) return -1;

    long long x_p = 1;
    long long x = 0;
    long long y_p = 0;
    long long y = 1;
    long long r_p = a;
    long long r = b;
    long long temp, q;

    while(r){
        // calc next step;
        q = r_p/r;

        temp = r;
        r = r_p - r*q;
        r_p = temp;
        temp = x;
        x = x_p - x*q;
        x_p = temp;
        temp = y;
        y = y_p - y*q;
        y_p = temp;
    }

    result->gcd = r_p;
    result->x = x_p;
    result->y = y_p;

    return 0;
}

long long gcrt_2(int M, int N, int x, int y){
    struct xgcd_r s;
    xgcd(M, N, &s);

    long long d = (y-x);
    if(d%s.gcd){
        return -1;
    }
    else{
        long long l = M*N/s.gcd;
        long long r = x + (M * s.x %l) * ((d/s.gcd)%l);
        r = (r%l + l)%l;//least positive congruence
        return r?r:l;
    }
}
*/

/*----------------------------------------------------------------------------*/
#define VISITED_A 1
#define VISITED_B 2
#define NOT_VISITED 0

int main(void){

    int t, a, b;
    int temp, current;
    int i, j;
    char v;
    char *buf_p;
    queue_init(q);
    readbuf_f();
    readd(&t);
    int prev[10000];
    char path[10000];
    char visited[10000];
    char buf[10000];
    int neighbor[5];
    buf[9999] = 0;
    char movement_c[6] = "DDSLR";
    for(i=0;i<t;i++){
        readd(&a);
        readd(&b);

        // bfs
        memset(visited, NOT_VISITED, 10000);
        queue_add_last(&q, a);
        visited[a] = VISITED_A;
        queue_add_last(&q, b);
        visited[b] = VISITED_B;

        while(!queue_is_empty(&q)){
            current = queue_del(&q);
            v = visited[current];

            if(v == VISITED_A){
                neighbor[1] = current<5000?current<<1:(current-5000)<<1;
                neighbor[2] = current==0?9999:current-1;
                neighbor[3] = (current*10 + current/1000)%10000;
                neighbor[4] = (current%10)*1000 + current/10;
            }
            else if(v == VISITED_B){
                neighbor[0] = current>>1;
                neighbor[1] = (current>>1) + 5000;
                neighbor[2] = current==9999?0:current+1;
                neighbor[3] = (current%10)*1000 + current/10;
                neighbor[4] = (current*10 + current/1000)%10000;
            }
            for(j = (v==VISITED_A?1:0);j<5;j++){
                if((current&1) && j<2 && v==VISITED_B){
                    continue;   // search from b, odd number cannot be reached
                                // by D operation
                }
                temp = neighbor[j];
                if(visited[temp] == v){
                    // already visited, from same side(A or B)
                    continue;
                }
                else if(visited[temp] == NOT_VISITED){
                    // newly visited node
                    prev[temp] = current;
                    path[temp] = movement_c[j];
                    visited[temp] = v;
                    queue_add_last(&q, temp);
                }
                else{
                    //search from each side coincides
                    // current, temp are two endpoints of each search
                    if(v == VISITED_B){
                        int t1 = current;
                        current = temp;
                        temp = t1;
                    }
                    // now current = search end from A, temp = search end from B
                    // print A to current
                    buf_p = buf+9999;
                    while(current!=a){
                        *(--buf_p) = path[current];
                        current = prev[current];
                    }
                    writes(buf_p); wp--;
                    // current to temp
                    writec(movement_c[j]);
                    // print temp from B
                    while(temp!=b){
                        writec(path[temp]);
                        temp = prev[temp];
                    }
                    writec('\n');
                    queue_del_all(&q);
                    break;
                }
            }
        }
    }
    writebuf_f();

    queue_free(q);
    return 0;
}