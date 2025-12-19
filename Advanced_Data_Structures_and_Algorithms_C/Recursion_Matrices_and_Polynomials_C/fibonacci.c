/*
 ============================================================================
Project: a2q1
File:    fibonacci.c
Author:  Nadeem Hassan
Version: 2025-09-22
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "fibonacci.h"

int recursive_fibonacci(int n) {

	if (n == 0)
		return 0;
	if (n == 1)
		return 1;

	int a = 1, b = 0, c;

	for (int i = 2; i <= n; i++) {
		c = a + b;
		b = a;
		a = c;

	}

	return a;

}

int iterative_fibonacci(int n)
{
	if (n < 0) return -1;
	    if (n == 0) return 0;
	    if (n == 1) return 1;

	    int a = 0, b = 1;
	    for (int i = 1; i < n; i++) {
	        // Will a + b overflow 32-bit signed int?
	        if (b > INT_MAX - a) return -1;   // signal overflow (ptest prints "overflow")
	        int c = a + b;
	        a = b;
	        b = c;
	    }
	    return b;
}

int dpbu_fibonacci(int *f, int n) {
	if (n < 0) return -1;
	    if (n == 0) { f[0] = 0; return 0; }
	    if (n == 1) { f[1] = 1; return 1; }

	    f[0] = 0;
	    f[1] = 1;

	    for (int i = 2; i <= n; i++) {
	        if (f[i-1] > INT_MAX - f[i-2]) return -1;  // overflow
	        f[i] = f[i-1] + f[i-2];
	    }
	    return f[n];

}

int dptd_fibonacci(int *f, int n) {

	if (n < 0) return -1;

	    // Base cases (store them so memo works)
	    if (n == 0) { f[0] = 0; return 0; }
	    if (n == 1) { f[1] = 1; return 1; }

	    // If memoized and valid (>0 for n>1), return it
	    if (f[n] > 0) return f[n];

	    // Compute subproblems
	    int a = dptd_fibonacci(f, n - 1);
	    if (a == -1) return -1;  // propagate overflow

	    int b = dptd_fibonacci(f, n - 2);
	    if (b == -1) return -1;

	    // Check for overflow before add
	    if (a > INT_MAX - b) return -1;

	    f[n] = a + b;
	    return f[n];

}
