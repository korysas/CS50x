/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */
 
#include <cs50.h>
#include <stdio.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    if (n <= 0)
    {
        return false;
    }


    // linear search
    // for (int i = 0; i < n; i++)
    // {
    //     if (values[i] == value)
    //         return true;
    // }

    printf("n value: %d\n", n);
    return binary_search(value, values, 0, n - 1);
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    int i, j;
    int max = getmax(values, n);

    // initialize helper array to store the amount of occurrences of a value in values
    int helper[max + 1];
    for(i = 0; i <= max; i++)
    {
        helper[i] = 0;
    }

    for (i = 0; i < n; i++)
    {
        helper[values[i]]++;
    }

    for (i = 0, j = 0; i <= max; i++)
    {
        // printf("value: %d, occurrences: %d\n", i, helper[i]);
        while (helper[i] != 0)
        {
            values[j] = i;
            helper[i]--;
            j++;
        }
    }
}

int getmax(int values[], int n)
{
    int i;

    // find the largest value in the input array
    int max = 0;
    for (i = 0; i < n; i++)
    {
        if (values[i] > max)
            max = values[i];
    }

    return max;
}

bool binary_search(int value, int values[], int start, int end)
{
    int middle = start + (end - start) / 2;

    // printf("index: %d, value: %d\n", middle, values[middle]);
    // check if midpoint is the value we want
    if (values[middle] == value)
        return true;

    // if the array is a single elements and that element is not the value we are looking for
    // then we have searched everything
    if (end - start < 1)
    {
        return false;
    }

    if (values[middle] < value)
        return binary_search(value, values, middle + 1, end);
    else
        return binary_search(value, values, start, middle - 1);
}


