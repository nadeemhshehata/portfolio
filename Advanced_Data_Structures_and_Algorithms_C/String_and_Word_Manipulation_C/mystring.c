/*
--------------------------------------------------
Project: a3q1
File:    mystring.c
Author:  Nadeem Hassan
Version: 2025-09-30
--------------------------------------------------
*/
#include "mystring.h"



#include <stdio.h>
#include <stdlib.h>

/**
 * Count the number words of given simple string. A word starts with an English charactor end with a charactor of space, tab, comma, or period.
 *
 * @param s - char pointer to a string
 * @return - return the number of words.
 */
int str_words(char *s){
	if (s == 0) return -1;

			int count = 0;
			int in_word = 0;
			char *p = s;

			while (*p) {
				if ((*p >= 'A' && *p <= 'Z') || (*p >= 'a' && *p <= 'z')) {
					if (!in_word) {  // First letter of a word
						count++;
						in_word = 1;
					}
				}

				else if (*p == ' ' || *p == '\t' || *p == ',' || *p == '.') {
					in_word = 0;
				}

				p++;
			}

			return count;
}

/**
 * Change every upper case English letter to its lower case of string passed by s.
 *
 * @param s - char pointer to a string
 * @return - return the number of actual flips.
 */
int str_lower(char *s){

	if (s == 0) return -1;
	char *p = s;
	int count = 0;

	while(*p) {
		 if(*p >= 'A' && *p <= 'Z') {
			 *p = *p + 32;
			 count ++;
		 }

		 p++;
	}
	return count;
}

/**
 * Remove unnecessary space characters in a simple string passed by `s`
 *
 * @param s - char pointer to a string
 */
void str_trim(char *s){
	char *p = s;
	char *d = s;
	int paki = 0;

	while(*p == ' ') {
		p++;
	}
	while(*p) {
		if(*p != ' ') {
			*d++ = *p;
			paki = 1;
		} else if (paki) {
			*d++ = ' ';
			paki = 0;
		}
		p++;
	}
	if(d > s && *(d - 1) == ' ') {
		d--;
	}
	*d = '\0';
}

