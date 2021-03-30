/*
 * 	Course:		    COMP-381 Systems Programming
 * 	Program:	    getop.c
 * 	Description:    get next operator or operand
 * 	Author:		    Simon Spivey
 * 	Date:		    02/04/21
*/

#include <stdio.h>
#include <ctype.h>
#include "calc.h"

 int getch(void);
 void ungetch(int);

/* getop: get next character or numeric operand */
int getop(char s[]) {
	int i, c;
 	while ((s[0] = c = getch()) == ' ' || c == '\t');
	s[1] = '\0';

	//add stuff
	if (c == '=') { //we are assigning vars with =
		s[1] = getch();
		s[2] = '\0';
		return ASSIGNVAR;
	}

	if(islower(c)) { //if our input char is lowercase, not assigning
		return VAR;
	}

	if (!isdigit(c) && c != '.' && c != '-') {
		if (c == 'Q')
			c = EOF;
		return c;
	}

 	i = 0;
	if (c == '-') {
		c = getch();
		s[++i] = c;
		s[i+1] = '\0';

		if (!isdigit(c) && c != '.') {
			ungetch(c);
			s[i] = '\0';
			return '-';
		}
	}


	if (isdigit(c)) /* collect integer part */
 		while (isdigit(s[++i] = c = getch()));

 	if (c == '.') /* collect fraction part */ 
 		while (isdigit(s[++i] = c = getch()));

 	s[i] = '\0';

 	if (c != EOF)
 		ungetch(c);

 	return NUMBER;
}
