avl : main.o avl.o 
	gcc main.o avl.o -o avl 

avl.o: avl.c  avl.h
	gcc -c -O1 avl.c

main.o: main.c	avl.h
	gcc -c -O1 main.c	