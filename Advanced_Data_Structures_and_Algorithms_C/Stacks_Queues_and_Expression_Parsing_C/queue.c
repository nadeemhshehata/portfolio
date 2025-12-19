/*
 ============================================================================
 Name        : queue.h
 Author      : Nadeem Hassan
 Version     : A6q1
 Copyright   :
 Description :
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

void enqueue(QUEUE *qp, NODE *np){
	np->next = NULL;
	if (qp->rear) {
	    qp->rear->next = np;
	} else {
	    qp->front = np;
	}
	qp->rear = np;
	qp->length++;
}

NODE *dequeue(QUEUE *qp){
	if (!qp->front) return NULL;
	NODE *temp = qp->front;
	qp->front = qp->front->next;
	if (!qp->front) {
	    qp->rear = NULL;
	}
	temp->next = NULL;
	qp->length--;
	return temp;
}

void clean_queue(QUEUE *qp){
	while (qp->front) {
	    NODE *temp = dequeue(qp);
	    free(temp);
	}
	qp->length = 0;
}
