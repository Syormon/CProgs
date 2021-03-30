/*
 * 	Course:		    COMP-381 Systems Programming
 * 	Program:	    xref.h
 * 	Description:    header for xref
 * 	Author:		    Simon Spivey
 * 	Date:		    03/15/21
*/

#define KEYS 32

//getch.c
int getch(void);
void ungetch(int c);

//getword.c
int mgetword(char *word, int lin, int *lineno_addr);

//tree.c
struct tnode *addtree(struct tnode *p, char *w, int linenumber);
void treeprint(struct tnode *p);
struct tnode *talloc(void);
char *mstrdup(char *s);

//nc.c
int checkVar(char c);
int inComment(char c);
int inInclude(char c);

struct key {
	char *word;
} keytab[KEYS] ={
	"auto",
	"break",
	"case",
	"char",
	"const",
	"continue",
	"default",
	"do",
	"double",
	"else",
	"enum",
	"extern",
	"float",
	"for",
	"goto",
	"if",
	"int",
	"long",
	"register",
	"return",
	"short",
	"signed",
	"sizeof",
	"static",
	"struct",
	"switch",
	"typedef",
	"union",
	"unsigned",
	"void",
	"volatile",
	"while"
};