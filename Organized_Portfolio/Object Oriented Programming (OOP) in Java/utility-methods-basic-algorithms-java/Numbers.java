package cp213;

/**
 * @author Nadeem Hassan 169093285
 * @version 2025-02-03
 */
public class Numbers {

    /**
     * Determines closest value of two values to a target value.
     *
     * @param target the target value
     * @param v1     first comparison value
     * @param v2     second comparison value
     * @return one of v1 or v2 that is closest to target, v1 is the value chosen if
     *         v1 and v2 are an equal distance from target
     */
    public static double closest(final double target, final double v1, final double v2) {

	// your code here

	double diff1 = Math.abs(target - v1);
	double diff2 = Math.abs(target - v2);

	return (diff1 <= diff2) ? v1 : v2;
    }

    /**
     * Determines if n is a prime number. Prime numbers are whole numbers greater
     * than 1, that have only two factors - 1 and the number itself. Prime numbers
     * are divisible only by the number 1 or itself.
     *
     * @param n an integer
     * @return true if n is prime, false otherwise
     */
    public static boolean isPrime(final int n) {

	// your code here
	boolean x = true;

	if (n < 2) {
	    x = false;
	}

	// Check for divisibility up to square root of n
	// This is an optimization - we only need to check up to sqrt(n)
	for (int i = 2; i <= Math.sqrt(n); i++) {
	    if (n % i == 0) {
		x = false;
	    }
	}

	// If no divisors found, it's prime
	return x;
    }

    /**
     * Sums and returns the total of a partial harmonic series. This series is the
     * sum of all terms 1/i, where i ranges from 1 to n (inclusive). Ex:
     *
     * n = 3: sum = 1/1 + 1/2 + 1/3 = 1.8333333333333333
     *
     * @param n an integer
     * @return sum of partial harmonic series from 1 to n
     */
    public static double sumPartialHarmonic(final int n) {

	// your code here
	return (n < 1) ? 0.0 : java.util.stream.IntStream.rangeClosed(1, n).mapToDouble(i -> 1.0 / i).sum();
    }

}
