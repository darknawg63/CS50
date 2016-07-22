/**
 * generate.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Generates pseudorandom numbers in [0,LIMIT), one per line.
 *
 * Usage: generate n [s]
 *
 * where n is number of pseudorandom numbers to print
 * and s is an optional seed
 */

#define _XOPEN_SOURCE

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// constant
#define LIMIT 65536

int main(int argc, string argv[])
{
    // Ensure that at least 1 but no more than two parameters are in
    // the list of arguments (not including argv[0]). Else show usage
    if (argc != 2 && argc != 3)
    {
        printf("Usage: generate n [s]\n");
        return 1;
    }

    // Parse or convert the first argument to an integer type
    // stored in the variable n
    int n = atoi(argv[1]);

    // If there are three parameters in the argv[] list, two of which
    // are entered by the user then call srand48 using the value of
    // argv[2] as the seed. Otherwise use the value of system time
    if (argc == 3)
    {
        srand48((long int) atoi(argv[2]));
    }
    else
    {
        srand48((long int) time(NULL));
    }

    // Print out as many random numbers as the user entered as the first argument
    // to the program, each time calling the drand48() function and casting its returned
    // double to an integer so that we can format it as $i on stdout.
    for (int i = 0; i < n; i++)
    {
        printf("%i\n", (int) (drand48() * LIMIT));
    }

    // success
    return 0;
}