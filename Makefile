CFLAGS := -Wall -Werror -pedantic -std=c11 -I/usr/local/include/libfreenect
LDFLAGS := -L/usr/local/lib -lfreenect
CC := clang

kkcd:

clean:
	rm -rf kkcd kkcd.o
