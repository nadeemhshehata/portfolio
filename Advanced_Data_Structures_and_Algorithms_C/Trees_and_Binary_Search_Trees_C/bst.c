/*
 ============================================================================
 Name        : bst.c
 Author      : Nadeem Hassan
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst.h"

/* Create a new node */
BSTNODE *bst_node(RECORD data) {
    BSTNODE *p = (BSTNODE *) malloc(sizeof(BSTNODE));
    if (p) {
        p->data = data;
        p->left = NULL;
        p->right = NULL;
    }
    return p;
}

/* Internal helper: recursive clean */
static void bst_clean_rec(BSTNODE *root) {
    if (root) {
        bst_clean_rec(root->left);
        bst_clean_rec(root->right);
        free(root);
    }
}

void bst_clean(BSTNODE **rootp) {
    if (rootp && *rootp) {
        bst_clean_rec(*rootp);
        *rootp = NULL;
    }
}

/* Search by name (string key) */
BSTNODE *bst_search(BSTNODE *root, char *key) {
    BSTNODE *p = root;
    while (p) {
        int cmp = strcmp(key, p->data.name);
        if (cmp == 0) return p;
        else if (cmp < 0) p = p->left;
        else p = p->right;
    }
    return NULL;
}

/* Insert iteratively by name key */
void bst_insert(BSTNODE **rootp, RECORD data) {
    if (rootp == NULL) return;

    if (*rootp == NULL) {
        *rootp = bst_node(data);
        return;
    }

    BSTNODE *parent = NULL, *cur = *rootp;
    int last_cmp = 0;
    while (cur) {
        parent = cur;
        last_cmp = strcmp(data.name, cur->data.name);
        if (last_cmp == 0) {
            /* Update score on duplicate key */
            cur->data.score = data.score;
            return;
        } else if (last_cmp < 0) {
            cur = cur->left;
        } else {
            cur = cur->right;
        }
    }

    BSTNODE *nn = bst_node(data);
    if (!nn) return;
    if (last_cmp < 0) parent->left = nn;
    else parent->right = nn;
}

/* Extract the smallest node from a subtree, return that node
   and remove it from the tree. The returned node has left/right = NULL. */
BSTNODE *extract_smallest_node(BSTNODE **rootp) {
    if (rootp == NULL || *rootp == NULL) return NULL;

    BSTNODE *parent = NULL;
    BSTNODE *cur = *rootp;

    while (cur->left) {
        parent = cur;
        cur = cur->left;
    }

    /* cur is the smallest */
    if (parent == NULL) {
        /* smallest is the root of this subtree */
        *rootp = cur->right;
    } else {
        parent->left = cur->right;
    }
    cur->left = NULL;
    cur->right = NULL;
    return cur;
}

/* Delete by key using standard BST deletion */
void bst_delete(BSTNODE **rootp, char *key) {
    if (rootp == NULL || *rootp == NULL) return;

    BSTNODE *parent = NULL;
    BSTNODE *cur = *rootp;
    int cmp = 0;

    /* find node */
    while (cur && (cmp = strcmp(key, cur->data.name)) != 0) {
        parent = cur;
        if (cmp < 0) cur = cur->left;
        else cur = cur->right;
    }
    if (cur == NULL) return; /* not found */

    /* case 1: node with 0 or 1 child */
    if (cur->left == NULL || cur->right == NULL) {
        BSTNODE *child = cur->left ? cur->left : cur->right;

        if (parent == NULL) {
            /* deleting root */
            *rootp = child;
        } else if (parent->left == cur) {
            parent->left = child;
        } else {
            parent->right = child;
        }
        free(cur);
        return;
    }

    /* case 2: node with 2 children -> replace with inorder successor */
    BSTNODE *succ = extract_smallest_node(&(cur->right));
    /* succ has no children now */
    succ->left = cur->left;
    succ->right = cur->right;

    if (parent == NULL) *rootp = succ;
    else if (parent->left == cur) parent->left = succ;
    else parent->right = succ;

    free(cur);
}
