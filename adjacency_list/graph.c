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
    // AdjNode* newnode = make_list_node(adj);
    // newnode->next = list.head;
    // list.head = newnode;
    // return list;
    AdjNode* curr = list.head;
    AdjNode* prev = NULL;
    while(curr && curr->value > adj){
        prev = curr;
        curr = curr->next;
    }
    if(!prev){
        if(curr && curr->value > adj){
            AdjNode* newnode = make_list_node(adj);
            newnode->next = list.head;
            list.head = newnode;
        }else if(curr && curr->value < adj){//i do this to avoid the duplicates into the list
            AdjNode* newnode = make_list_node(adj);
            newnode->next = list.head->next;
            list.head->next = newnode;
        }else if(!curr){// if the list is empty
            list.head = make_list_node(adj);
        }//else the value is already present into the list
    }else if(prev && curr){//insert into the middle of the list
        if(curr->value != adj){//if the value is different from
            AdjNode* newnode = make_list_node(adj);
            newnode->next = curr;
            prev->next = newnode;
        }//else the value is already present into the list
    }else{// insert in tail
        AdjNode* newnode = make_list_node(adj);
        prev->next = newnode;
    }
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

void dfs_visit(Graph g, int starting_point, int* color, int* prev, int* t_discover, int* t_end_visit, int* time, edge_info* info){
    color[starting_point] = GREY;
    *time += 1;
    t_discover[starting_point] =  *time;
    AdjNode* iter = g.entries[starting_point].head;
    while(iter){
        if(color[iter->value] == WHITE){
            prev[iter->value] = starting_point;
            dfs_visit(g, iter->value, color, prev, t_discover, t_end_visit, time, info);
        }
        else if(color[iter->value] == GREY)
            info->backward_edge[iter->value] = starting_point;
        else{
            if(t_end_visit[iter->value] < t_discover[starting_point])
                info->transition_edge[iter->value] = starting_point;
            else
                info->forward_edge[iter->value] = starting_point;
        }
        iter = iter->next;
    }
    *time += 1;
    t_end_visit[starting_point] = *time;
    color[starting_point] = BLACK;
    return;
}

void dfs(Graph g){
    int time = 0;
    edge_info info; 
    initialize_edge_info(g, &info);
    int* color = (int*) calloc(g.num_vertex, sizeof(int));
    if(!color)error("error in function dfs");
    int* prev = (int*)calloc(g.num_vertex, sizeof(int)); 
    if(!prev)error("error in function dfs");
    int* t_discover = (int*)calloc(g.num_vertex, sizeof(int));
    if(!t_discover)error("error in function dfs");
    int*t_end_visit = (int*)calloc(g.num_vertex, sizeof(int));
    if(!t_end_visit)error("error in function dfs");
    for(int i=0; i<g.num_vertex; i++){
        prev[i] = inf;
        t_discover[i] = t_end_visit[i] = inf;
    }    
    ////////// TEST /////////////////
    // dfs_visit(g, 0, color, prev, t_discover, t_end_visit, &time);
    // for(int i=0; i<g.num_vertex; i++){
    //     printf("color[%d]: %12d, prev[%d]: %12d, t_discover[%d]: %12d, t_end_visit[%d]: %12d\n", i, color[i], i, prev[i], i, t_discover[i], i, t_end_visit[i]);
    // }
    /////////////////////////////////

    
    for(int i=0; i<g.num_vertex; i++)
        dfs_visit(g, i, color, prev, t_discover, t_end_visit, &time, &info);

    for(int i=0; i<g.num_vertex; i++){
        printf("forward[%d] = %12d, backward[%d] = %12d, transition[%d] = %12d\n", i,  info.forward_edge[i], i, info.backward_edge[i], i, info.transition_edge[i]);
    }

    free(info.backward_edge);
    free(info.forward_edge);
    free(info.transition_edge);
    free(color);
    free(prev);
    free(t_discover);
    free(t_end_visit);
    return;
}

void initialize_edge_info(Graph g, edge_info* info){
    info->backward_edge = (int*) calloc(g.num_vertex, sizeof(int));
    info->forward_edge = (int*) calloc(g.num_vertex, sizeof(int));
    info->transition_edge = (int*) calloc(g.num_vertex, sizeof(int));
    if(!(info->backward_edge && info->forward_edge && info->transition_edge))
        error("error in function initialize_edge_info");
    for(int i=0; i<g.num_vertex; i++){
        info->backward_edge[i] = inf;
        info->forward_edge[i] = inf;
        info->transition_edge[i] = inf;
    }
    return;
}

list_node* make_node_ot(int value){
    list_node* newnode = (list_node*) malloc(sizeof(list_node));
    if(!newnode) error("error in function make_node_ot");
    newnode->next = NULL;
    newnode->value = value;
    return newnode;
}

list_node* insert_node(list_node* head, int value){
    list_node* newnode = make_node_ot(value);
    newnode->next = head;
    return newnode;
}   

list_node* drop_ot(list_node* head){
    list_node* tmp;
    while(head){
        tmp = head;
        head = head->next;
        free(tmp);
    }
    return NULL;
}

list_node* print_ot(list_node* head){
    list_node* iter = head;
    while(iter){
        printf("%d\t", iter->value);
        iter = iter->next;
    }
    puts("");
}


void topologic_ordering(Graph g){
    int flag = 1;
    int* color = (int*) calloc(g.num_vertex, sizeof(int));
    if(!color) error("error in function topologic error");
    list_node* head = NULL;
    for(int i=0; i<g.num_vertex; i++){
        if(color[i] == WHITE) head = ot_dfs(g, i, head, color, &flag);
        if(!flag) break;
    }
    if(flag) print_ot(head);
    else printf("there are not TO on the graph\n");
    head = drop_ot(head);
    free(color);
    return;
}

list_node* ot_dfs(Graph g, int starting_point, list_node* node, int* color, int* flag){
    color[starting_point] = GREY;
    AdjNode* iter = g.entries[starting_point].head;
    while(iter){
        if(!flag) return NULL;
        if(color[iter->value] == WHITE){
            node = ot_dfs(g, iter->value, node, color, flag);
        }else if(color[iter->value] == GREY){
            flag = 0;
            return NULL;
        }
        iter = iter->next;
    }
    node = insert_node(node, starting_point);
    color[starting_point] = BLACK;
    return node;
}