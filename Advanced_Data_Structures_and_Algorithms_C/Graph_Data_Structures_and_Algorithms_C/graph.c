/*
 ============================================================================
 Name        : graph.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"
#include "queue_stack.h"

GRAPH *new_graph(int n) {
    GRAPH *g = (GRAPH *)malloc(sizeof(GRAPH));
    g->order = n;
    g->size = 0;
    g->nodes = (GNODE **)malloc(sizeof(GNODE *) * n);
    for (int i = 0; i < n; i++) {
        g->nodes[i] = (GNODE *)malloc(sizeof(GNODE));
        g->nodes[i]->nid = i;
        g->nodes[i]->name[0] = '\0';
        g->nodes[i]->neighbor = NULL;
    }
    return g;
}

void insert_edge_graph(GRAPH *g, int from, int to, int weight) {
    if (!g || from >= g->order || to >= g->order) return;

    ADJNODE *curr = g->nodes[from]->neighbor;
    while (curr) {
        if (curr->nid == to) {
            curr->weight = weight;
            return;
        }
        curr = curr->next;
    }

    ADJNODE *new_node = (ADJNODE *)malloc(sizeof(ADJNODE));
    new_node->nid = to;
    new_node->weight = weight;
    new_node->next = NULL;

    curr = g->nodes[from]->neighbor;
    if (!curr) {
        g->nodes[from]->neighbor = new_node;
    } else {
        while (curr->next) curr = curr->next;
        curr->next = new_node;
    }

    g->size++;
}

void delete_edge_graph(GRAPH *g, int from, int to) {
    if (!g || from >= g->order || to >= g->order) return;

    ADJNODE *curr = g->nodes[from]->neighbor;
    ADJNODE *prev = NULL;

    while (curr) {
        if (curr->nid == to) {
            if (prev) prev->next = curr->next;
            else g->nodes[from]->neighbor = curr->next;
            free(curr);
            g->size--;
            return;
        }
        prev = curr;
        curr = curr->next;
    }
}

int get_edge_weight(GRAPH *g, int from, int to) {
    if (!g || from >= g->order || to >= g->order) return INFINITY;

    ADJNODE *curr = g->nodes[from]->neighbor;
    while (curr) {
        if (curr->nid == to) return curr->weight;
        curr = curr->next;
    }
    return INFINITY;
}

void traverse_bforder(GRAPH *g, int start) {
    if (!g || start >= g->order) return;

    int *visited = (int *)calloc(g->order, sizeof(int));
    QUEUE q = {NULL, NULL};

    enqueue(&q, g->nodes[start]);
    visited[start] = 1;

    while (q.front) {
        GNODE *v = (GNODE *)dequeue(&q);
        printf("(%d %s) ", v->nid, v->name);

        ADJNODE *adj = v->neighbor;
        while (adj) {
            if (!visited[adj->nid]) {
                enqueue(&q, g->nodes[adj->nid]);
                visited[adj->nid] = 1;
            }
            adj = adj->next;
        }
    }

    free(visited);
    clean_queue(&q);
}

void traverse_dforder(GRAPH *g, int start) {
    if (!g || start >= g->order) return;

    int *visited = (int *)calloc(g->order, sizeof(int));
    STACK s = {NULL};

    push(&s, g->nodes[start]);

    while (s.top) {
        GNODE *v = (GNODE *)pop(&s);
        if (!visited[v->nid]) {
            printf("(%d %s) ", v->nid, v->name);
            visited[v->nid] = 1;

            ADJNODE *adj = v->neighbor;
            while (adj) {
                if (!visited[adj->nid]) {
                    push(&s, g->nodes[adj->nid]);
                }
                adj = adj->next;
            }
        }
    }

    free(visited);
    clean_stack(&s);
}

void display_graph(GRAPH *g) {
    if (!g) return;

    printf("order %d size %d (from to weight) ", g->order, g->size);
    for (int i = 0; i < g->order; i++) {
        ADJNODE *adj = g->nodes[i]->neighbor;
        while (adj) {
            printf("(%d %d %d) ", i, adj->nid, adj->weight);
            adj = adj->next;
        }
    }
}

void clean_graph(GRAPH **gp) {
    if (!gp || !*gp) return;

    GRAPH *g = *gp;
    for (int i = 0; i < g->order; i++) {
        ADJNODE *curr = g->nodes[i]->neighbor;
        while (curr) {
            ADJNODE *temp = curr;
            curr = curr->next;
            free(temp);
        }
        free(g->nodes[i]);
    }
    free(g->nodes);
    free(g);
    *gp = NULL;
}
