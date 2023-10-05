src=$(wildcard *.c)
obj=$(patsubst %.c,%.o,$(src))
detected_obj=$(wildcard *.o)
out=$(patsubst %.c,%.out,$(src))
detected_out=$(wildcard *.out)
temp=$(wildcard *~)
debug=debug.out

# for windows powershell compatibility
ifeq ($(OS),Windows_NT)
RM:=del /s
out:=$(patsubst %.c,%.exe,$(src))
detected_out:=$(wildcard *.exe)
debug:=debug.exe
endif



all: $(out)

%.out:%.c
	gcc $< -o $@

%.exe:%.c
	gcc $< -o $@

debug:$(debug) FORCE 
	gdb $(debug) -tui
$(debug): main.c
	gcc main.c -o $(debug) -g
FORCE:

clean:
	$(RM) $(detected_out)
	$(RM) $(temp)
