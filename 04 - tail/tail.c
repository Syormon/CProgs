/*
 * 	Course:		    COMP-381 Systems Programming
 * 	Program:	    tail.c
 * 	Description:    main file for reading std-in
 * 	Author:		    Simon Spivey
 * 	Date:		    02/14/21
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define DEFLINES 10 // default # of lines to print 
#define LINES   100 // maximum # of lines to print 
#define MAXLEN  100 // maximum length of an input line

int mgetline(char *,int); //inteface

int main(int argc,char *argv[])
{
    char *p;
    char *buf;  // pointer to the large buffer 
    char *bufend;   // end of the large buffer 

    char line[MAXLEN];
    char *lineptr[LINES];   // pointer to lines read 
    
    int first,i,last,len,n,nlines;

    printf("%d args.\n", argc); //debugging - amount of input args

    // managing input arguments
    if( argc == 1) //set default if no # arg
        n = DEFLINES;

    else if(argc ==2 && (*++argv)[0] == '-') //if we have 2 args, set n as #
        n = atoi(argv[0]+1);
    else {//0 args or 3+ args should not pass
        printf("Usage: tail [-n] < 'file.txt'\n");
        exit(1);
    }

    //setting line count
    if( n < 1 || n > LINES) 
            n = LINES;
    //Should not have made it here - set n to LINES);

    //set ptrs to null.
    for(i = 0; i < LINES; i++)
            lineptr[i] = NULL; 

    if(( p = buf = malloc(LINES * MAXLEN)) == NULL) {//allocate memory of chars per line * lines
        printf("tail: cannot allocate buf\n");
        exit(1);
    }
    bufend = buf + LINES + MAXLEN; //set our buffer 

    last = 0;
    nlines = 0;

    //loop until EOF
    while((len = mgetline(line,MAXLEN)) > 0)
    {
        if(p+len+1 >= bufend)
            p = buf;
        lineptr[last] = p;

        //copy our str into ptr from line
        strcpy(lineptr[last],line);
        if(++last >= LINES)
            last = 0;

        p += len + 1;
        nlines++;
    }

    if( n > nlines) //catch to make sure it doesn't go over the limit
        n = nlines;

    first = last - n;

    if(first < 0)
        first += LINES;
    
    //print our output
    for(i= first; n-- > 0;i = (i+1) % LINES)
        printf("%s",lineptr[i]);

    printf("\n");
    return 0;
}

// read a line into s and return length 

int mgetline(char s[],int lim)
{
    int c,i;
    //lim is max char per line
    for(i=0; i<lim-1 && (c=getchar())!=EOF && c!='\n'; ++i)
        s[i] = c;

    if (c == '\n') { //increment i for new line
        s[i] = c;
        ++i;
    }

    s[i] = '\0';
    return i;
}
