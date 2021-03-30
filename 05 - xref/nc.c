/*
	    Course:         COMP-381 Systems Programming
        Program:        nc.c
        Description:    ignoring comments
        Author:         Simon Spivey
        Date:           03/15/21
*/
#include "xref.h"

/* checkVar: returns false when character is in single or double quotes */
int checkVar(char c){
	/* check for double quotes */
	if(c == '\"') {
		while((c = getch()) != '\"'){
		}
		return 0;
	}
	/* check for single quotes */
	if(c == '\'') {
		while((c = getch()) != '\''){
		}
		return 0;
	}
	return 1;
}

/* inComment: ignores anything in a comment */
int inComment(char c){
	char d = getch();
	/* checks for start of a comment */
	if (c == '/' && d == '*') {
		/* loops through characters until end of comment */
		while (!(c == '*' && d == '/')) {
			c = d;
			d = getch();
		}
		return 1;
	} else {
		/* release second last character */
		ungetch(d);
		return 0;
	}
}

/* inInclude: ignores any line that starts with # */
int inInclude(char c){
	if (c == '#') {
		while (c != 10) {
			c = getch();
		}
	}
	return 0;
}