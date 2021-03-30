/*
 * 	Course:		    COMP-381 Systems Programming
 * 	Program:	    itob.c
 * 	Descirption:	converts int in decimal to base n
 * 	Author:		    Simon Spivey
 * 	Date:		    1/31/2021
*/
#include<stdio.h>
#include<string.h>

//interfacing methods
void itob(int n,char s[],int b); 
void reverse(char s[]);

//main
int main() {
    int b, n; //instanation
    char str[100];

    printf("Enter a base n: >>");
    scanf("%d", &b);

    printf("Enter a number in decimal: >>");
    scanf("%d", &n);


    itob(n,str,b); //calling itob method, will not return anything but instead change the variable str as it as a pointer not a memcpy

    printf("\nOutput: ");
    printf("%s\n",str); //output string nicely

    return 0;
}

void itob(int n, char s[], int b) {
    int i,j,z_flag;

    if((z_flag = n) < 0) { //z_flag is a boolean bit that is marked negative if a signed integer has MSB
        n = -n;
    }

    i = 0;
    do {
        j = n % b; //modulus gives us remainder
        
        if (j <= 9) { //these are our carries; if we as pass 9 (the end of decimal vales), we start keeping track of carry bits
            s[i] = j + '0'; //arbritary constant of 48
        } 
        else {
            s[i] = j + 'a' - 10; //arbritary constant of 87
        }
        
        i++;

    } while ((n /= b) > 0); //divides the left operand with the right operand and assigns the result to the left operand.

    if (z_flag < 0) { //if our z_flag is flagged, append a negative
        s[i] = '-';
        i++;
    }
    
    s[i] = '\0'; //add end char
    reverse(s); //reverse our output str as it is flipped
}

void reverse(char s[]) {
    int i,j,temp;

    //to reverse the word, doing a bubble sort-esc like sorter
    for (i=0, j=strlen(s)-1; i < j; i++, j--) { //this is a double for loop where i increments up and j goes down 
        temp = s[i];
        s[i] = s[j];
        s[j] = temp;
    }
}
