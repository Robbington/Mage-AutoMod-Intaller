CFLAGS=-Wall -g

all:
	gcc MMB.c -o MMB
	./MMB

memtest:
	gcc -g MMB.c -o MMB
	valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 --track-fds=yes ./MMB 2> val.log
clean:
	rm -rf MMB
