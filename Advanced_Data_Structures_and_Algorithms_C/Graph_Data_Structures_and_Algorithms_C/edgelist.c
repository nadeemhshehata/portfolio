/*
 ============================================================================
 Name        : edgelist.c
 Author      : Nadeem Hassan
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "edgelist.h"

EDGELIST *new_edgelist() {
    EDGELIST *g = (EDGELIST *)malloc(sizeof(EDGELIST));
    g->size = 0;
    g->start = NULL;
    g->end = NULL;
    return g;
}

void insert_edge_start(EDGELIST *g, int from, int to, int weight) {
    EDGENODE *new_node = (EDGENODE *)malloc(sizeof(EDGENODE));
    new_node->from = from;
    new_node->to = to;
    new_node->weight = weight;
    new_node->next = g->start;
    g->start = new_node;
    if (g->end == NULL) {
        g->end = new_node;
    }
    g->size++;
}

void insert_edge_end(EDGELIST *g, int from, int to, int weight) {
    EDGENODE *new_node = (EDGENODE *)malloc(sizeof(EDGENODE));
    new_node->from = from;
    new_node->to = to;
    new_node->weight = weight;
    new_node->next = NULL;

    if (g->start == NULL) {
        g->start = new_node;
        g->end = new_node;
    } else {
        g->end->next = new_node;
        g->end = new_node;
    }
    g->size++;
}

void delete_edge(EDGELIST *g, int from, int to) {
    EDGENODE *prev = NULL;
    EDGENODE *curr = g->start;

    while (curr != NULL) {
        if (curr->from == from && curr->to == to) {
            if (prev == NULL) {
                g->start = curr->next;
            } else {
                prev->next = curr->next;
            }

            if (curr == g->end) {
                g->end = prev;
            }

            free(curr);
            g->size--;
            return;
        }
        prev = curr;
        curr = curr->next;
    }
}

int weight_edgelist(EDGELIST *g) {
    int total = 0;
    EDGENODE *curr = g->start;
    while (curr != NULL) {
        total += curr->weight;
        curr = curr->next;
    }
    return total;
}

void clean_edgelist(EDGELIST **gp) {
    if (*gp == NULL) return;
    EDGENODE *curr = (*gp)->start;
    while (curr != NULL) {
        EDGENODE *temp = curr;
        curr = curr->next;
        free(temp);
    }
    free(*gp);
    *gp = NULL;
}

void display_edgelist(EDGELIST *g) {
    printf("size %d (from to weight)", g->size);
    EDGENODE *curr = g->start;
    while (curr != NULL) {
        printf(" (%d %d %d)", curr->from, curr->to, curr->weight);
        curr = curr->next;
    }
}
