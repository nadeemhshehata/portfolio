/*
 ============================================================================
 Name        : graph.h
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */
#ifndef SRC_GRAPH_H_
#define SRC_GRAPH_H_

#define INFINITY 999999
#include <stdio.h>
#include <stdlib.h>

/*
 * structure of adjacent linked list node
 * nid    -  to node id
 * weight -  edge weight
 * next   -  pointer to next adjnode
*/
typedef struct adjnode  {
    int nid;
    int weight;
    struct adjnode *next;
} ADJNODE;

/*
 * structure of graph vertex node
 * nid   - graph vertex node id
 * name  - name or data of the node
 * neighbor - pointer to the linked list of neighbors
*/
typedef struct gnode  {
    int nid;
    char name[10];
    ADJNODE *neighbor;
} GNODE;

/*
 * structure of adjacent list graph
 * order - number of nodes
 * size - number of edges
 * nodes - array of GNODE pointers
*/
typedef struct graph {
    int order;
    int size;
  GNODE **nodes;
} GRAPH;

/* create and return a new adjacent list graph of order n */
GRAPH *new_graph(int n);

/* Add edge (from, to, weight) to a graph. If edge (from, to) exists, update its weight by the new weight,
 * This indicates that if (from, to) does not exist, the new edge will be added to the end of the linked list.
*/
void insert_edge_graph(GRAPH *g, int from, int to, int weight);

/* Delete edge (from, to)*/
void delete_edge_graph(GRAPH *g, int from, int to);

/* Get and return the weight of edge (from, to) if exists, otherwise return INFINITY*/
int get_edge_weight(GRAPH *g, int from, int to);

/* Travere graph nodes in breadth-first-order using auxiliary queue */
void traverse_bforder(GRAPH *g, int start);

/* Traverse graph in depth-first-order using auxiliary stack */
void traverse_dforder(GRAPH *g, int start);

/* Display the graph*/
void display_graph(GRAPH *g);

/* Clean the graph by free all dynamically allocated memory*/
void clean_graph(GRAPH **gp);
#endif /* SRC_GRAPH_H_ */
