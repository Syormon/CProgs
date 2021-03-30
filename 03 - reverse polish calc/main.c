/*
 * 	Course:		    COMP-381 Systems Programming
 * 	Program:	    main.c
 * 	Description:    main driver for calculator program
 * 	Author:		    Simon Spivey
 * 	Date:		    02/04/21
*/

#include <stdio.h>
#include <stdlib.h> //for atof() method
#include <math.h>
#include "calc.h"

#define MAXOP 100 //max size of operand/operator

int main() {
	int type;
	double op2;
	char s[MAXOP];


	while((type = getop(s)) != EOF) {  //EOF = END OF FILE
		switch(type) {
			case NUMBER:
				push(atof(s));
				break;
			case '+':
				push(pop() + pop());
				break;
			case '*':
				push(pop() * pop());
				break;
			case '-':
				op2 = pop();
				push(pop() - op2);
				break;
			case '/':
				op2 = pop();
				if (op2 != 0.0) {
					push(pop() / op2);
				}
				else {
					printf("Error: Zero Divisor.\n");
				}
				break;
			//==========================================
			case '%':
				op2 = pop();
				push((int)pop() % (int)op2);
				break;
			case 'A':
				push(op2);
				break;
			case 'D':
				op2 = pop();
				push(op2);
				push(op2);
				break;
			case 'S':
				op2 = pop();
				push(pop());
				push(op2);
				break;
			case 'C':
				clear();
				break;
			case '$':
				op2 = sin(pop());
				push(op2);
				break;
			case 'E':
				op2 = exp(pop());
				push(op2);
				break;
			case '^':
				push(pow(pop(), pop()));
				break;
			case VAR:
				push(getvar(s[0]));
				break;
			case ASSIGNVAR:
				if (s[1] != '\0')
					op2 = pop();
					setvar(s[1], op2);
					push(op2);
					printf("Value %.8g saved to Variable %c.\n", op2, s[1]);
				break;
			//==========================================
			case '\n':
				op2 = pop();
				printf("\t%.8g\n", op2);
				break;
			default:
				printf("Unknown Command %s\n", s);
				break;
			}
	}
	return 0;
}

