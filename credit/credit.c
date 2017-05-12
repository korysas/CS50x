/*
    Program that validates a credit card using Luhn's algorithm
*/

#include <stdio.h>

#define MAX_INPUT_LENGTH 1024
#define TRUE 1
#define FALSE 0

// note that this method uses '\n' to look for the end of user input
int get_input(char s[], int max_length, char prompt[]);

// check if user input is made up of all digits (ints) should return 0 or 1
int is_all_digits(char s[]);

// check if a single character is a digit should return 0 or 1
int is_digit(char c);

// convert from character array to integer
int char_to_int(char c);

// return the sum of a number digits (e.g. 18 --> 9), we assume that the maximum input
// is 18 because Luhn's alogrithm calls for a single digit multiplied by 2
int sum_of_digits(int num);


int main(void) 
{
    char s[MAX_INPUT_LENGTH];

    int len = get_input(s, MAX_INPUT_LENGTH, "Number");

    while (is_all_digits(s) == FALSE)
    {
        len = get_input(s, MAX_INPUT_LENGTH, "Number");
    }

    // Luhn's algorithm check
    int every_other_times_two[len / 2];
    int i, j, product_digits_sum, final_sum;

    for (i = (len % 2 == 0 ? 0 : 1), j = 0; i < len; i++, j++)
    {
        // printf("%d", char_to_int(s[i]));

        every_other_times_two[j] = char_to_int(s[i]) * 2;

        // increment i here to skip every other
        i++;
    }

    product_digits_sum = 0;
    for (i = 0; i < len / 2; i++)
    {
        product_digits_sum += sum_of_digits(every_other_times_two[i]);
    }

    // printf("Product digits sum: %d\n", product_digits_sum);

    final_sum = 0;
    for (i = (len % 2 == 0 ? 1 : 0); i < len; i++)
    {
        // printf("every other: %d\n", char_to_int(s[i]));
        final_sum += char_to_int(s[i]);
        i++;
    }

    final_sum += product_digits_sum;

    // printf("Sum: %d\n", final_sum);

    if (final_sum % 10 == 0)
    {
        if (s[0] == '3')
            printf("AMEX\n");
        else if (s[0] == '4')
            printf("VISA\n");
        else
            printf("MASTERCARD\n");
    }
    else
    {
        printf("INVALID\n");
    }

    return 0;
}

int get_input(char s[], int max_length, char prompt[])
{
    int c, i;

    printf("%s: ", prompt);

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

int char_to_int(char c)
{
    return c - '0';
}

int sum_of_digits(int num)
{
    if (num / 10 < 1)
    {
        return num;
    }

    int result;
    result = (num / 10) + (num % 10);

    return result;
}

