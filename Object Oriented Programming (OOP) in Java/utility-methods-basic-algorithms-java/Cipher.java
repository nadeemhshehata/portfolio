package cp213;

/**
 * @author Nadeem Hassan 169093285
 * @version 2025-02-03
 */
public class Cipher {
    // Constants
    public static final String ALPHA = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    public static final int ALPHA_LENGTH = ALPHA.length();

    /**
     * Encipher a string using a shift cipher. Each letter is replaced by a letter
     * 'n' letters to the right of the original. Thus for example, all shift values
     * evenly divisible by 26 (the length of the English alphabet) replace a letter
     * with itself. Non-letters are left unchanged.
     *
     * @param s string to encipher
     * @param n the number of letters to shift
     * @return the enciphered string in all upper-case
     */
    public static String shift(final String s, final int n) {

	// your code here

	// Convert input to uppercase
	String upper = s.toUpperCase();

	// Create StringBuilder to build result
	StringBuilder result = new StringBuilder();

	// Normalize shift to be within alphabet length
	int shift = n % ALPHA_LENGTH;

	// Process each character
	for (char c : upper.toCharArray()) {
	    // Find index of character in alphabet
	    int index = ALPHA.indexOf(c);

	    // If character is a letter, shift it
	    if (index != -1) {
		// Calculate new index with wrapping
		int newIndex = (index + shift + ALPHA_LENGTH) % ALPHA_LENGTH;
		result.append(ALPHA.charAt(newIndex));
	    } else {
		// Non-letter characters remain unchanged
		result.append(c);
	    }
	}
	return result.toString();
    }

    /**
     * Encipher a string using the letter positions in ciphertext. Each letter is
     * replaced by the letter in the same ordinal position in the ciphertext.
     * Non-letters are left unchanged. Ex:
     *
     * <pre>
    Alphabet:   ABCDEFGHIJKLMNOPQRSTUVWXYZ
    Ciphertext: AVIBROWNZCEFGHJKLMPQSTUXYD
     * </pre>
     *
     * A is replaced by A, B by V, C by I, D by B, E by R, and so on. Non-letters
     * are ignored.
     *
     * @param s          string to encipher
     * @param ciphertext ciphertext alphabet
     * @return the enciphered string in all upper-case
     */
    public static String substitute(final String s, final String ciphertext) {

	// your code here

	if (ciphertext.length() != ALPHA_LENGTH) {
	    throw new IllegalArgumentException("Ciphertext must be 26 letters long");
	}

	// Convert inputs to uppercase
	String upper = s.toUpperCase();
	String upperCipher = ciphertext.toUpperCase();

	// Create StringBuilder to build result
	StringBuilder result = new StringBuilder();

	// Process each character
	for (char c : upper.toCharArray()) {
	    // Find index of character in alphabet
	    int index = ALPHA.indexOf(c);

	    // If character is a letter, substitute it
	    if (index != -1) {
		result.append(upperCipher.charAt(index));
	    } else {
		// Non-letter characters remain unchanged
		result.append(c);
	    }
	}

	return result.toString();
    }

}
