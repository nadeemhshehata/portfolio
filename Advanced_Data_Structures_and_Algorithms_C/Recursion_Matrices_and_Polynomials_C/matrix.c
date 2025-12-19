/*
 ============================================================================
Project: a2q3
File:    matrix.c
Author:  Nadeem Hassan
Version: 2025-09-22
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#include <math.h>
#include "matrix.h"

float norm(float *v, int n) {
	float sum = 0.0f;
	    for (int i = 0; i < n; i++) {
	        sum += v[i] * v[i];
	    }
	    return sqrtf(sum);
}

void normalize(float *v, float *vout, int n) {
    float m = norm(v, n);
    if (m == 0.0f) {
        for (int i = 0; i < n; i++) vout[i] = 0.0f;
        return;
    }
    for (int i = 0; i < n; i++) {
        vout[i] = v[i] / m;
    }
}

void matrix_scalar_multiply(float *A, float s, float *B, int rows, int cols) {
    int total = rows * cols;
    for (int i = 0; i < total; i++) {
        B[i] = s * A[i];
    }
}

void matrix_transpose(float *A, float *B, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            B[j * rows + i] = A[i * cols + j];
        }
    }
}


void matrix_add(float *A, float *B, float *C, int rows, int cols) {
    int total = rows * cols;
    for (int i = 0; i < total; i++) {
        C[i] = A[i] + B[i];
    }
}

void matrix_multiply(float *A, float *B, float *C,
                     int rowsA, int colsA, int colsB) {
    for (int i = 0; i < rowsA; i++) {
        for (int j = 0; j < colsB; j++) {
            float sum = 0.0f;
            for (int k = 0; k < colsA; k++) {
                sum += A[i * colsA + k] * B[k * colsB + j];
            }
            C[i * colsB + j] = sum;
        }
    }



}

