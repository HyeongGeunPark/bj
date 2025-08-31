// fast io things, linux only
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>

namespace FastIO {
	constexpr int writeBufSz = 10000 * 30;
	char* readBuf;
	char* readCursor;
	char writeBuf[writeBufSz];
	char* writeCursor = writeBuf;
	struct stat st;

	void init() {
		fstat(0, &st);
		readBuf = (char*)mmap(0, st.st_size, PROT_READ, MAP_SHARED, 0, 0);
		readCursor = readBuf;
	}
	void deinit() {
		munmap(readBuf, st.st_size);
	}

	bool is_blank(char c) { return c == ' ' || c == '\n'; }
	bool is_end(char c) { return c == '\0'; }
	bool is_digit(char c) { return c >= '0' && c <= '9'; }
	char read_char() {
		while (is_blank(*readCursor))
			++readCursor;
		return *readCursor++;
	}
	template<typename T>
	// requires std::is_integral_v<T>
	T read_int() {
		T result = 0;
		char current = read_char();
		bool flag = false;
		if (current == '-') {
			flag = true;
			current = read_char();
		}
		result += current - '0';
		while (is_digit(*readCursor)) {
			result = result * 10 + (read_char() - '0');
		}
		return flag ? -result : result;
	}

	void write_char(char c) {
		*writeCursor++ = c;
	}

	template<typename T>
	// requires std::is_integral_v<T>
	void write_int(T n) {
		char buf[30];
		char* bufCursor = buf;
		if (n < 0) {
			*writeCursor++ = '-';
			n = -n;
		}
		do {
			*bufCursor++ = (n % 10) + '0';
			n /= 10;
		}
		while (n);
		do {
			*writeCursor++ = *(--bufCursor);
		} while (bufCursor != buf);
	}

	void flush() {
		write(1, writeBuf, writeCursor - writeBuf);
		writeCursor = writeBuf;
	}


}
