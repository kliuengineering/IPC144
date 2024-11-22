#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 20

// play with the following function and see what it does.
void foo(char s[])
{
    int i;
    for(i = 0; s[i] != '\0'; i++)
    {
        if(i % 2 == 0)
        {
            s[i] = toupper(s[i]);
        }
        else
            s[i] = tolower(s[i]);
    }
}

void main(void)
{
    char s1[MAX] = "Hello ";
    char s2[MAX] = "World.";
    char s3[MAX] = "Hello ";
    char s4[MAX] = "Oh ";
    char s5[MAX] = "Uhm Uhm ";

    // p1
    // returns 0 if True
    if(strcmp(s1, s3))
        printf("False");
    else
        printf("True");
    puts("");

    // p2
    // need to make sure size is big enough
    // why is there no return value of strcat() ?
    strcat(s1, s3);
    printf("%s\n", s1);

    // p3
    // is it going to run if the size of s4 is smaller than the size of s1?
    strcpy(s4, s1);
    printf("%s\n", s4);
    
    // p4 
    // what should be the output like? will s4 string get replaced completely after copy?
    strncpy(s4, s5, 4);
    printf("%s\n", s4);

    // p5
    // can we make some use of the following common string functions?
    // the toupper(), tolower() are quite useful.
    /*
    toupper(int ch): Converts a character to uppercase if it is a lowercase letter.
    tolower(int ch): Converts a character to lowercase if it is an uppercase letter.
    isalpha(int ch): Returns non-zero if ch is an alphabetic character.
    isdigit(int ch): Returns non-zero if ch is a digit (0–9).
    isalnum(int ch): Returns non-zero if ch is alphanumeric.
    isspace(int ch): Returns non-zero if ch is a whitespace character (space, tab, newline, etc.).
    ispunct(int ch): Returns non-zero if ch is a punctuation character.
    isupper(int ch): Returns non-zero if ch is an uppercase letter.
    islower(int ch): Returns non-zero if ch is a lowercase letter.
    */
}