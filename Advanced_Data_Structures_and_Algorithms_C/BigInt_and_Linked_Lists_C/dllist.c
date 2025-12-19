/*
 ============================================================================
 Name        : A5q2.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "dllist.h"

NODE *dll_node(char value){

	NODE *new_node = (NODE *)malloc(sizeof(NODE));
	if (new_node == NULL) {
	    fprintf(stderr, "Memory allocation failed\n");
	    exit(EXIT_FAILURE);
	}
	new_node->data = value;
	new_node->prev = NULL;
	new_node->next = NULL;
	return new_node;
}

void dll_insert_start(DLL *dllp, NODE *np){
	if (dllp == NULL || np == NULL) {
	    return;
	}

	np->next = dllp->start;
	np->prev = NULL;

	if (dllp->start != NULL) {
	    dllp->start->prev = np;
	} else {
	    dllp->end = np;
	}

	dllp->start = np;
	dllp->length++;
}

void dll_insert_end(DLL *dllp, NODE *np){
	if (dllp == NULL || np == NULL) {
	    return;
	}

	np->next = NULL;
	np->prev = dllp->end;

	if (dllp->end != NULL) {
	    dllp->end->next = np;
	} else {
	    dllp->start = np;
	}

	dllp->end = np;
	dllp->length++;
}

void dll_delete_start(DLL *dllp){
	if (dllp == NULL || dllp->start == NULL) {
	    return;
	}

	NODE *temp = dllp->start;
	dllp->start = dllp->start->next;

	if (dllp->start != NULL) {
	    dllp->start->prev = NULL;
	} else {
	    dllp->end = NULL;
	}

	free(temp);
	dllp->length--;
}

void dll_delete_end(DLL *dllp){
	if (dllp == NULL || dllp->end == NULL) {
	    return;
	}

	NODE *temp = dllp->end;
	dllp->end = dllp->end->prev;

	if (dllp->end != NULL) {
	    dllp->end->next = NULL;
	} else {
	    dllp->start = NULL;
	}

	free(temp);
	dllp->length--;
}

void dll_clean(DLL *dllp){
	if (dllp == NULL) {
	    return;
	}

	NODE *current = dllp->start;
	while (current != NULL) {
	    NODE *temp = current;
	    current = current->next;
	    free(temp);
	}

	dllp->start = NULL;
	dllp->end = NULL;
	dllp->length = 0;
}

