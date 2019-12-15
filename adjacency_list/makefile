graph: main.o graph.o queue.o 
	gcc main.o graph.o queue.o -o graph && gcc graph_generator.c -o graph_generator

queue.o: queue.c queue.h
	gcc -c -O3 queue.c 

graph.o: graph.c graph.h queue.h queue.c
	gcc -O3 -c graph.c 

main.o: main.c graph.h
	gcc -O3 main.c -c