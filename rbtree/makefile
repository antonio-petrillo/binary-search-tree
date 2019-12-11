rbtree: main.o rbtree.o queue.o
	gcc -O3 main.o rbtree.o queue.o -o rbtree

queue.o: queue.c queue.h
	gcc -O3 queue.c -c

rbtree.o: rbtree.c rbtree.h queue.c queue.h
	gcc -O3 rbtree.c -c

main.o: main.c rbtree.h
	gcc -O3 main.c -c