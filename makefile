abr : main.o bst.o queue.o stack.o
	gcc main.o bst.o queue.o stack.o -o abr 

stack.o: stack.c stack.h
	gcc -c -O1 stack.c

queue.o: queue.c queue.h
	gcc -c -O1 queue.c

bst.o: bst.c  queue.c queue.h bst.h
	gcc -c -O1 bst.c

main.o: main.c	bst.h
	gcc -c -O1 main.c	