/*
--------------------------------------------------
Project: a5q1
File:    myrecord_sllist.c
Author:  Nadeem Hassan
Version: 2025-10-20
--------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "myrecord_sllist.h"

NODE *sll_search(SLL *sllp, char *name){

	if (sllp == NULL || sllp->start == NULL) {
	    return NULL;
	}

	NODE *current = sllp->start;
	while (current != NULL) {
	    if (strcmp(current->data.name, name) == 0) {
	        return current;
	    }
	    current = current->next;
	}
	return NULL;
}

void sll_insert(SLL *sllp, char *name, float score){

	if (sllp == NULL) {
	      return;
	}

	NODE *new_node = (NODE *)malloc(sizeof(NODE));
	if (new_node == NULL) {
	    fprintf(stderr, "Memory allocation failed\n");
	    exit(EXIT_FAILURE);
	}

	strncpy(new_node->data.name, name, sizeof(new_node->data.name) - 1);
	new_node->data.name[sizeof(new_node->data.name) - 1] = '\0';
	new_node->data.score = score;
	new_node->next = NULL;

	if (sllp->start == NULL || strcmp(sllp->start->data.name, name) > 0) {
	    new_node->next = sllp->start;
	    sllp->start = new_node;
	} else {
		NODE *current = sllp->start;
	    while (current->next != NULL && strcmp(current->next->data.name, name) < 0) {
	        current = current->next;
	    }
	    new_node->next = current->next;
	    current->next = new_node;
	}

	sllp->length++;
}


int sll_delete(SLL *sllp,  char *name){
	if (sllp == NULL || sllp->start == NULL) {
	    return 0;
	}

	NODE *current = sllp->start;
	NODE *prev = NULL;

	while (current != NULL && strcmp(current->data.name, name) != 0) {
	    prev = current;
	    current = current->next;
	}

	if (current == NULL) {
	    return 0;
	}

	if (prev == NULL) {
	    sllp->start = current->next;
	} else {
	     prev->next = current->next;
	}

	free(current);
	sllp->length--;
	return 1;
}

void sll_clean(SLL *sllp){

	if (sllp == NULL) {
	    return;
	}

	NODE *current = sllp->start;
	while (current != NULL) {
	    NODE *temp = current;
	    current = current->next;
	    free(temp);
	}

	sllp->start = NULL;
	sllp->length = 0;
}
