// linux only
#include<bits/stdc++.h>
#include<unistd.h>
#include<sys/syscall.h>

#include<concepts>


namespace fio {
	const int BSIZE = 1 << 22;
	char buffer[BSIZE];
	auto p = buffer + BSIZE;

	inline char readc() {
		if (p == buffer + BSIZE) {
			syscall(0x00, 0, buffer, BSIZE);
			p = buffer;
		}
		return *p++;
	}

	template<typename T> requires std::integral<T>
	T readd() {
		char c = readc();
		while (c < '-') {
			c = readc();
		}
		T r = 0;
		while (c >= '-') {
			r = r * 10 + c - '0';
			c = readc();
		}
		return r; 
	}

	unsigned char outbuf[BSIZE];
	unsigned char* outp = outbuf;

	void flush() {
		syscall(0x01, 1, outbuf, outp - outbuf);
		outp = outbuf;
	}
	
	inline void writec(char c) {
		if (outp == outbuf + BSIZE) {
			flush();
		}
		*outp++ = c;
	}

} // namespace fio


/*
int main(){
	input_pointer = mymmap();
	...
	int a;
	readd(&a);
} 
*/

