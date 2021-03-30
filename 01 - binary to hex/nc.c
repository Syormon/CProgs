/*
 * 	Course:		COMP-381 Systems Programming
 * 	Program:	nc.c
 * 	Descirption:	Removes Comments froma C source Program
 * 	Author:		Simon Spivey
 * 	Date:		1/20/2021
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

int main(int argc, char *argv[]) { //argc is the amount of arguments, argv[] is array of each argument
	//This string would represent the code from a C file with comments; Realistically, we would use a inputstream writer 

    if (argc != 2) { //return 'error exception' if we don't have an runtime argument
        printf("Expected 1 argument --> %d argument(s) supplied\n", argc); //throw semi-detailed error
        return -1; //we don't have the expected amount of arguments
    }

    printf("%s", argv[1]);
    //should be argv[1] instead of test.txt
    FILE *f = fopen(argv[1], "r"); //declaring file to read from
    if (f == NULL) { //makes sure we don't have an empty/null param
        perror("Null pointer for file argument: file not found\n"); //throw null pointer exception
        return -1; //return error code
    }

    int length = 300; //calulcate length of input param string 

    char *prgm = malloc(length); //make allocation of equal size to input param --> FIXME

    char c;
    int x = 0;

    while ((c = getc(f)) != EOF) {
        prgm[x] = c;
        x++;
    }

    fclose(f); //close our I/O reader

    //if (fgets(prgm, length, f) != NULL) { //checks to make sure our input string is not null
        //puts(prgm); //places our string into our prgm[] 
    //}


    printf("The argument supplied is:\n\n %s\n", prgm); //test

    char *result = malloc(length); //declaring an empty string => can't use n because its not static but strlen is not a static returning method?

    bool s_cmt = false; //single line comment flag
    bool l_cmt = false; //line or block comment flag
    int i; //declaring i outside the for loop --> my WSL works great with or without; I think our school uses an outdated GCC compilier

    for (i = 0; i < length; i++) { //looping through our pgrm string
        
        if (s_cmt == true && prgm[i] == '\n') { //contrary to first thought, '/n' is considering one char :: ASCII value of 10
                s_cmt = false; //If the single comment boolean is flagged and the end line char appears, unmark the single comment flag.
            }

            else if (l_cmt == true && prgm[i] == '*' && prgm[i+1] == '/') { //if line comment is true and the ending two chars, / & * are present, unmark the flag
                l_cmt = false; //reset the flag
                result[i] = ' '; //set /* to blank chars
                result[i+1] = ' ';
                i++;
            }

            else if (s_cmt || l_cmt) { //if either flags are currently raised, return an empty char
                result[i] = ' ';
            }

            else if(prgm[i] == '/' && prgm[i+1] == '/') { //if we see //, we check the single line flag, and replace // with an empty chars.
                s_cmt = true,
                printf("// flag marked true\n");
                result[i] = ' ';
                result[i+1] = ' ';
                i++;
            }
            else if(prgm[i] == '/' && prgm[i+1] == '*') { //if we see the /* chars, we check the line comment flag and replace /* with empty chars.
                l_cmt = true;
                printf("/* flag marked true\n");
                result[i] = ' ';
                result[i+1] = ' ';
                i++;
            }

            else { //if neither flag is checked and none of the comment chars are appearing, copy the char from the original string.
                result[i] = prgm[i];
            }
    }
    printf("\nWith Comments Removed:\n\n");
    printf("%s", result); //print our result - %s lets the printf method know we want to print a string
    return 0;
}


