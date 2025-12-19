/*
 ============================================================================
 Name        : tree.c
 Author      : Nadeem Hassan
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "queue_stack.h"

/* ---------- helpers ---------- */

TNODE *tree_node(char val) {
    TNODE *p = (TNODE *) malloc(sizeof(TNODE));
    if (p) {
        p->data = val;
        p->left = NULL;
        p->right = NULL;
    }
    return p;
}

static void clean_tree_rec(TNODE *root) {
    if (root) {
        clean_tree_rec(root->left);
        clean_tree_rec(root->right);
        free(root);
    }
}

void clean_tree(TNODE **rootp) {
    if (rootp && *rootp) {
        clean_tree_rec(*rootp);
        *rootp = NULL;
    }
}

/* Level-order insertion: first available spot, left to right */
void insert_tree(TNODE **rootp, char val) {
    if (rootp == NULL) return;

    TNODE *newnode = tree_node(val);
    if (newnode == NULL) return;

    if (*rootp == NULL) {
        *rootp = newnode;
        return;
    }

    QUEUE q = {0};
    enqueue(&q, *rootp);

    while (q.front) {
        TNODE *cur = (TNODE *) dequeue(&q);
        if (cur->left == NULL) {
            cur->left = newnode;
            clean_queue(&q);
            return;
        } else if (cur->right == NULL) {
            cur->right = newnode;
            clean_queue(&q);
            return;
        } else {
            enqueue(&q, cur->left);
            enqueue(&q, cur->right);
        }
    }
    /* Shouldn't reach here */
    clean_queue(&q);
    /* Fallback (attach as left child of root) */
    if (!(*rootp)->left) (*rootp)->left = newnode;
    else if (!(*rootp)->right) (*rootp)->right = newnode;
    else free(newnode);
}

/* ---------- properties & traversals ---------- */

static void props_rec(TNODE *root, int *count, int *height) {
    if (root == NULL) {
        *height = 0;
        return;
    }
    int lh = 0, rh = 0;
    (*count)++;
    props_rec(root->left, count, &lh);
    props_rec(root->right, count, &rh);
    *height = (lh > rh ? lh : rh) + 1;
}

TPROPS tree_property(TNODE *root) {
    TPROPS p = {0, 0};
    int cnt = 0, h = 0;
    props_rec(root, &cnt, &h);
    p.order = cnt;
    p.height = h;
    return p;
}

void preorder(TNODE *root) {
    if (root == NULL) return;
    printf("%c ", root->data);
    preorder(root->left);
    preorder(root->right);
}

void inorder(TNODE *root) {
    if (root == NULL) return;
    inorder(root->left);
    printf("%c ", root->data);
    inorder(root->right);
}

void postorder(TNODE *root) {
    if (root == NULL) return;
    postorder(root->left);
    postorder(root->right);
    printf("%c ", root->data);
}

/* ---------- BFS order & search using queue ---------- */

void bforder(TNODE *root) {
    if (root == NULL) return;

    QUEUE q = {0};
    enqueue(&q, root);
    while (q.front) {
        TNODE *cur = (TNODE *) dequeue(&q);
        printf("%c ", cur->data);
        if (cur->left) enqueue(&q, cur->left);
        if (cur->right) enqueue(&q, cur->right);
    }
    clean_queue(&q);
}

TNODE *bfs(TNODE *root, char key) {
    if (root == NULL) return NULL;

    QUEUE q = {0};
    enqueue(&q, root);
    while (q.front) {
        TNODE *cur = (TNODE *) dequeue(&q);
        if (cur->data == key) {
            clean_queue(&q);
            return cur;
        }
        if (cur->left) enqueue(&q, cur->left);
        if (cur->right) enqueue(&q, cur->right);
    }
    clean_queue(&q);
    return NULL;
}

/* ---------- DFS (preorder) using stack ---------- */

TNODE *dfs(TNODE *root, char key) {
    if (root == NULL) return NULL;

    STACK st = {0};
    push(&st, root);
    while (st.top) {
        TNODE *cur = (TNODE *) pop(&st);
        if (cur->data == key) {
            clean_stack(&st);
            return cur;
        }
        /* push right first so left is processed first (preorder) */
        if (cur->right) push(&st, cur->right);
        if (cur->left) push(&st, cur->left);
    }
    clean_stack(&st);
    return NULL;
}

