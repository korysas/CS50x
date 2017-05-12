/*
    From a user's integer input build via text a Mario-like pyramid using hashes (#).
    Program should reject negative numbers and re prompt for the height
    we should also only accept input that is less than some specified maximum.

    Example:

    User input: 4
       #  #
      ##  ## 
     ###  ###
    ####  ####
*/

#include <stdio.h>

#define MAX_HEIGHT 23
#define MAX_INPUT_LENGTH 1024

int get_input(char s[], int max_length)
{
    int c, i;

    printf("Height: ");

    for (i = 0; i < max_length - 1 && (c = getchar()) != EOF && c != '\n'; i++)
    {
        s[i] = c;
    }

    s[++i] = '\0';

    return i;
}

int main(void)
{
    char s[MAX_INPUT_LENGTH];

    int len = get_input(s, MAX_INPUT_LENGTH);

    int i = 0;
    while (s[i] != '\0')
    {
        putchar(s[i]);
        i++;
    }
}


