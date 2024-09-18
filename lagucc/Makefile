CFLAGS=-std=c11 -g -static

lagucc: lagucc.c

test: lagucc
		./test.sh

clean:
		rm -f lagucc *.o *~ tmp*

.PHONY: test clean
