/*
 ============================================================================
 Name        : A10q3.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "algorithm.h"
#include "heap.h"

/* === Helper: Initialize distance and parent arrays === */
static void init_arrays(int order, int *dist, int *parent, int start) {
    for (int i = 0; i < order; i++) {
        dist[i] = INT_MAX;
        parent[i] = -1;
    }
    dist[start] = 0;
}

/* Get weight of edge (from -> to) from adjacency list */
static int get_edge_cost(GRAPH *g, int from, int to) {
    ADJNODE *curr = g->nodes[from]->neighbor;
    while (curr) {
        if (curr->nid == to) return curr->weight;
        curr = curr->next;
    }
    return 0;
}

/* Build an EDGELIST from parent[] in BFS order starting at `start`. */
static EDGELIST *build_tree_bfs(GRAPH *g, int *parent, int start) {
    EDGELIST *tree = new_edgelist();
    int *queue = (int *)malloc(sizeof(int) * g->order);
    int front = 0, back = 0;

    /* BFS over the tree defined by parent[] */
    queue[back++] = start;

    while (front < back) {
        int u = queue[front++];

        /* children v with parent[v] == u, in increasing v */
        for (int v = 0; v < g->order; v++) {
            if (parent[v] == u) {
                int w = get_edge_cost(g, u, v);
                insert_edge_end(tree, u, v, w);
                queue[back++] = v;
            }
        }
    }

    free(queue);
    return tree;
}

/* === Prim’s MST === */
EDGELIST *mst_prim(GRAPH *g, int start) {
    int *dist = (int *)malloc(sizeof(int) * g->order);
    int *parent = (int *)malloc(sizeof(int) * g->order);
    int *visited = (int *)calloc(g->order, sizeof(int));

    init_arrays(g->order, dist, parent, start);

    HEAP *heap = new_heap(g->order);
    for (int i = 0; i < g->order; i++)
        heap_insert(heap, (HEAPDATA){dist[i], i});

    while (heap->size) {
        HEAPDATA min = heap_extract_min(heap);
        int u = min.value;
        if (visited[u]) continue;
        visited[u] = 1;

        ADJNODE *adj = g->nodes[u]->neighbor;
        while (adj) {
            int v = adj->nid;
            int w = adj->weight;
            if (!visited[v] && w < dist[v]) {
                dist[v] = w;
                parent[v] = u;
                int idx = heap_search_value(heap, v);
                if (idx != -1)
                    heap_change_key(heap, idx, w);
            }
            adj = adj->next;
        }
    }

    /* Build MST edges in BFS order over parent[] */
    EDGELIST *tree = build_tree_bfs(g, parent, start);

    free(dist);
    free(parent);
    free(visited);
    heap_clean(&heap);
    return tree;
}

/* === Dijkstra’s Shortest Path Tree === */
EDGELIST *spt_dijkstra(GRAPH *g, int start) {
    int *dist = (int *)malloc(sizeof(int) * g->order);
    int *parent = (int *)malloc(sizeof(int) * g->order);
    int *visited = (int *)calloc(g->order, sizeof(int));

    init_arrays(g->order, dist, parent, start);

    HEAP *heap = new_heap(g->order);
    for (int i = 0; i < g->order; i++)
        heap_insert(heap, (HEAPDATA){dist[i], i});

    while (heap->size) {
        HEAPDATA min = heap_extract_min(heap);
        int u = min.value;
        if (visited[u]) continue;
        visited[u] = 1;

        ADJNODE *adj = g->nodes[u]->neighbor;
        while (adj) {
            int v = adj->nid;
            int w = adj->weight;
            if (!visited[v] && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                parent[v] = u;
                int idx = heap_search_value(heap, v);
                if (idx != -1)
                    heap_change_key(heap, idx, dist[v]);
            }
            adj = adj->next;
        }
    }

    /* Build SPT edges in BFS order over parent[] */
    EDGELIST *tree = build_tree_bfs(g, parent, start);

    free(dist);
    free(parent);
    free(visited);
    heap_clean(&heap);
    return tree;
}

/* === Dijkstra’s Shortest Path from start to end === */
EDGELIST *sp_dijkstra(GRAPH *g, int start, int end) {
    int *dist = (int *)malloc(sizeof(int) * g->order);
    int *parent = (int *)malloc(sizeof(int) * g->order);
    int *visited = (int *)calloc(g->order, sizeof(int));

    init_arrays(g->order, dist, parent, start);

    HEAP *heap = new_heap(g->order);
    for (int i = 0; i < g->order; i++)
        heap_insert(heap, (HEAPDATA){dist[i], i});

    while (heap->size) {
        HEAPDATA min = heap_extract_min(heap);
        int u = min.value;
        if (visited[u]) continue;
        visited[u] = 1;

        if (u == end) break;  /* end’s distance is finalized */

        ADJNODE *adj = g->nodes[u]->neighbor;
        while (adj) {
            int v = adj->nid;
            int w = adj->weight;
            if (!visited[v] && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                parent[v] = u;
                int idx = heap_search_value(heap, v);
                if (idx != -1)
                    heap_change_key(heap, idx, dist[v]);
            }
            adj = adj->next;
        }
    }

    /* Build shortest path from end back to start */
    EDGELIST *path = new_edgelist();
    int v = end;
    while (parent[v] != -1) {
        insert_edge_start(path, parent[v], v, dist[v] - dist[parent[v]]);
        v = parent[v];
    }

    free(dist);
    free(parent);
    free(visited);
    heap_clean(&heap);
    return path;
}
