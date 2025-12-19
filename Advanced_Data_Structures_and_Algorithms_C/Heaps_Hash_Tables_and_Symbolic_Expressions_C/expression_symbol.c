/*
 ============================================================================
 Name        : A9q2.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "expression_symbol.h"   // brings in QUEUE, STACK, NODE, HASHTABLE, prototypes

/* Helper: trim trailing newline, if any */
static void trim_newline(char *s) {
    if (s == NULL) return;
    size_t len = strlen(s);
    if (len > 0 && (s[len-1] == '\n' || s[len-1] == '\r')) {
        s[len-1] = '\0';
    }
}

/* Convert infix (with symbols) to postfix queue.
 * Uses hashtable to resolve symbols to integer values.
 */
QUEUE infix_to_postfix_symbol(HASHTABLE *ht, char *infixstr) {
    QUEUE postfix;
    STACK opstack;

    postfix.front  = NULL;
    postfix.rear   = NULL;
    postfix.length = 0;

    opstack.top    = NULL;
    opstack.height = 0;

    if (infixstr == NULL) {
        return postfix;
    }

    int i = 0;
    while (infixstr[i] != '\0') {
        char c = infixstr[i];
        int t = mytype(c);   /* 0-digit, 1-op, 2-'(', 3-')', 4-letter, 5-space */

        /* Ignore spaces */
        if (t == 5) {
            i++;
            continue;
        }

        /* Multi-digit number */
        if (t == 0) {
            int value = 0;
            while (infixstr[i] != '\0' && mytype(infixstr[i]) == 0) {
                value = value * 10 + (infixstr[i] - '0');
                i++;
            }
            NODE *np = new_node(value, 0);   // type 0 = number
            enqueue(&postfix, np);
            continue;
        }

        /* Symbol (variable name): one or more letters */
        if (t == 4) {
            char name[20];
            int k = 0;
            while (infixstr[i] != '\0' && mytype(infixstr[i]) == 4 &&
                   k < (int)sizeof(name) - 1) {
                name[k++] = infixstr[i];
                i++;
            }
            name[k] = '\0';

            int value = 0;
            HNODE *hnode = hashtable_search(ht, name);
            if (hnode != NULL) {
                value = hnode->data.value;
            }
            /* If symbol not found, value stays 0; tests should define
               symbols before use. */

            NODE *np = new_node(value, 0);   // store as number
            enqueue(&postfix, np);
            continue;
        }

        /* Left parenthesis */
        if (t == 2) {
            NODE *np = new_node(c, 1);       // treat '(' as operator-type node
            push(&opstack, np);
            i++;
            continue;
        }

        /* Right parenthesis: pop until '(' */
        if (t == 3) {
            NODE *np = pop(&opstack);
            while (np != NULL && (char)np->data != '(') {
                enqueue(&postfix, np);
                np = pop(&opstack);
            }
            if (np != NULL) {
                /* This was the '(' node; do not enqueue it */
                free(np);
            }
            i++;
            continue;
        }

        /* Operator +, -, *, /, % (mytype == 1) */
        if (t == 1) {
            char op = c;
            int p1 = priority(op);

            /* Pop operators from stack with higher or equal priority,
               stopping at '(' */
            NODE *top = opstack.top;
            while (top != NULL && (char)top->data != '(' &&
                   priority((char)top->data) >= p1) {
                NODE *popnode = pop(&opstack);
                enqueue(&postfix, popnode);
                top = opstack.top;
            }

            NODE *np = new_node(op, 1);  // type 1 = operator
            push(&opstack, np);
            i++;
            continue;
        }

        /* For any other characters (e.g., ';'), just skip. */
        i++;
    }

    /* Pop remaining operators from stack */
    NODE *np = pop(&opstack);
    while (np != NULL) {
        if ((char)np->data != '(' && (char)np->data != ')') {
            enqueue(&postfix, np);
        } else {
            free(np);
        }
        np = pop(&opstack);
    }

    return postfix;
}

/* Evaluate symbolic infix expression: infix -> postfix -> value */
int evaluate_infix_symbol(HASHTABLE *ht, char *infixstr) {
    QUEUE postfix = infix_to_postfix_symbol(ht, infixstr);
    /* Use the existing evaluate_postfix defined in expression.c */
    int value = evaluate_postfix(postfix);
    return value;
}

/* Evaluate statement like "b = (a+3)*2;" and update the hashtable. */
DATA evaluate_statement(HASHTABLE *ht, char *statement) {
	DATA result;
	    result.name[0] = '\0';
	    result.value = 0;

	    if (statement == NULL) {
	        return result;
	    }

	    trim_newline(statement);

	    /* Find '=' */
	    char *eq = strchr(statement, '=');

	    /* CASE 1: no '=' → treat as a variable lookup, e.g. "b" or "k" */
	    if (eq == NULL) {
	        char lname[20];
	        int li = 0;
	        char *p = statement;

	        /* extract symbol name: letters up to ';' or end */
	        while (*p != '\0' && *p != ';' && li < (int)sizeof(lname) - 1) {
	            if ((*p >= 'A' && *p <= 'Z') || (*p >= 'a' && *p <= 'z')) {
	                lname[li++] = *p;
	            }
	            p++;
	        }
	        lname[li] = '\0';

	        if (li == 0) {
	            /* no valid name found → return null */
	            return result;
	        }

	        /* look it up in the hashtable */
	        HNODE *hn = hashtable_search(ht, lname);
	        if (hn != NULL) {
	            /* found: return its stored DATA */
	            strncpy(result.name, hn->data.name, sizeof(result.name) - 1);
	            result.name[sizeof(result.name) - 1] = '\0';
	            result.value = hn->data.value;
	        }
	        /* if not found, result.name stays empty → public test prints "null" */
	        return result;
	    }

	    /* CASE 2: normal assignment: lhs = rhs */

	    /* Parse left-hand side symbol name (letters before '=') */
	    char lname[20];
	    int li = 0;
	    char *p = statement;
	    while (p < eq && *p != '\0') {
	        if ((*p >= 'A' && *p <= 'Z') || (*p >= 'a' && *p <= 'z')) {
	            if (li < (int)sizeof(lname) - 1) {
	                lname[li++] = *p;
	            }
	        }
	        p++;
	    }
	    lname[li] = '\0';

	    /* Copy to DATA.name */
	    strncpy(result.name, lname, sizeof(result.name) - 1);
	    result.name[sizeof(result.name) - 1] = '\0';

	    /* Extract right-hand side expression (from after '=' up to ';' or end) */
	    char expr[256];
	    int ei = 0;

	    char *rhs = eq + 1;
	    while (*rhs != '\0' && *rhs != ';' && ei < (int)sizeof(expr) - 1) {
	        expr[ei++] = *rhs;
	        rhs++;
	    }
	    expr[ei] = '\0';

	    /* Evaluate the right-hand side symbolic infix expression */
	    int value = evaluate_infix_symbol(ht, expr);
	    result.value = value;

	    /* Store/update the variable in the hash table */
	    hashtable_insert(ht, result);

	    return result;
	}
