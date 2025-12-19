/*
 ============================================================================
 Name        : A6q3.c
 Author      : Nadeem Hassan
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "expression.h"
#include "queue.h"
#include "stack.h"
#include "common.h"


QUEUE infix_to_postfix(char *infixstr){
	QUEUE queue = {0, NULL, NULL};
	STACK stack = {0, NULL};

	for (int i = 0; infixstr[i] != '\0';) {
	    if (isdigit(infixstr[i])) {
	        int num = 0;
	        while (isdigit(infixstr[i])) {
	            num = num * 10 + (infixstr[i] - '0');
	            i++;
	        }
	        enqueue(&queue, new_node(num, 0));
	    } else {
	        char ch = infixstr[i];
	        int t = mytype(ch);

	        if (t == 1) {
	            while (stack.top && priority(stack.top->data) >= priority(ch)) {
	                enqueue(&queue, pop(&stack));
	            }
	            push(&stack, new_node(ch, 1));
	        } else if (t == 2) {
	            push(&stack, new_node(ch, 2));
	        } else if (t == 3) {
	            while (stack.top && stack.top->type != 2) {
	                enqueue(&queue, pop(&stack));
	            }
	            if (stack.top && stack.top->type == 2) {
	                free(pop(&stack));
	            }
	        }
	        i++;
	    }
	}

	while (stack.top) {
	enqueue(&queue, pop(&stack));
	}

	return queue;
}

int evaluate_postfix(QUEUE queue){
    STACK stack = {0, NULL};

    while (queue.front) {
        NODE *node = dequeue(&queue);

        if (node->type == 0) {
            push(&stack, new_node(node->data, 0));
        } else if (node->type == 1) {
            NODE *b = pop(&stack);
            NODE *a = pop(&stack);
            int result = 0;

            if (a == NULL || b == NULL) {
                printf("Error: Invalid expression\n");
                exit(EXIT_FAILURE);
            }

            switch (node->data) {
                case '+': result = a->data + b->data; break;
                case '-': result = a->data - b->data; break;
                case '*': result = a->data * b->data; break;
                case '/':
                    if (b->data == 0) {
                        printf("Error: Division by zero\n");
                        exit(EXIT_FAILURE);
                    }
                    result = a->data / b->data;
                    break;
            }

            free(a);
            free(b);
            free(node);

            push(&stack, new_node(result, 0));
        }
    }

    int final_result = pop(&stack)->data;
    return final_result;
}


int evaluate_infix(char *infixstr){
	QUEUE postfix_queue = infix_to_postfix(infixstr);
	return evaluate_postfix(postfix_queue);
}
