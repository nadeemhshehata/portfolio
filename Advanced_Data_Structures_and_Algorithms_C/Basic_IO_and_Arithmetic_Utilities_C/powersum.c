/*
--------------------------------------------------
Project: a1q2
File:    powersum.c
Author:  Nadeem Hassan
Version: 2025-09-15
--------------------------------------------------
*/
#include "powersum.h"
#include <limits.h>
/**
 * Depect if overflow in power computing of b to power of n
 *
 * @param b - the base
 * @param n - the exponent
 * @return - 1 if overflow happens, 0 otherwise
 */
int power_overflow(int b, int n)
{
long long result = 1;
for(int i = 0; i < n; i++) {
	if (result > INT_MAX / b)
	return 1;

	result *= b;
}
	return 0;

}

/**
 * Compute and return b to power of n.
 *
 * @param b - the base
 * @param n - the exponent
 * @return - b to the power of n if no overflow happens, 0 otherwise
 */
int mypower(int b, int n)
{
long long result = 1;
for(int i=0; i < n; i++) {
	if (result > INT_MAX / b)
		return 0;

	result *= b;
}
	return (int)result;
}

/**
 * Compute and return the sum of powers.
 *
 * @param b - the base
 * @param n - the exponent
 * @return -  the sum of powers if no overflow happens, 0 otherwise
 */
int powersum(int b, int n)
{
	long long power = 1;
	long long sum = 1;

	    for (int i = 1; i <= n; i++) {

	        if (power > INT_MAX / b) {
	            return 0;
	        }
	        power *= b;


	        if (sum > INT_MAX - power) {
	            return 0;
	        }
	        sum += power;
	    }

	    return (int)sum;
}
