/*
 * 	Course:		    COMP-381 Systems Programming
 * 	Program:	    calc.h
 * 	Description:    header for calc.c
 * 	Author:		    Simon Spivey
 * 	Date:		    02/04/21
*/

#define NUMBER '0'
#define VAR 'v'
#define ASSIGNVAR 'a'

void push(double);
double pop(void);
void clear(void);
int getch(void);
void ungetch(int);
int getop(char []);
double getvar(char c);
void setvar(char c, double val);
