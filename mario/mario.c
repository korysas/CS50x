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

#define TRUE 1
#define FALSE 0


/* note that this method uses '\n' to look for the end of user input */
int get_input(char s[], int max_length);

// check if user input is made up of all digits (ints) should return 0 or 1
int is_all_digits(char s[]);

// check if a single character is a digit should return 0 or 1
int is_digit(char c);

// convert from character array to integer
int str_to_int(char s[]);


int main(void)
{
    int i, j, len, val;
    char s[MAX_INPUT_LENGTH];

    len = get_input(s, MAX_INPUT_LENGTH);
    val = str_to_int(s);

    // we are looking for a two digit number or less (reject large numbers)
    while (len > 2 || is_all_digits(s) == FALSE || val > MAX_HEIGHT)
    {
        len = get_input(s, MAX_INPUT_LENGTH);
        val = str_to_int(s);
    }

    for (i = 0; i < val; i++)
    {
        for (j = 0; j < val; j++)
        {
            if (j + 1 < val - i)
                putchar(' ');
            if (j + 1 >= val - i)
                putchar('#');

            if (j + 1 == val)
                putchar('\n');
        }
    }
    // i = 0;
    // while (s[i] != '\0')
    // {
    //     printf("%d, ", s[i]);
    //     i++;
    // }
    // printf("\n");
}

int get_input(char s[], int max_length)
{
    int c, i;

    printf("Height: ");

    for (i = 0; i < max_length - 1 && (c = getchar()) != EOF && c != '\n'; i++)
        s[i] = c;

    s[i] = '\0';

    // printf("string input: %s\n", s);

    return i;
}

int is_all_digits(char s[])
{
    int i = 0;
    while (s[i] != '\0')
    {
        if (is_digit(s[i]) == FALSE)
        {
            return FALSE;
        }

        i++;
    }

    return TRUE;
}

int is_digit(char c)
{
    if (c >= '0' && c <= '9')
        return TRUE;

    return FALSE;
}

int str_to_int(char s[])
{
    int result, i;

    if (is_all_digits(s) == FALSE)
        return '\0';

    result = 0;
    for (i = 0; s[i] != '\0'; i++)
    {
        result = 10 * result + (s[i] - '0');
    }

    // printf("result: %d\n", result);
    return result;
}


