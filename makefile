
program=./sample_programs/sample.scaf

main: main.c
	gcc -Wall -Wextra -ggdb -D_DEBUG *.c

run: main.c
	make
	./a.out -n ${program}

db: main.c
	make
	gdb --args ./a.out -n ${program}

prod: main.c
	gcc -Wall -O3 *.c

val: main.c
	make
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all \
		./a.out -n ${program}
