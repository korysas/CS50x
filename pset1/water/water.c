/*
    This programs gives the approximate conversion for the amount of bottles of water
    used during a shower.

    Input: minutes of the shower as an integer

    Output: equivalent bottles of water as an integer
*/

#include <stdio.h>

#define OUNCES_PER_MIN 192;
#define OUNCES_PER_BOTTLE 16;

int main(void)
{
    int shower_mins;
    int c;
    
    printf("Time of shower in minutes: ");
    
    while (1)
    {
        if (scanf("%d", &shower_mins) != 1)
        {
            c = getchar();
            while (c != '\n')
            {
                c = getchar();
            }
            
            printf("Invalid input, retry: ");
        }
        
        else if ((c = getchar()) != '\n')
        {
            while ((c = getchar()) != '\n')
            {
                c = getchar();
            }
            
            printf("Incalid input, retry: ");
        }
        
        else break;
    }
    
    int ounces_used = shower_mins * OUNCES_PER_MIN;
    int bottles_used = ounces_used / OUNCES_PER_BOTTLE;
    
    printf("Bottles: %d\n", bottles_used);
}