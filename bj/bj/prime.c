/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
// input 2 number, and this program will print prime numbers between them


/*----------------------------------------------------------------------------*/

// buffered input output related things
#define BUF_SIZE 10000   // size of input, output buffer for buffered IO functions
#define STDOUT_FD 1
#define STDIN_FD 0

//check: all bulk read functions(reads, readu) removes delimeter automatically
//      all bulk write functions(writes, writeu) adds some end character(currently \n)

char BUF[BUF_SIZE+1];
char *p = BUF;  // input buffer handling pointer
char *pl = NULL;   // input buffer last pointer(be careful that the value of this pointer is  an invalid value)
char WBUF[BUF_SIZE+1];
char *wp = WBUF;


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
// write a \0 padded string
// automatically adds '\n' to the end
// do not check string size, so be careful with segfault
static inline void writes(char *c){
    while(*c != 0 ){
        writec(*c++);
    }
    writec('\n');
}
// convert an unsigned decimal to character string and write it
// automatically adds '\n' to the end
#define WUD_SIZE 30
static inline void writeud(int d){
    int i;
    char buf[WUD_SIZE];
    char *bp = buf + WUD_SIZE - 1;
    while(d>0){
        i=d%10;
        *bp-- = i + '0';
        d/=10;
    }
    while(bp < (buf + WUD_SIZE - 1)){
        writec(*(++bp));
    }
    writec('\n');
}
// read from stdin to BUF manually
// this function should be called at the first
static inline void readbuf_f(void){
    p = BUF;
    int r_return = read(STDIN_FD, BUF, BUF_SIZE);
    if(r_return<0) return;
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
// read an unsiged integer from buffered input
static inline int readud(int *up){
    char ibuf[3];
    char c;
    *up = 0;
    while(!isnum(c=readc()));
    do{
        *up = ((*up)*10) + (c-'0');
    }while(isnum(c=readc()));
    return *up;
}
// read a string, consisted only of alphabets, from buffered input
static inline void reads(char *dest){
    int i=0;
    char c;
    while(!isalp(c=readc()));
    do{
        *dest++ = c;
    }while(isalp(c=readc()));
    *dest=0;
}

/*----------------------------------------------------------------------------*/

// bitmap related things

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
#define bmap_set_all_long(name, bit) name[bit_to_index(bit)] |= 0xffffffff
#define bmap_reset_all_long(name, bit) name[bit_to_index(bit)] &= 0


/*----------------------------------------------------------------------------*/
int main()
{
    int n, m;
    readbuf_f();
    readud(&n);
    readud(&m);
    //printf("%d %d", (int)stdin, (int)stdout);
    bmap_init_dynamic(arr1, m+1);

    bmap_set(arr1, 1);
    bmap_reset(arr1, 2);
    
    int i;
    int j;
    int r = sqrt(m);
    for(i=2;i<=r;i++){
        if(bmap_get(arr1, i)==1) continue;
        for(j=2*i;j<=m;j+=i){
            bmap_set(arr1, j);
        }
    }
    
    for(i=n;i<=m;i++){
        if(bmap_get(arr1, i) == 0){
            writeud(i);
        }
    }
    writebuf_f();
    bmap_free_dynamic(arr1);
    
    return 0;
}
