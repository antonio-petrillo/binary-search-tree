CC_C = $(CROSS_TOOL) gcc 

CFLAGS = -g -Wall -Werror -std=c99 -lm

all: main clean test 

%.o: %.c
	$(CC_C) -c $(CFLAGS) $<
	

main: main.o rbtree.o
	$(CC_C) main.o rbtree.o -o main

clean:
	rm *.o 
	
test: main
	./main 10
