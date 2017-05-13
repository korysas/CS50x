/*
    program that encrypts a message using Caesar's cipher
    each letter of the plain text is offset by some fixed amount

    e.g. HELLO --> URYYB
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_INPUT_LENGTH 1000
#define TRUE 1
#define FALSE 0

void get_string(char s[]);

int is_all_digits(char *s);

int main(int argc, char **argv)
{

    // check if we execute the program correctly with a positive integer
    if (argc != 2)
    {

        printf("Usage: ./caesar <positive int>\n");
        return 1;
    }

    if (is_all_digits(argv[1]) == FALSE)
    {
        printf("Usage: ./caesar <positive int>\n");
        return 1;
    }

    int offset = atoi(argv[1]);

    if (offset < 1)
    {
        printf("Usage: ./caesar <positive int>\n");
        return 1;
    }


    // get the user's plaintext input
    char s[MAX_INPUT_LENGTH];
    printf("plaintext: ");
    get_string(s);

    int i = 0;
    while (s[i] != '\0')
    {
        int offset_char = s[i] + (offset % 26);

        // printf("%d : %d\n", s[i], offset_char);

        if (s[i] >= 65 && s[i] <= 90 && offset_char >= 91)
        {
            s[i] = 'A' + offset_char - 91;
        }

        else if (s[i] >= 97 && s[i] <= 122 && offset_char > 122)
        {
            s[i] = 'a' + offset_char - 123;
        }

        else if (s[i] < 65 || s[i] > 122 || (s[i] > 90 && s[i] < 97))
        {

        }

        else
        {
            s[i] = offset_char;
        }

        i++;
    }

    printf("ciphertext: %s\n", s);
}

// get user input string, ends when user presses new line character
void get_string(char *s)
{
    int c, i;
    i = 0;
    while ((c = getchar()) != '\n')
    {
        s[i] = c;
        i++;
    }

    s[i] = '\0';
}

int is_all_digits(char *s)
{
    int i = 0;
    while (s[i] != '\0')
    {
        if (isdigit(s[i]) == FALSE)
        {
            return FALSE;
        }

        i++;
    }

    return TRUE;
}




