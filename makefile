all: a.exe

my_stack_lib.o: my_stack_lib.c my_stack_lib.h
	gcc -c my_stack_lib.c

main.o: main.c my_stack_lib.h
	gcc -c main.c

a.exe: main.o my_stack_lib.o
	gcc main.o my_stack_lib.o
	./a.exe
