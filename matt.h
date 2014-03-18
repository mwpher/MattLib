/*
 * =====================================================================================
 *
 *       Filename:  matt.h
 *
 *    Description:  My little collection of useful functions I've made for myself
 *
 *        Version:  0.1
 *        Created:  03/03/14 11:18:03
 *       Revision:  none
 *       Compiler:  Clang
 *        License:  BSD 3-Clause License
 *                  see attached file ./LICENSE
 *
 *         Author:  Matthew Pherigo (mwp), hybrid120@gmail.com
 *
 * =====================================================================================
 */
#include <stdbool.h>

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  stringtoint
 *  Description:  Converts a string to a long long using strtonum, then to an int.
 *                Sets errno to a non-zero value if the number cannot fit in an 
 *                int value.
 * =====================================================================================
 */
int stringtoint(char* string);

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
char* getString(unsigned int limit);

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  getChar
 *  Description:  Gets a char from the user. Mostly CS50 code, see cs50.h
 * =====================================================================================
 */
char getChar(void);

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  getDouble
 *  Description:  Get a double from the user. Returns NULL and errno=1 upon failure.
 * =====================================================================================
 */
double getDouble(void);

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  stringtod
 *  Description:  Convert string to double float.
 * =====================================================================================
 */
double stringtod(char* string);

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  dEquality
 *  Description:  Tests if two doubles are close enough to each other to consider
 *                "equal". "Close enough" is defined by the value of epsilon.
 * =====================================================================================
 */
bool dEquality(double a, double b, double epsilon);
