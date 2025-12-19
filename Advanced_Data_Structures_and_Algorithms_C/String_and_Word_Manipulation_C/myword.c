/*
--------------------------------------------------
Project: a3q2
File:    myword.c
Author:  Nadeem Hassan
Version: 2025-09-30
--------------------------------------------------
*/

#include <stdio.h>
#include <string.h>
#include "mystring.h"
#include "myword.h"

#define MAX_LINE_LEN 1000
#define MAX_WORDS 1000

/*
 * Define enumeration type BOOLEAN with value FALSE = 0 and TRUE 1.
 */

/*
 * Define structure type WORD consists of char word[20] to store a word, int count to hold frequency of the word.
 */

/*
 * Define structure type WORDSTATS consisting of int line_count, int word_count, and int keyword_count to represent
 * to represent the number of lines, number of all words, and the number of different non-common-word in text data.
 */


/*
 * Load word data from file, and insert words a directory represented by char array.
 *
 * @param  FILE *fp -   file pointer to an opened text file
 * @param *dictionary - char pointer to a char array where dictionary words are stored.
 *                      It's up to your design on how to store words in the char array.
 * @return - the number of words added into the dictionary.
 */

int create_dictionary(FILE *fp, char *dictionary) {
	char line[MAX_LINE_LEN];
	    char delimiters[] = " .,\n\t\r";
	    char *token;
	    int count = 0;

	    dictionary[0] = '\0';


	    while (fgets(line, MAX_LINE_LEN, fp) != NULL) {
	        str_lower(line);
	        str_trim(line);


	        token = strtok(line, delimiters);
	        while (token != NULL) {
	            strcat(dictionary, token);
	            strcat(dictionary, ",");
	            count++;
	            token = strtok(NULL, delimiters);
	        }
	    }
	    return count;
}

/*
 * Determine if a given word is contained in the given dictionary.
 *
 * @param *dictionary -  char pointer to a char array of given dictionary.
 * @param *word  -  pointer to a given word.
 *
 * @return - TRUE if the word is in the dictionary, FALSE otherwise.
 */


BOOLEAN contain_word(char *dictionary, char *word) {


	if (word == NULL || *word == '\0') return 0;

	char temp[25] = ",";
	strncat(temp, word, sizeof(temp) - strlen(temp) - 1);
	strcat(temp, ",");

	if (strstr(dictionary, temp) != NULL) {
		return 1;
	}

	return 0;

}

/*
 * Process text data from a file for word statistic information of line count, word count, keyword count, and frequency of keyword.
 *
 * @param *fp -  FILE pointer of input text data file. .
 * @param *words  -  WORD array for keywords and their frequencies.
 * @param *dictionary  -  stop-word/common-word dictionary.
 *
 * @return - WORDSTATS value of processed word stats information.
 */

WORDSTATS process_words(FILE *fp, WORD *words, char *dictionary) {

	WORDSTATS ws = {0};
		    char line[MAX_LINE_LEN];
		    char delimiters[] = " .,\n\t\r";
		    char *word_token;
		    int i, found;


		    while (fgets(line, MAX_LINE_LEN, fp) != NULL) {
		        ws.line_count++;

		        str_lower(line);


		        word_token = strtok(line, delimiters);
		        while (word_token != NULL) {
		            ws.word_count++;

		            if (contain_word(dictionary, word_token) == FALSE) {
		                found = 0;


		                for (i = 0; i < ws.keyword_count; i++) {
		                    if (strcmp(words[i].word, word_token) == 0) {
		                        words[i].count++;
		                        found = 1;
		                        break;
		                    }
		                }


		                if (!found && ws.keyword_count < MAX_WORDS) {
		                    strcpy(words[ws.keyword_count].word, word_token);
		                    words[ws.keyword_count].count = 1;
		                    ws.keyword_count++;
		                }
		            }

		            word_token = strtok(NULL, delimiters);
		        }
		    }

	return ws;



}
