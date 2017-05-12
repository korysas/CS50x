/*
    Program that takes in a users name and prints out their initials
*/

#include <stdio.h>
#include <ctype.h>

#define MAX_LENGTH 1000

// get a string from the user in a terminal window, end when they hit a new line character
void get_string(char s[]);

int main(void)
{
    char s[MAX_LENGTH];

    get_string(s);

    int i = 0;
    while (s[i] != '\0')
    {
        if (i == 0 && s[0] != ' ' && s[0] != '\t')
        {
            putchar(toupper(s[i]));
        }

        if (s[i] != ' ' && s[i] != '\t' && (s[i - 1] == ' ' || s[i - 1] == '\t'))
        {
            putchar(toupper(s[i]));
        }

        i++;
    }

    putchar('\n');
}

void get_string(char s[])
{
    char c;
    int i = 0;

    // keep getting chars until we hit a newline    
    while ((c = getchar()) != '\n')
    {
        // place chars in array to build the string
        s[i] = c;
        i++;
    }

    // delimit string with null character
    s[i] = '\0';
}


