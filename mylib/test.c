#include<stdio.h>
#include<stdlib.h>

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
#define bmap_get(name, bit) ((name[bit_to_index(bit)]>>((size_t)bit_to_offset(bit))) & ((size_t)1))
#define bmap_set_long(name, bit) name[bit_to_index(bit)] |= BIT_FULL
#define bmap_reset_long(name, bit) name[bit_to_index(bit)] &= 0
#define bmap_set_all(name, bit) memset(name, 0, sizeof(size_t)*bit_to_long(bit))
#define bmap_reset_all(name, bit) memset(name, (char)0xFF, sizeof(size_t)*bit_to_long(bit))
#define bmap_toggle_all(name, bit) for(int i=0;i<(bit_to_long(bit);i++) name[i]^=BIT_FULL

// 2D bitmap

struct bmap2_size{
	int m;
	int len;
};

const static struct bmap2_size bmap2_size_zero = {.m=0, .len=0};

#define __bmap2_size_init(name, a, b) struct bmap2_size name_size = {.m = (b), .len=(a)*(b)}
//#define bmap2_init(name, n, m) __bmap2_size_init(name,n,m);bmap_init(name, name_size.len)
#define bmap2_init(name, n, m) __bmap2_size_init(name,n,m);bmap_init_dynamic(name, name_size.len)
#define bmap2_free(name) free(name);name_size = bmap2_size_zero
#define bmap2_index_to_bit(name,i,j) ((i)*(name_size.m)+(j))
#define bmap2_set(name, i, j) bmap_set(name, bmap2_index_to_bit(name,i,j))
#define bmap2_reset(name, i, j) bmap_reset(name, bmap2_index_to_bit(name,i,j))
#define bmap2_toggle(name, i, j) bmap_toggle(name, bmap2_index_to_bit(name,i,j))
#define bmap2_get(name, i, j) bmap_get(name, bmap2_index_to_bit(name,i,j))
#define bmap2_set_all(name) memset(name, (char)0xFF, ((name_size.len>>3)+1))
#define bmap2_reset_all(name) memset(name, 0, ((name_size.len>>3)+1))
#define bmap2_toggle_all(name) for(int i=0;i<(bit_to_long(name_size.len));i++) name[i]^=BIT_FULL


int main(void){
	// bmap test
	bmap2_init(a, 32, 32);
	bmap2_set(a, 1, 1);
	bmap2_set(a, 16, 1);
	bmap2_set(a, 16, 16);
	printf("int width:%d\n", sizeof(int)*8);
	printf("width:%d\n", sizeof(long)*8);
	printf("index of (16, 16): %d\n", bit_to_index(bmap2_index_to_bit(a,16,16)));
	printf("offset of (16, 16): %d\n", bit_to_offset(bmap2_index_to_bit(a,16,16)));
	printf("index of (2, 0): %d\n", bit_to_index(bmap2_index_to_bit(a,2,0)));
	printf("offset of (2, 0): %d\n", bit_to_offset(bmap2_index_to_bit(a,2,0)));
	printf("size_t: %d\n", sizeof(size_t)*8);
	int i, j;
	for(i=0;i<32;i++){
		for(j=0;j<32;j++){
			printf("%d ", bmap2_get(a,i,j));
		}
		printf("\n");
	}
	

	bmap2_free(a);
	
	return 0;
}

