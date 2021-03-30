/*
 * 	Course:		    COMP-381 Systems Programming
 * 	Program:	    getch.c
 * 	Description:    get and unget char from buffer
 * 	Author:		    Simon Spivey
 * 	Date:		    02/04/21
*/

#include <stdio.h>
#include "calc.h"

#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;
static double vars[26]; //26 uppercase letters

int getch(void) {
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {
	if (bufp >= BUFSIZE) {
		printf("too many characters\n");
	}
	else {
		buf[bufp++] = c;
	}
}

double getvar(char c) {
	if (!islower(c)) {
		printf("invalid var %c\n", c);
		return 0.0;
	}

	return vars[c-'a']; //convert
}

void setvar(char c, double val) {
	if (!islower(c)) {
		printf("invalid var %c\n", c);
		return;
	}

	vars[c-'a'] = val;
}

