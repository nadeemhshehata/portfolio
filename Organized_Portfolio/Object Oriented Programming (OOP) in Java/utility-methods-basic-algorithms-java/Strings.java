package cp213;

/**
 * @author Your name and id here
 * @version 2025-01-05
 */
public class Strings {
    // Constants
    public static final String VOWELS = "aeiouAEIOU";

    /**
     * Determines if string is a "palindrome": a word, verse, or sentence (such as
     * "Able was I ere I saw Elba") that reads the same backward or forward. Ignores
     * case, spaces, digits, and punctuation in the string parameter s.
     *
     * @param string a string
     * @return true if string is a palindrome, false otherwise
     */
    public static boolean isPalindrome(final String string) {

	// your code here

	String cleaned = string.replaceAll("[^a-zA-Z]", "").toLowerCase();
	return cleaned.equals(new StringBuilder(cleaned).reverse().toString());
    }

    /**
     * Determines if name is a valid Java variable name. Variables names must start
     * with a letter or an underscore, but cannot be an underscore alone. The rest
     * of the variable name may consist of letters, numbers and underscores.
     *
     * @param name a string to test as a Java variable name
     * @return true if name is a valid Java variable name, false otherwise
     */
    public static boolean isValid(final String name) {

	// your code here
	return name != null && name.length() > 0
		&& (Character.isLetter(name.charAt(0)) || (name.charAt(0) == '_' && name.length() > 1))
		&& name.matches("^[a-zA-Z_][a-zA-Z0-9_]*$");
    }

    /**
     * Converts a word to Pig Latin. The conversion is:
     * <ul>
     * <li>if a word begins with a vowel, add "way" to the end of the word.</li>
     * <li>if the word begins with consonants, move the leading consonants to the
     * end of the word and add "ay" to the end of that. "y" is treated as a
     * consonant if it is the first character in the word, and as a vowel for
     * anywhere else in the word.</li>
     * </ul>
     * Preserve the case of the word - i.e. if the first character of word is
     * upper-case, then the new first character should also be upper case.
     *
     * @param word The string to convert to Pig Latin
     * @return the Pig Latin version of word
     */
    public static String pigLatin(String word) {

	// your code here

	if (word == null || word.isEmpty()) {
	    return word;
	}

	boolean isCapitalized = Character.isUpperCase(word.charAt(0));
	word = word.toLowerCase();

	String pigWord;

	if (VOWELS.indexOf(word.charAt(0)) != -1) {
	    pigWord = word + "way";
	} else {
	    int vowelIndex = 0;

	    // 'y' is treated as a consonant only if it's the first letter
	    while (vowelIndex < word.length() && (VOWELS.indexOf(word.charAt(vowelIndex)) == -1
		    || (word.charAt(vowelIndex) == 'y' && vowelIndex == 0))) {
		vowelIndex++;
	    }

	    pigWord = word.substring(vowelIndex) + word.substring(0, vowelIndex) + "ay";
	}

	if (isCapitalized) {
	    pigWord = Character.toUpperCase(pigWord.charAt(0)) + pigWord.substring(1);
	}

	return pigWord;
    }
}
