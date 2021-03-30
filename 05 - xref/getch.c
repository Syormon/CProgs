/*
 * 	Course:		    COMP-381 Systems Programming
 * 	Program:	    getch.c
 * 	Description:    get char and previous char
 * 	Author:		    K&R2, page 79 - Revised by Simon Spivey
 * 	Date:		    02/22/21
*/

#include <stdio.h>

#define BUFSIZE 100

char buf[BUFSIZE];  // buffer for ungetch() 
int bufp = 0;       // next free position in buf 

int getch(void) { // get a (possibly pushed back) character 
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {  // push character back on input 
    if(bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

// checkVar: returns false when character is in single or double quotes 
int checkVar(char c){
	// check for double quotes 
	if(c == '\"') {
		while((c = getch()) != '\"'){
		}
		return 0;
	}
	// check for single quotes 
	if(c == '\'') {
		while((c = getch()) != '\''){
		}
		return 0;
	}
	return 1;
}

// inComment: ignores anything in a comment 
int inComment(char c){
	char d = getch();
	// checks for start of a comment 
	if (c == '/' && d == '*') {
		// loops through characters until end of comment 
		while (!(c == '*' && d == '/')) {
			c = d;
			d = getch();
		}
		return 1;
	} else {
		// release second last character
		ungetch(d);
		return 0;
	}
}

// inInclude: ignores any line that starts with # 
int inInclude(char c){
	if (c == '#') {
		while (c != 10) {
			c = getch();
		}
	}
	return 0;
}