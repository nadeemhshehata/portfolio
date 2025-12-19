/*
 ============================================================================
Project: a2q3
File:    matrix.h
Author:  Nadeem Hassan
Version: 2025-09-22
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#ifndef MATRIX_H
#define MATRIX_H

float norm(float *v, int n);
void  normalize(float *v, float *vout, int n);

void  matrix_scalar_multiply(float *A, float s, float *B, int rows, int cols);
void  matrix_transpose(float *A, float *B, int rows, int cols);
void  matrix_add(float *A, float *B, float *C, int rows, int cols);

/* General rectangular multiply:
   A is rowsA x colsA, B is colsA x colsB, C is rowsA x colsB */
void  matrix_multiply(float *A, float *B, float *C,
                      int rowsA, int colsA, int colsB);

#endif
