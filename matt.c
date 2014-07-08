/* 
 * =====================================================================================
 *
 *       Filename:  matt.c
 *
 *    Description:  My little collection of useful functions I've made for myself
 *
 *        Version:  0.1
 *        Created:  03/03/14 11:18:52
 *       Revision:  none
 *       Compiler:  Clang
 *        License:  BSD 3-Clause License
 *                  see attached file ./LICENSE
 *
 *         Author:  Matthew Pherigo (mwp), hybrid120@gmail.com
 * 
 * =====================================================================================
 */

// Header files
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include "matt.h"

//// Define true and false
// #define	TRUE 1			
// #define	FALSE 0

// define some error shortcuts
// when we know what went wrong:
#define ERROR fprintf(stderr, "%s", strerror(errno));

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  stringtoint
 *  Description:  Converts a string to a long long using strtonum, then to an int.
 *                Sets errno to a non-zero value if the number cannot fit in an 
 *                int value; 1 for a positive overflow, -1 for negative.
 * =====================================================================================
 */
int stringtoint(char* string)
{
    const char* err;
    long long ll;
    int answer;
    errno = 0;

    ll = strtonum(string, LLONG_MIN, LLONG_MAX, &err);
    if (err != NULL)
    {
        errno = -2;
        fprintf(stderr, "strtonum error: %s\n", err);
        return 0;
    }

    if (ll > INT_MAX)
    {
        errno = 1;
        fprintf(stderr, "stringtoint: number too big for int! (Number was %lld)\n", ll);
        return 0;
    }
    else if (ll < INT_MIN)
    {
        errno = -1;
        fprintf(stderr, "stringtoint: number too big for int! (Number was %lld)\n", ll);
        return 0;
    }

    answer = (int)ll;
    errno = 0;
    return answer;
} 

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  getString
 *  Description:  Gets a string from the user, with an optional limit. To not use the
 *                limit, just pass getString a limit of (0).
 *
 *                CS50 code with the added ability to declare a limit on the length
 *                of the string.
 * =====================================================================================
 */
char* getString(unsigned int limit)
{
    // growable buffer for chars
    char* buffer = NULL;

    // capacity of buffer
    unsigned int capacity = 0;

    // number of chars actually in buffer
    unsigned int n = 0;

    // character read or EOF
    int c;

    // limit precheck
    if (limit > UINT_MAX)
    {
        fprintf(stderr, "getString: Limit %i outside UINT boundaries? For no limit, pass the function a limit of (0).", limit);
        return NULL;
    }

    // iteratively get chars from standard input
    while ((c = fgetc(stdin)) != '\n' && c != EOF)
    {
        // grow buffer if necessary
        if (n + 1 > capacity)
        {
            if (limit > 0) {
                // determine new capacity, considering limit: start at 32 then double
                if (capacity == 0)
                {
                    capacity = 32;
                }
                else if (capacity <= (UINT_MAX / 2) && capacity <= (limit / 2) )
                {
                    capacity *= 2;
                }
                else if (capacity <= (UINT_MAX / 2) && capacity > (limit / 2) )
                {
                    if (capacity == limit)
                    {
                        fprintf(stderr, "\nCharacter limit of %i reached. About to retry...\n", limit);
                        sleep(1);
                        printf ( "3...\n" );
                        sleep(1);
                        printf ( "2...\n" );
                        sleep(1);
                        printf ( "1...\n" );
                        sleep(1);
                        printf ( "Retry: " );
                        continue;
                    }
                    capacity = limit;
                }
                else
                {
                    free(buffer);
                    return NULL;
                }
            }
            else if (limit == 0) {
                // determine new capacity: start at 32 then double
                if (capacity == 0)
                {
                    capacity = 32;
                }
                else if (capacity <= (UINT_MAX / 2))
                {
                    capacity *= 2;
                }
                else if (capacity <= (UINT_MAX / 2))
                {
                    capacity = limit;
                }
                else
                {
                    free(buffer);
                    return NULL;
                }

            }

            // extend buffer's capacity
            char* temp = realloc(buffer, capacity * sizeof(char));
            if (temp == NULL)
            {
                free(buffer);
                return NULL;
            }
            buffer = temp;
        }

        // append current character to buffer
        buffer[n++] = (char)c;
    }

    // return NULL if user provided no input
    if (n == 0 && c == EOF)
    {
        return NULL;
    }

    // minimize buffer
    char* minimal = malloc((n + 1) * sizeof(char));
    strncpy(minimal, buffer, n);
    free(buffer);

    // terminate string
    minimal[n] = '\0';

    // return string
    return minimal;
}

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  getChar
 *  Description:  Gets a char from the user. CS50 code.
 * =====================================================================================
 */
char getChar(void)
{
    while ( true )
    {
        char c1, c2;
        char* line = getString(0);

        if (line == NULL)
            return CHAR_MAX;
        
        if (1 == sscanf(line, " %c %c", &c1, &c2))
        {
            free(line);
            return c1;
        }
        else
        {
            free(line);
            printf ( "Retry: " );
        }
    }
}

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  getDouble
 *  Description:  Get a double from the user. Returns NULL and errno=1 upon failure.
 * =====================================================================================
 */
double getDouble(void)
{
    // try to get a double from user
    while (true)
    {
        // get line of text, returning CHAR_MAX & errno on failure
        char* line = getString(0);
        if (line == NULL)
        {
            errno = 1;
            return CHAR_MAX;
        }

        // return a double if only a double (possibly with
        // leading and/or trailing whitespace) was provided
        char* extract; double d; char c;
        extract = malloc(sizeof(double));
        if (sscanf(line, " %s %c", extract, &c) == 1)
        {
            d = stringtod(extract);
            free(line);
            return d;
        }
        else
        {
            free(line);
            printf("Retry: ");
        }
    }
}
/*
 * ===  FUNCTION  ======================================================================
 *         Name:  stringtod
 *  Description:  Convert string to double float.
 * =====================================================================================
 */
double stringtod(char* string)
{
    errno = 0;
    double result = strtod(string, NULL);
    if (errno != 0)
    {
        if (ERANGE == errno)
        {
            if (HUGE_VAL >= result)
            {
                result = INFINITY;
                ERROR;
            }
            else if (-HUGE_VAL <= result)
            {
                result = -INFINITY;
                ERROR;
            }
            else
                ERROR;
        }
        else if (errno == EINVAL)
        {
            result = NAN;
            ERROR;
        }
        else
            ERROR;
    }
    
    return result;
}

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  dEquality
 *  Description:  Tests if two doubles are close enough to each other to consider
 *                "equal". "Close enough" is defined by the value of epsilon.
 * =====================================================================================
 */
bool dEquality(double a, double b, double epsilon)
{
    return fabs(a - b) < epsilon;
}
