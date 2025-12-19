/**
 * Project: a1q1
 * File:    mychar.c
 * Author:  Nadeem Hassan
 * Version: 2025-09-15
 * Determine the type of a char character.
*/


#include "mychar.h"

#include <ctype.h>




/**
 *
 * @param c - char type
 * @return - 0 if c is a digit
             1 if c is an arithmetic operator
             2 if c is the left parenthsis (
             3 if c is the right parenthsis )
             4 if c is an English letter;
             otherwise -1.
 */


int mytype(char c){
	if (c >= '0' && c <= '9') {
			return 0;
		}

		if (c == '+' || c == '-' || c == '*' || c == '/') {
			return 1;
		}

		if (c == '(') {
			return 2;
		}

		if (c == ')') {
			return 3;
		}

		if (isalpha(c)) {
			return 4;
		}

		return -1;
}

/**
 * Flip the case of an English character.
 *
 * @param c - char type
 * @return -  c's upper/lower case letter if c is a lower/upper case English letter.
 */
char case_flip(char c) {
	if (c >= 'A' && c <= 'Z') {
			return tolower(c);
		}
		if (c >= 'a' && c <= 'z') {
			return toupper(c);
		}
		return c;

}

/**
 * Convert digit character to the corresponding integer value.
 *
 * @param c - char type value
 * @return - its corresponding integer value if c is a digit character;
 *           otherwise -1.
 */
int digit_to_int(char c){
	if (c >= '0' && c <= '9'){
		return c - '0';
	 }
	 else {
		return -1;
	 }
}


