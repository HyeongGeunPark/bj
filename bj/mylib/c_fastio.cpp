// linux only
#include<sys/mman.h>
#include<sys/stat.h>

char* input_pointer;

template<typename T> // requires std::signed_integral<T> /*C++20~*/
inline T readd(void) {
	T ret = 0; char c = *input_pointer++; flag = 0;
	if (c == '-') c = *input_pointer++, flag = 1;
	while (c & 16) { // only usable when inputs are numbers or space
		// c&16 is true when c is
		// 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, :, ;, <, =, >, ?
		// p, q, ..., z, {, |, }, ~
		ret = 10 * ret + (c & 15);
		c = *input_pointer++;
	}
	return flag ? -ret : ret; 
}
inline char* mymmap() {
	struct stat st; fstat(0, &st);
	return (char*)mmap(0, st.st_size, PROT_READ, MAP_SHARED, 0, 0);
}

/*
int main(){
	input_pointer = mymmap();
	...
	int a = readd();
} 
*/

