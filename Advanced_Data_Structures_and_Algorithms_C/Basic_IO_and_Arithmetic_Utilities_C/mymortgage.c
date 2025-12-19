/**
 * Project: a1q1
 * File:    mychar.c
 * Author:  Nadeem Hassan
 * Version: 2025-09-15
*/

#include <math.h>
#include "mymortgage.h"




 /**
 * Compute the monthly payment of given mortgage princile, annual interest rate (%), and mortgage years.
 *
 * @param principal_amount - float type.
 * @param annual_interest_rate - value of parcentage rate, e.g. 5 means 5%, float type.
 * @param years - number of mortgage year, int type.
 * @return - monthly payment, float type.
 */
float monthly_payment(float principal_amount, float annual_interest_rate, int years){
	if (principal_amount < 0.0f || years <= 0) {
			return 0.0f;
		}

		const float n = (float)years * 12.0f;
		const float r = annual_interest_rate / 100.0f / 12.0f;

		if (r == 0.0f) {
			return principal_amount / n;
		}

		const float one_plus_r = 1.0f + r;
		const float denom = 1.0f - powf(one_plus_r, -n);
		if (denom == 0.0f) {
			return 0.0f;
		}
		return principal_amount * r / denom;
}

/**
 * Determine the total payment of loan given mortgage princile, annual interest rate (%), and mortgage years.
 *
 * @param principal_amount - float type.
 * @param annual_interest_rate - value of parcentage rate, e.g. 5 means 5%, float type.
 * @param years - number of mortgage year, int type.
 * @return - the total payment of the loan, float type.
 */
float total_payment(float principal_amount, float annual_interest_rate, int years){
	if (principal_amount < 0.0f || years <= 0) {
	        return 0.0f;
	    }
	    const float m = monthly_payment(principal_amount, annual_interest_rate, years);
	    const float n = (float)years * 12.0f;
	    return m * n;

}
/**
 * Determine the total interested payed for the loan given mortgage princile, annual interest rate (%), and mortgage years.
 *
 * @param principal_amount - float type.
 * @param annual_interest_rate - value of parcentage rate, e.g. 5 means 5%, float type.
 * @param years - number of mortgage year, int type.
 * @return - the total interest payed by the end of paying off the loan, float type.
 */
float total_interest(float principal_amount, float annual_interest_rate, int years){
	if (principal_amount < 0.0f || years <= 0) {
	        return 0.0f;
	    }
	    const float tp = total_payment(principal_amount, annual_interest_rate, years);
	    return tp - principal_amount;
	}



