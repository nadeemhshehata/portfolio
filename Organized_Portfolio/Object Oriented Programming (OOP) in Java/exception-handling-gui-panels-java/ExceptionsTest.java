package cp213;

import java.util.InputMismatchException;
import java.util.Scanner;

public class ExceptionsTest {

    /**
     * Uses exceptions to capture bad input from a keyboard Scanner.
     *
     * @return The total of all the integers entered.
     */
    public static int scannerTest(final Scanner keyboard) {

	// your code here

	int total = 0;
	while (true) {
	    System.out.print("Enter an integer (\"Quit\" to stop): ");
	    try {
		if (keyboard.hasNextInt()) {
		    total += keyboard.nextInt(); // Read integer and add to total
		} else {
		    String input = keyboard.next(); // Read input
		    if (input.equalsIgnoreCase("Quit")) {
			return total;
		    } else {
			throw new InputMismatchException("That is not an integer!");
		    }
		}
	    } catch (InputMismatchException e) {
		System.out.println(e.getMessage());
	    }
	}
    }

    /**
     * Repeats a string.
     *
     * @param n   Number of times to repeat a string.
     * @param str The string to print.
     * @return The repeated string.
     * @throws Exception If n is negative.
     */
    public static String stringPrinter(int n, String str) throws Exception {

	// your code here

	if (n < 0) {
	    throw new IllegalArgumentException("Please Enter a Positive Number!");
	}

	StringBuilder result = new StringBuilder();
	for (int i = 0; i < n; i++) {
	    result.append(str);
	}

	return result.toString();
    }

}
