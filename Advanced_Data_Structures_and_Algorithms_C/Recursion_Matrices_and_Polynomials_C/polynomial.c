/*
 ============================================================================
Project: a2q2
File:    polynomial.c
Author:  Nadeem Hassan
Version: 2025-09-22
 ============================================================================
 */


#include <stdlib.h>
#include <math.h>

#include <stdio.h>
#include "polynomial.h"
#define EPSILON 1e-6
#define MAXCOUNT 100

float horner(float *p, int n, float x)
{
	float result = p[0];

	for (int i = 1; i < n; i++) {
		result = result * x + p[i];
	}
	return result;
}

void derivative(float *p, float *d, int n)
{
	for (int i = 0; i < n - 1; i++) {
	        d[i] = (n - 1 - i) * p[i];
	    }
}



float newton(float *p, int n, float x0) {
	float tolerance = 1e-6f;
	    int   max_iterations = 100;

	    float d[n - 1];
	    derivative(p, d, n);

	    for (int i = 0; i < max_iterations; i++) {
	        float f_x       = horner(p, n, x0);
	        float f_prime_x = horner(d, n - 1, x0);

	        if (fabsf(f_prime_x) < tolerance) {
	            return x0; // derivative too small
	        }

	        float x1 = x0 - f_x / f_prime_x;

	        if (fabsf(x1 - x0) < tolerance) {
	            return x1;
	        }
	        x0 = x1;
	    }
	    return x0;
	}
