all: main.c
	gcc main.c -o main.exe

debug: main.c
	gcc main.c -o debug -g
	gdb debug -tui

clean:
	rm debug
	rm main.exe
