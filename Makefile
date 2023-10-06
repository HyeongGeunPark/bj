src=$(wildcard *.c)
obj=$(patsubst %.c,%.o,$(src))
detected_obj=$(wildcard *.o)
out=$(patsubst %.c,%.out,$(src))
detected_out=$(wildcard *.out)
temp=$(wildcard *~)
debug=debug.out
mainout=main.out

# for windows powershell compatibility
ifeq ($(OS),Windows_NT)
RM:=del /s
out:=$(patsubst %.c,%.exe,$(src))
detected_out:=$(wildcard *.exe)
debug:=debug.exe
mainout:=main.exe
endif



all: $(mainout)

%.out:%.c
	gcc $< -o $@

%.exe:%.c
	gcc $< -o $@

debug:$(debug) FORCE 
	gdb $(debug) -tui
$(debug): main.c
	gcc main.c -o $(debug) -g
FORCE:

test: $(mainout)
ifeq ($(OS),Windows_NT)
	$(mainout) <test.txt
else
	./$(mainout) <test.txt
endif

run: $(mainout)
ifeq ($(OS),Windows_NT)
	$(mainout)
else
	./$(mainout)
endif

clean:
	$(RM) $(detected_out)
	$(RM) $(temp)
