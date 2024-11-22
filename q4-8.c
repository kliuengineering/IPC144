#include <stdio.h>
#include <string.h>
#define MAX 1001

struct Ribbon
{
    char line[MAX];
    int position;
    int length;
};


int readRibbons(const char filename[], struct Ribbon ribbons[], int maxCapacity)
{
    FILE *file = fopen(filename, "r");
    if(!file)
        return -1;

    int counter = 0;
    while( counter < maxCapacity && fgets(ribbons[counter].line, MAX, file) )
    {
        // let's find out the size of the string
        int len = strlen( ribbons[counter].line );

        // if the last char is enter key
        if( ribbons[counter].line[len - 1] == '\n' )
        {
            // then replace it with a null terminator
            ribbons[counter].line[ len - 1 ] = '\0';

            // decrements length by 1 so that we don't read the null
            len--;
        }

        // initializes the other member variables (requested by the problem statement)
        ribbons[counter].position = 0;
        ribbons[counter].length = len;

        counter++;
    }

    // don't forget to clean up
    fclose(file);
    return counter;
}


void advance(struct Ribbon* ribbon, int n) 
{
    if (ribbon == NULL) 
    {
        return;  // Null check to avoid dereferencing a null pointer to the ribbon
    }

    // Updates position based on 'n'
    ribbon->position += n;

    // Ensures position is within bounds; remember this for your exam
    if (ribbon->position < 0) 
    {
        ribbon->position = 0;
    } 
    else if (ribbon->position > ribbon->length) 
    {
        ribbon->position = ribbon->length;
    }
}


void overUnder(int n, struct Ribbon ribbons[], int size, int* over, int* under, int* equals) 
{
    // Initializes the counters to 0
    *over = 0;
    *under = 0;
    *equals = 0;

    // Loops through the ribbons array
    for (int i = 0; i < size; i++) 
    {
        if (ribbons[i].length > n) 
        {
            (*over)++;  // remember to deference for the exam!
        } else if (ribbons[i].length < n) 
        {
            (*under)++;
        } else 
        {
            (*equals)++;
        }
    }
}


int appendAtPosition(struct Ribbon* ribbon, const char str[]) 
{
    if (ribbon == NULL || str == NULL)  // if either one of those parameter is a corrupted piece of data
    {
        return -1; // then returns some kind of error code, let's use -1 here
    }

    int position = ribbon->position;  // The position to start the 'append'
    int strLength = strlen(str);      // Length of the string to 'append'

    // Checks if appending the string would exceed the maximum allowed size
    if (position + strLength > 1000) 
    {
        return -1; // Returns -1 if the new string would exceed the buffer size
    }

    // Copy & pastes the string starting at the position
    strcpy(&ribbon->line[position], str);

    // Updates the length of the ribbon (don't forget this)
    ribbon->length = position + strLength;

    return 0; // Return 0 to indicate success
}


void printRibbon(const char filename[], struct Ribbon ribbons[], int size, int longForm) 
{
    // Opens the file for writing stuff
    FILE *file = fopen(filename, "w");
    if (file == NULL) 
    {
        // if there's an issue with file opening, then we invokes an error
        fprintf(stderr, "Error: Could not open file %s for writing.\n", filename);
        return;
    }

    // Iterates through the ribbons array 
    for (int i = 0; i < size; i++) 
    {
        if (longForm) 
        {
            // Prints the text string and position if longForm is true
            fprintf(file, "%s; %d\n", ribbons[i].line, ribbons[i].position);
        } else 
        {
            // Prints only the text string if longForm is false
            fprintf(file, "%s\n", ribbons[i].line);
        }
    }

    // Closes the file
    fclose(file);
}


int main() 
{
    const int SIZE = 10;
    struct Ribbon ribbons[SIZE];  // Array to hold up to 10 ribbons
    int numRead = readRibbons("data.txt", ribbons, 10);

    if (numRead == -1) 
    {
        printf("Failed to open the file.\n");
        return 1;
    }



    // Q4
    printf("Number of lines read: %d\n", numRead);
    for (int i = 0; i < numRead; i++) 
    {
        printf("Ribbon %d: Line='%s', Position=%d, Length=%d\n",
               i, ribbons[i].line, ribbons[i].position, ribbons[i].length);
    }
    puts("");



    // Q5
    struct Ribbon myRibbon = {"hello world", 5, 11};
    printf("Before advancing: Position = %d\n", myRibbon.position);

    // Advance by +2
    advance(&myRibbon, 2);
    printf("After advancing by +2: Position = %d\n", myRibbon.position);

    // Advance by -8
    advance(&myRibbon, -8);
    printf("After advancing by -8: Position = %d\n", myRibbon.position);

    // Advance by +20 (beyond length)
    advance(&myRibbon, 20);
    printf("After advancing by +20: Position = %d\n", myRibbon.position);

    puts("");



    // Q6

    // Variables to store the result
    int over, under, equals;

    // Call the function with n = 10
    overUnder(10, ribbons, SIZE, &over, &under, &equals);

    // Print the results
    printf("Over: %d\n", over);
    printf("Under: %d\n", under);
    printf("Equals: %d\n", equals);

    puts("");



    // Q7

    // Example Ribbon struct
    struct Ribbon myRibbon2 = {"hot air balloon", 4, 16};

    printf("Before: %s (Length: %d)\n", myRibbon2.line, myRibbon2.length);

    // Append "dog" starting at position 4
    if (appendAtPosition(&myRibbon2, "dog") == 0) 
    {
        printf("After: %s (Length: %d)\n", myRibbon2.line, myRibbon2.length);
    } 
    else 
    {
        printf("Failed to append the string.\n");
    }



    // Q8
    // Example array of ribbons
    struct Ribbon ribbons3[] = 
    {
        {"hot dog", 4, 7},
        {"hello world", 0, 11},
        {"example string", 6, 14}
    };
    int size = 3;

    // Write ribbons in long form
    printRibbon("output_long.txt", ribbons3, size, 1);

    // Write ribbons in short form
    printRibbon("output_short.txt", ribbons3, size, 0);

    printf("Ribbon data has been written to the files.\n");

    return 0;
}