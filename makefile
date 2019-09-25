
main: main.c
	gcc -Wall -ggdb *.c

run: main.c
	make
	./a.out

db: main.c
	make
	gdb ./a.out

prod: main.c
	gcc -Wall -O3 *.c

val: main.c
	make
	valgrind --leak-check=full --track-origins=yes ./a.out
