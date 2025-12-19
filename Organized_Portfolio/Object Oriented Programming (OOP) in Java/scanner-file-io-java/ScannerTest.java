package cp213;

import java.util.Scanner;

/**
 * Class to demonstrate the use of Scanner with a keyboard and File objects.
 *
 * @author Nadeem, 169093285, hass3285@mylaurier.ca
 * @version 2022-01-08
 */
public class ScannerTest {

    /**
     * Count lines in the scanned file.
     *
     * @param source Scanner to process
     * @return number of lines in scanned file
     */
    public static int countLines(final Scanner source) {
	int count = 0;

	// your code here
	while (source.hasNextLine()) {
	    source.nextLine(); // Consume the line
	    count++; // Increment the line count
	}

	return count;
    }

    /**
     * Count tokens in the scanned object.
     *
     * @param source Scanner to process
     * @return number of tokens in scanned object
     */
    public static int countTokens(final Scanner source) {
	int tokens = 0;

	// your code here
	while (source.hasNext()) {
	    source.next();
	    tokens++;
	}

	return tokens;
    }

    /**
     * Ask for and total integers from the keyboard.
     *
     * @param source Scanner to process
     * @return total of positive integers entered from keyboard
     */
    public static int readNumbers(final Scanner keyboard) {
	int total = 0;

	// your code here
	while (true) {
	    if (keyboard.hasNextInt()) {
		int number = keyboard.nextInt();
		if (number > 0) {
		    total += number; // Add positive integers to the total
		} else {
		    System.out.println("Only positive integers are allowed.");
		}
	    } else {
		String input = keyboard.next(); // Read the next token
		if (input.equalsIgnoreCase("q")) {
		    System.out.println("Exiting...");
		    break; // Exit the loop when 'q' is entered
		} else {
		    System.out.println("'" + input + "' is not an integer or 'q'.");
		}
	    }
	}

	return total;
    }

}
