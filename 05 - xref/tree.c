/*
 * 	Course:		    COMP-381 Systems Programming
 * 	Program:	    tree.c
 * 	Description:    tree structure and methods
 * 	Author:		    K&R2 page 140 - Revised by Simon Spivey
 * 	Date:		    03/15/21
*/
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX 100
// tnode:  Words are initially read into the tree by getword.
struct tnode
{
    char *word;
    int count;
    int lines[MAX];
    struct tnode *left;
    struct tnode *right;
};

struct tnode* talloc(void);
char* mstrdup(char*);

struct tnode *addtree(struct tnode* p, char* w, int linenumber)
{
    int cond;

    if(p == NULL) { /* new word */
        p = talloc();
        p->word = mstrdup(w);
        p->count = 1;
        p->left = p->right = NULL;
        p->lines[0] = linenumber;
    }

    else if((cond = strcmp(w, p->word)) == 0) {
        p->count++;
        p->lines[p->count - 1] = linenumber;
    }

    else if(cond < 0)
        p->left = addtree(p->left, w, linenumber);
    
    else
        p->right = addtree(p->right, w, linenumber);
        
    return p;
}

// treeprint: Prints tree p in-order. pg 126 
void treeprint(struct tnode *p)
{
    int i;

    if(p != NULL) {
        treeprint(p->left);
        printf("%-15s", p->word);

        for (i = 0; i < p->count; i++) {
            printf("%-5d", p->lines[i]);
        }
        printf("\n");

        treeprint(p->right); 
    }
}

// talloc: Makes a tnode. pg 127 
struct tnode *talloc(void) {
    return (struct tnode*) malloc(sizeof(struct tnode));
}

// mstrdup: Makes a duplicate of s. pg 127
char *mstrdup(char *s)
{
    char *p;
    p = (char *) malloc(strlen(s) + 1);
    if(p != NULL)
        strcpy(p, s);
    return p;
}