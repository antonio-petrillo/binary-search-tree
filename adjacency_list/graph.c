#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "graph.h"
#include "queue.h"

#define inf INT_MAX

void error(char* message){
    printf("%s\n", message);
    exit(EXIT_FAILURE);
}

AdjNode* make_list_node(int adj){
    AdjNode* newnode = (AdjNode*)malloc(sizeof(AdjNode));
    if(!newnode) error("error in function: AdjNode* make_list_node(int adj)");
    newnode->next = NULL;
    if(!newnode) error("error in function: AdjNode* make_list_node(int adj)");
    newnode->next = NULL;
    newnode->value = adj;
    return newnode;
}

AdjList insert(AdjList list, int adj){
    AdjNode* newnode = make_list_node(adj);
    newnode->next = list.head;
    list.head = newnode;
    return list;
}

Graph makegraph(Graph g, int num_vertex, int num_egde, Edge edge_to_add[]){
    g.entries = (AdjList*) calloc(num_vertex, sizeof(AdjList));
    g.num_vertex = num_vertex;
    for(int i=0; i<num_vertex; i++) g.entries[i].head = NULL;
    g.num_edge = num_egde;
    for(int i=0; i<num_egde; i++) g.entries[edge_to_add[i].src] = insert(g.entries[edge_to_add[i].src], edge_to_add[i].dest);
    return g;
}

void print_Graph(Graph g){
    for(int i=0; i<g.num_vertex; i++){
        printf("adjacency list of %d: ", i);
        print_list(g.entries[i]);
        puts("");
    }
}

void print_list(AdjList l){
    AdjNode* node = l.head;
    while(node){
        printf("%4d", node->value);
        node = node->next;
    }
}

AdjList droplist(AdjList list){
    AdjNode* tmp = list.head;
    while (tmp){
        list.head = list.head->next;
        free(tmp);
        tmp = list.head;
    }
    return list;
}

Graph drop(Graph g){
    for(int i=0; i<g.num_vertex; i++) g.entries[i] = droplist(g.entries[i]);
    free(g.entries);
    g.num_edge = g.num_vertex = 0;
    return g;
}

int* bfs(Graph g, int starting_point){
    int* color = (int*) calloc(g.num_vertex, sizeof(int));
    if(!color)error("error in bfs function");
    int* prev = (int*) calloc(g.num_vertex, sizeof(int));
    if(!prev)error("error in bfs function");
    for(int i=0; i<g.num_vertex; i++) prev[i] = inf; 
    Queue q = make_queue(q);
    enqueue(&q, starting_point);
    while (q.head != NULL){
        //status(q);
        int v = dequeue(&q);
        if(v != inf){
            AdjNode* iter = g.entries[v].head;
            while(iter){
                if(color[iter->value] == WHITE){
                    prev[iter->value] = v;
                    color[iter->value] = GREY;
                    //printf("node: %4d, color: %d, prev: %d\n", iter->value, color[iter->value], prev[iter->value]);
                    enqueue(&q, iter->value);
                }
                iter = iter->next;
            }
            color[v] = BLACK;
        }
        //status(q);
        //printf("la coda e': %d\n", (q.head == NULL)? 1 : 0);
    }
    free(color);
    return prev;
}

void print_min_path(Graph g, int src, int dest){
    int* prev = bfs(g, src);
    if(prev[dest] != inf){
        genpath(src, dest, prev);
        puts("");
    }else printf("that path doesn't exist!\n");
    free(prev);
}

void genpath(int src, int dest, int* prev){
    if(src == dest)
        printf("%d\t", src);
    else{
        genpath(src, prev[dest], prev);
        printf("%d\t", dest);
    }
}

Graph makegraph_from_file(char* filename){
    FILE* fp = fopen(filename, "r");
    int num_v, src, dest;
    fscanf(fp, "%d", &num_v);
    Graph g;
    g.num_vertex = num_v;
    g.num_edge = 0;
    g.entries = (AdjList*) calloc(num_v, sizeof(AdjList));
    for(int i=0; i<num_v; i++) g.entries[i].head = NULL;
    while(fscanf(fp, "%d%d", &src, &dest) != EOF){
        g.entries[src] = insert(g.entries[src], dest);
        g.num_edge += 1;
    }
    fclose(fp);
    return g;
}