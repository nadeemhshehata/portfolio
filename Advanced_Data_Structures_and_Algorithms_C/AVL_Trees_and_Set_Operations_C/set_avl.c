/*
 ============================================================================
 Name        : set_avl.c
 Author      : Nadeem Hassan
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "set_avl.h"

/**
 * returns the number of elements in the set
 */
int set_size(SET *s) {
    return s->size;
}

/**
 * Returns 1 if set s contains element e; otherwise 0.
 */
int set_contain(SET *s, char *e) {
    AVLNODE *node = avl_search(s->root, e);
    return node != NULL ? 1 : 0;
}

/**
 * Add element e into set s.
 */
void set_add(SET *s, char *e) {
	if (!s || !e || !*e) return;                 // guard bad inputs

	// If the element already exists, do nothing.
	if (set_contain(s, (char *)e)) return;

	// Prepare the RECORD to insert (safe, truncating copy; always NUL-terminated)
	RECORD rec;
	snprintf(rec.name, sizeof rec.name, "%s", e);
	rec.score = 0.0f;

	// Insert into AVL and update size
	avl_insert(&s->root, rec);
	s->size += 1;
}

/**
 * Remove element e from set s.
 */
void set_remove(SET *s, char *e) {
    if (!set_contain(s, e)) return;
    avl_delete(&s->root, e);
    s->size--;
}

/**
 * Clear the set, clearing the underlying AVL tree, and reset fields of s.
 */
void set_clean(SET *s) {
    avl_clean(&s->root);
    s->size = 0;
}
