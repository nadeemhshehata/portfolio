/*
 ============================================================================
 Name        : edgelist.h
 Author      : Nadeem Hassan
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */
#ifndef SRC_EDGELIST_H_
#define SRC_EDGELIST_H_

#include <stdio.h>
#include <stdlib.h>

/*
 * Define structure EDGE if linked list node
 * from  - index of source vertex
 * to - index of destination vertex
 * weight - weight of the edge
 * next  - pointer to the next edge node
*/
typedef struct edgenode {
  int from;
  int to;
  int weight;
  struct edgenode *next;
} EDGENODE;

/*
 * Define structure EDGELIST of edge list graph DS
 * size  - number of edges
 * start - pointer to the first edge node
 * end   - pointer to the last edge node
*/
typedef struct edgelist {
  int size;
  EDGENODE *start;
  EDGENODE *end;
} EDGELIST;


/* Create and return a new edge list graph*/
EDGELIST *new_edgelist();

/* Add a new edge at the start of the linked list of edges*/
void insert_edge_start(EDGELIST *g, int from, int to, int weight);

/* Add an new edge at the end of the linked list of edges */
void insert_edge_end(EDGELIST *g, int from, int to, int weight);

/* Delete edge (from to) from the edgelist */
void delete_edge(EDGELIST *g, int from, int to);

/* Get the weight of the graph */
int weight_edgelist(EDGELIST *g);

/* clean the graph by free all dynamically allocated memory*/
void clean_edgelist(EDGELIST **gp);

/* Display edge list graph*/
void display_edgelist(EDGELIST *g);

#endif /* SRC_EDGELIST_H_ */
