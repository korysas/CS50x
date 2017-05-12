/*
    Program that attempts to crack a password

    We simplify this by assuming that the password:
        1. has a length of 4
        2. consits only of alphabetical chars (upper and lower)
        3. has been hashed with crypt function
*/

#define _XOPEN_SOURCE

#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Usage: ./crack <hash>");
        return 1;
    }

    char salt[] = { '5', '0' };

    int i, j, k, l;
    char *hash;
    char pass_attempt[5];

    for (i = 'A'; i <= 'z'; i++)
    {
        if (i >= 91 && i <= 96) continue;
        for (j = '\0'; j <= 'z'; j++)
        {
            if ((j >= 91 && j <= 96) || (j > '\0' && j < 'A')) continue;
            for (k = '\0'; k <= 'z'; k++)
            {
                if ((k >= 91 && k <= 96) || (k > '\0' && k < 'A')) continue;
                for (l = '\0'; l <= 'z'; l++)
                {
                    if ((l >= 91 && l <= 96) || (l > '\0' && l < 'A')) continue;
                    pass_attempt[0] = i;
                    pass_attempt[1] = j;
                    pass_attempt[2] = k;
                    pass_attempt[3] = l;
                    pass_attempt[4] = '\0';                    
                    
                    printf("%s\n", pass_attempt);

                    hash = crypt(pass_attempt, salt);
                    // check if we have a match
                    if (strcmp(hash, argv[1]) == 0)
                    {
                        printf("input hash: %s\n", argv[1]);
                        printf("computed hash: %s\n", hash);
                        printf("password: %s\n", pass_attempt);

                        return 0;
                    }
                }
            }
        }
    }
}