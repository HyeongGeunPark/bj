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

bool mem[2001][2001];
bool checked[2001][2001];
int arr[2001];

char check(int s, int e) {
	if (!checked[s][e]) {
		// not evaluated yet
		if (e - s < 2) {
			mem[s][e] = (arr[s] == arr[e]);
		}
		else {
			mem[s][e] = (arr[s] == arr[e]) && check(s + 1, e - 1);
		}
		checked[s][e] = true;
	}
	return mem[s][e];
}

int main() {

	int n = fio::readd<int>();
	for (int i = 1; i <= n; ++i) {
		arr[i] = fio::readd<int>();
	}

	int m = fio::readd<int>();
	for (int i = 0; i < m; ++i) {
		int s, e;
		s = fio::readd<int>();
		e = fio::readd<int>();
		fio::writec(check(s, e) ? '1' : '0');
		fio::writec('\n'); 
	} 
}