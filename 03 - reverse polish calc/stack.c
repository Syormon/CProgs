/*
 * 	Course:		    COMP-381 Systems Programming
 * 	Program:	    stack.c
 * 	Description:    ush and pop from stack data structure
 * 	Author:		    Simon Spivey
 * 	Date:		    02/04/21
*/

#include <stdio.h>
#include "calc.h"

#define MAXVAL 100

int sp = 0;
double val[MAXVAL];

void push(double f) {
	if (sp < MAXVAL) {
		val[sp++] = f;
	}
	else {
		printf("stack is full. %g not pushed.\n", f);
	}
}

double pop(void) {
	if (sp > 0) {
		return val[--sp];
	}
	if (sp == -1) {
		printf("Stack cleared.\n");
		sp = 0;
	}
	else {
		printf("Can not pop empty stack.\n");
		return 0.0;
	}
}

void clear(void) {
	sp = -1;
}

