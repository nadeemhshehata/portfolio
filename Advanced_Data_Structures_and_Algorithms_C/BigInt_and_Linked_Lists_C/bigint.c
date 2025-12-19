/*
 ============================================================================
 Name        : A5q3.c
 Author      : Nadeem Hassan
 Version     :
 Copyright   : Your copyright notice
 Description :
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "dllist.h"
#include "bigint.h"

BIGINT bigint(char *digitstr){
	BIGINT result;
	result.length = 0;
	result.start = NULL;
	result.end = NULL;

	for (int i = 0; digitstr[i] != '\0'; i++) {
	    NODE *new_node = dll_node(digitstr[i] - '0');
	    dll_insert_end(&result, new_node);
	}
	return result;
}

BIGINT bigint_add(BIGINT oprand1, BIGINT oprand2){
	BIGINT sum;
	sum.length = 0;
	sum.start = NULL;
	sum.end = NULL;

	NODE *ptr1 = oprand1.end;
	NODE *ptr2 = oprand2.end;
	int carry = 0;

	while (ptr1 != NULL || ptr2 != NULL || carry > 0) {
	    int num1 = (ptr1 != NULL) ? ptr1->data : 0;
	    int num2 = (ptr2 != NULL) ? ptr2->data : 0;
	    int total = num1 + num2 + carry;

	    carry = total / 10;
	    total = total % 10;

	    NODE *new_node = dll_node(total);
	    dll_insert_start(&sum, new_node);

	    if (ptr1 != NULL) ptr1 = ptr1->prev;
	    if (ptr2 != NULL) ptr2 = ptr2->prev;
	}
	return sum;
}

BIGINT bigint_fibonacci(int n){
	BIGINT fib0 = bigint("0");
	BIGINT fib1 = bigint("1");
	if (n == 0) return fib0;
	if (n == 1) return fib1;

	BIGINT fib_n;
	for (int i = 2; i <= n; i++) {
	    fib_n = bigint_add(fib0, fib1);
	    dll_clean(&fib0);
	    fib0 = fib1;
	    fib1 = fib_n;
	}
	return fib_n;
}
