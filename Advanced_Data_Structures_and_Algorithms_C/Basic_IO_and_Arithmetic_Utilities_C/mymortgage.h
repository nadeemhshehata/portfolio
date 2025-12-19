/**
 *
 *
 */
#ifndef MYMORTGAGE_H
#define MYMORTGAGE_H

/**
 * @file mymortgage.h
 * @brief Simple mortgage calculation utilities.
 *
 * Provides functions to compute a fixed-rate mortgage monthly payment,
 * total payment, and total interest over the life of the loan.
 */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Compute the monthly payment for a fixed-rate mortgage.
 *
 * @param principal_amount Principal loan amount (must be >= 0).
 * @param annual_interest_rate Annual interest rate in percent (e.g., 5 means 5%).
 * @param years Length of the mortgage in years (must be > 0).
 * @return Monthly payment. Returns 0.0f if inputs are invalid (e.g., years <= 0).
 */
float monthly_payment(float principal_amount, float annual_interest_rate, int years);

/**
 * Compute the total payment over the full term of the loan.
 *
 * @param principal_amount Principal loan amount (must be >= 0).
 * @param annual_interest_rate Annual interest rate in percent (e.g., 5 means 5%).
 * @param years Length of the mortgage in years (must be > 0).
 * @return Total paid over the life of the loan. Returns 0.0f if inputs are invalid.
 */
float total_payment(float principal_amount, float annual_interest_rate, int years);

/**
 * Compute the total interest paid by the end of the loan.
 *
 * @param principal_amount Principal loan amount (must be >= 0).
 * @param annual_interest_rate Annual interest rate in percent (e.g., 5 means 5%).
 * @param years Length of the mortgage in years (must be > 0).
 * @return Total interest paid. Returns 0.0f if inputs are invalid.
 */
float total_interest(float principal_amount, float annual_interest_rate, int years);

#ifdef __cplusplus
}
#endif

#endif /* MYMORTGAGE_H */
