package cp213;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

/**
 * Test class for ScannerTest.
 */
public class ScannerTestMain {

    public static void main(String[] args) {
	System.out.println("Testing ScannerTest functions:");
	System.out.println("------------------------------------");

	// Test readNumbers
	testReadNumbers();

	// Test countLines and countTokens on a file
	testFileFunctions();

	// Test countTokens on a string
	testStringTokens();

	System.out.println("Testing complete.");
    }

    /**
     * Test the readNumbers function.
     */
    private static void testReadNumbers() {
	System.out.println("Testing readNumbers:");

	// Simulated user input
	String input = "5\n-3\n8\nwhat?\nq\n";
	Scanner keyboard = new Scanner(input);

	// Call the function and capture the total
	int total = ScannerTest.readNumbers(keyboard);
	keyboard.close();

	// Expected output
	System.out.println("Expected Total: 13");
	System.out.println("Actual Total: " + total);

	System.out.println("------------------------------------");
    }

    /**
     * Test countLines and countTokens using a file.
     */
    private static void testFileFunctions() {
	System.out.println("Testing countLines and countTokens on a file:");

	// Define the file to scan (assumes ScannerTest.java exists in the project)
	final File file = new File("src/cp213/ScannerTest.java");

	try {
	    // Test countLines
	    Scanner source = new Scanner(file);
	    int lineCount = ScannerTest.countLines(source);
	    source.close();

	    // Test countTokens
	    source = new Scanner(file);
	    int tokenCount = ScannerTest.countTokens(source);
	    source.close();

	    // Display results
	    System.out.println("Lines in file: " + lineCount);
	    System.out.println("Tokens in file: " + tokenCount);

	} catch (FileNotFoundException e) {
	    System.out.println("File not found: " + file.getPath());
	}

	System.out.println("------------------------------------");
    }

    /**
     * Test countTokens on a string.
     */
    private static void testStringTokens() {
	System.out.println("Testing countTokens on a string:");

	// Test string
	String sentence = "This is a sentence with words.";
	Scanner source = new Scanner(sentence);

	// Call the function and capture the token count
	int tokenCount = ScannerTest.countTokens(source);
	source.close();

	// Expected output
	System.out.println("Expected Tokens: 6");
	System.out.println("Actual Tokens: " + tokenCount);

	System.out.println("------------------------------------");
    }
}