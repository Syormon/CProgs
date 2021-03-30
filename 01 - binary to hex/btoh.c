#include <stdio.h>
#include <string.h>


char btoh_hi(char High[]) { //unsigned char byte
    int value = 0;
    for (int i = 4; i > 0; i--) {
        value += (int)(High[i]) * (1 << i);
    }
    char c = (char) value;
    return (c);
}

char btoh_lo(char Low[4]) {
    int value = 0;
    for (int i = 4; i > 0; i--) {
        value += (int)(Low[i]) * (1 << i);
    }
    char c = (char) value;
    return (c);
}

int main(int argc, char *argv[]) {

    if (argc != 2) { //return 'error exception' if we don't have an runtime argument
        printf("Expected 1 argument --> %d argument(s) supplied\n", argc); //throw semi-detailed error
        return -1; //we don't have the expected amount of arguments
    }

    if (strlen(argv[1]) != 1 ) {
        perror("input char was not of length 1");
        return -1;
    }

    char c = getchar();

    if (c > 128) {
        perror("Char outside of range of available chars");
        return -1;
    }
    printf("Hex Value:\n");

    char high[4];
    char low[4];
    int j = 0;

    //basically masking with 0x80 --> 1000 0000 and moving 1 bit over right
    for (int i = 7; i >= 4; --i) { //index through higher nibble
        high[j] = ((c & (1 << i)) ? 1 : 0);
        j++;
    }
    
    j = 0;
    for (int i = 3; i >= 0; --i) { //index through lower nibble 
        low[j] = ((c & (1 << i)) ? 1 : 0); 
        j++;
    }

    char h = 0;
    char l = 0;
    j = 0;
    for (int i = 3; i > 0; i--) { //assigning values in decimal after bit shifting
        h += (int)(high[i]) * (1 << j);
        l += (int)(low[i]) * (1 << j);
        j++;
    }
    printf("%d", h); //print bits
    printf("%d\n", l);
}