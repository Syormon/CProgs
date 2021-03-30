/*
 * 	Course:		    COMP-381 Systems Programming
 * 	Program:	    getword.c
 * 	Description:    fetching a word - comination of nc.c and some new code
 * 	Author:		    Simon Spivey
 * 	Date:		    02/22/21
*/

#define IN 1
#define OUT 0
#define EOF -1
#include <ctype.h>

int mgetword(char *word, int lim, int *lineno_addr)
{
    int c, d, getch(void), comment, string, directive;
    void ungetch(int);
    char *w = word;

    comment = string = directive = OUT;

    while (isspace(c = getch())) {
        if (c == '\n') {

            *lineno_addr = *lineno_addr +1;

        }
    }

    /* Check if inside a comment */

    if (c == '/') {
        if ((d = getch()) == '*') {
            comment = IN;
        } else {
            comment = OUT;
            ungetch(d);
        }
    }

    /* Check if inside a quote */

    if ( c == '\"') {
        string = IN;
    }

    /* Check if inside a directive */

    if (c == '#') {
            directive = IN;
    }

    if ( c == '\\') {
        c = getch(); /* ignore the \\ character */
    }

    if (comment == OUT && string == OUT && directive == OUT) {

        if (c != EOF)
            *w++ = c;

        if (!isalnum(c) && c !='_' ) {
            *w = '\0';
            return c;
        }

        for ( ; --lim > 0; w++) {
            *w = getch();
            if (!isalnum(*w) && *w != '_') {
                ungetch(*w);
                break;
            }
        }
        *w = '\0';
        return word[0];
    }
    else if ( comment == IN) {
        *w++ = c;
        *w++ = d;

        while ((*w++ = c = getch())) {
            if ( c == '*' ) {
                if ( (c = getch()) == '/' ) {
                    *w++ = c;
                    comment = OUT;
                    break;
                } else {
                    ungetch(c);
                }
            }
        }
        *w = '\0';

    }
    else if ( string == IN) {
        *w++ = c;
        while ((*w++ = getch()) != '\"') {
            if ( *w == '\\')  /* Take care of escaped quotes */
                *w++ = getch();
        }
        string = OUT;
        *w = '\0';
    }
    else if (directive == IN) {
        *w++ = c;
        while ((*w++ = getch()) != '\n') {
            if ( c == '\\') { /* Take care of continuation line escape */
                *w++ = getch();
            }
        }
        directive = OUT;
        *w = '\0';
    }

    return c;

}