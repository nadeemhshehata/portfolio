package cp213;

import java.io.PrintStream;
import java.util.Scanner;

/**
 * @author Your name and id here
 * @version 2025-01-05
 */
public class SerialNumber {

    /**
     * Determines if a string contains all digits.
     *
     * @param str The string to test.
     * @return true if str is all digits, false otherwise.
     */
    public static boolean allDigits(final String str) {

	// your code here

	return str != null && !str.isEmpty() && str.chars().allMatch(Character::isDigit);

    }

    /**
     * Determines if a string is a good serial number. Good serial numbers are of
     * the form 'SN/nnnn-nnn', where 'n' is a digit.
     *
     * @param sn The serial number to test.
     * @return true if the serial number is valid in form, false otherwise.
     */
    public static boolean validSn(final String sn) {

	// your code here

	return sn != null && sn.length() == 11 && sn.startsWith("SN/") && sn.charAt(7) == '-'
		&& Character.isDigit(sn.charAt(3)) && Character.isDigit(sn.charAt(4)) && Character.isDigit(sn.charAt(5))
		&& Character.isDigit(sn.charAt(6)) && Character.isDigit(sn.charAt(8)) && Character.isDigit(sn.charAt(9))
		&& Character.isDigit(sn.charAt(10));

    }

    /**
     * Evaluates serial numbers from a file. Writes valid serial numbers to
     * good_sns, and invalid serial numbers to bad_sns. Each line of fileIn contains
     * a (possibly valid) serial number.
     *
     * @param fileIn  a file already open for reading
     * @param goodSns a file already open for writing
     * @param badSns  a file already open for writing
     */
    public static void validSnFile(final Scanner fileIn, final PrintStream goodSns, final PrintStream badSns) {

	// your code here

	while (fileIn.hasNextLine()) {
	    String sn = fileIn.nextLine();
	    (validSn(sn) ? goodSns : badSns).println(sn);
	}
    }

}
