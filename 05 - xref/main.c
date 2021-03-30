/*
 * 	Course:		    COMP-381 Systems Programming
 * 	Program:	    getword.c
 * 	Description:    fetching a word
 * 	Author:		    Simon Spivey
 * 	Date:		    03/16/21
*/

#include <stddef.h> //EOF
#include <ctype.h> //null
#include <stdio.h> //IO
#include <string.h> //strcmp
#include "xref.h"

#define MAXWORD 100

int linenumber = 1;

int getword(char *, int);
int binsearch(char *, struct key *, int);

int a = 0x043;
int _a = 0x043;

// find C keywords 

/*
xref3 -i in.c, 
xref3 -o out.txt
xref3 -i in.c -o out.txt
xref3 -o out.txt -i in.c
*/

/*
stdin --> scanf
stoud --> printf
file input --> https://www.tutorialspoint.com/cprogramming/c_file_io.htm
*/

int main(int argc, char *argv[])
{
	FILE *fp;
	char word[MAXWORD];

	printf("%d arguments\n", argc);

	if (argc == 1) { //read from stdin and write to stdout. no use of argv
		printf("No arugments received. Please input text to xref.\n");
		//scanf("")
	}
	else if (argc == 2) { //file input and write to stdout
		if (!strstr(argv[1], ".")) { //does the arg contain a '.'
			perror("Input argument was not a valid file type.\n");
			return 2;
		} 
		fp = fopen(argv[1], "r"); //open the file for read only

		if (fp == NULL) {
			perror("File could not be found.");
			return 2;
		}

		//fscanf(fp, "%s", word); //puts file lines into word
		//printf("%s", word);
	}
	else if (argc == 3) { //read from stdin and write to output file
		if (!strstr(argv[1], ".")) { //does the arg contain a '.'
			perror("Input argument was not a valid file type");
			return 1;
		} 
		if (!strstr(argv[2], ".txt")) { //does the arg contain a '.'
			perror("Ouput file argument needs to be a .txt file");
			return 1;
		} 
		fp = fopen(argv[1], "r"); //open the file for read only
		fp = fopen(argv[2], "w"); //open the file for write only
		fputs(word, fp); //puts file lines into word

	}
	else if (argc > 3 && argc < 7) {
		//xref3
	}
	else {
		perror("Too many arguments were received.");
		return 1;
	}
	struct tnode* root = NULL;

	while((fscanf(fp, "%s", word) > 0) && argc > 1) {
		fgets(word, MAXWORD, fp);
		while(getword(word, MAXWORD) != EOF) {
			if(isalpha(word[0]) || word[0] == '_') {
				if (binsearch(word, keytab, KEYS) < 0){
					root = addtree(root, word, linenumber);
				}
			}
		}	
	}

	treeprint(root);
	return 0;
}

// binsearch: find word in tab [0] -> tab[n-1] 
int binsearch(char *word, struct key tab[], int n)
{
	int cond;
	int low, high, mid;

	low = 0;
	high = n - 1;
	while (low <= high) {
		mid = (low+high) / 2; //set the middle point
		if ((cond = strcmp(word, tab[mid].word)) < 0)
			high = mid - 1;
		else if (cond > 0)
			low = mid + 1;
		else{
			return mid;
		}
	}
	return -1;
}

// getword: get next word or character from input 
int getword(char *word, int lim)
{
	int c;
	char *w = word;
	// isspace checks for if the character is whitespace
	while ((c = getch()) != EOF && (isspace(c) || !checkVar(c) || inComment(c) || inInclude(c)))
		if (c == '\n')
			linenumber++;
	if (c != EOF)
		*w++ = c;
	if (!isalnum(c) && c != '_') {
		*w = '\0';
		return c;
	}
	for ( ; --lim > 0; w++)
		if (!isalnum(*w = getch()) && *w != '_') {
			ungetch(*w);
			break;
		}
	*w = '\0';
	return word[0];
}
