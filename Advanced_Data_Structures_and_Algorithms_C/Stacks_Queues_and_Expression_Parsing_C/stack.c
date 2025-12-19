/*
 ============================================================================
 Name        : stack.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

void push(STACK *sp, NODE *np){
	if (!np) return;
	np->next = sp->top;
	sp->top = np;
	sp->length++;
}

NODE *pop(STACK *sp){
	if (!sp->top) return NULL;
	NODE *temp = sp->top;
	sp->top = sp->top->next;
	temp->next = NULL;
	sp->length--;
	return temp;
}

void clean_stack(STACK *sp){
	while (sp->top) {
	    NODE *temp = pop(sp);
	    free(temp);
	}
	sp->length = 0;
}
