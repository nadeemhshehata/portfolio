/*
--------------------------------------------------
Project: a4q1
File:    mysort.c
Author:  Nadeem Hassan
Version: 2025-09-30
--------------------------------------------------
*/

#include "mysort.h"
#include <stdio.h>
#include <stdlib.h>

// swap point
void swap(void **x, void **y) {
     void *temp = *y;
     *y = *x;
     *x = temp;
}

// a compare floating  by  pointers.
int cmp(void *x, void *y) {
   float a = *(float*)x;
   float b = *(float*)y;
     if (a > b) return 1;
     else if (a < b) return -1;
     else return 0;
}

/**
 * Use selection sort algorithm to sort array of pointers such that their pointed values
 * are in increasing order.
 *
 * @param *a[] - array of void pointers.
 * @param left - the start index of pointer in array.
 * @param right - the end index of pointer in array
 */

void select_sort(void *a[], int left, int right)
{
	for(int i = left; i < right; i++){
		int k = i;

		for (int j = i+1; j <= right; j++) {

			if (cmp(a[j], a[k]) < 0) {
			                k = j;
			 }

			}
		                if(k != i) {
						void *temp = a[i];
						a[i] = a[k];
						a[k] = temp;

		}
	}


}
/**
 * Use quick sort algorithm to sort array of pointers such that their pointed values
 * are in increasing order.
 *
 * @param *a[] - array of void pointers.
 * @param left - the start index of pointer in array.
 * @param right - the end index of pointer in array
 */
void quick_sort(void *a[], int left, int right) {

	if (left < right) {
	        int i = left + 1;
	        int j = right;
	        void *pivot = a[left];

	        while (i <= j) {
	            while (i <= right && cmp(a[i], pivot) <= 0) i++;
	            while (j >= left && cmp(a[j], pivot) > 0) j--;

	            if (i < j) {
	                swap(&a[i], &a[j]);
	            }
	        }

	        swap(&a[left], &a[j]);


	        quick_sort(a, left, j - 1);
	        quick_sort(a, j + 1, right);
	    }

}

/**
 * Use either selection or quick sort algorithm to sort array of pointers such that their pointed values
 * are in order defined by the given comparison function
 *
 * @param *a[] - array of void pointers.
 * @param left - the start index of pointer in array.
 * @param right - the end index of pointer in array
 * @param (*cmp) - pointer to a comparison function used to compaire pointers by their pointed values.
 */
void my_sort(void *a[], int left, int right, int (*cmp)(void*, void*) )
{
	for(int i = left; i < right; i++){
		int k = i;

	for(int j = i+1; j <= right; j++){

		if(cmp(a[j], a[k]) < 0) {
			   k = j;
		    }
	    }

		if(k != i) {
			void *temp = a[i];
			a[i] = a[k];
			a[k] = temp;

		}
	}
}

