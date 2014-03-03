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

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

#include "matt.h"

int stringtoint(char* string)
{
	const char* err;
	long long ll;
	int answer;

	ll = strtonum(string, LLONG_MIN, LLONG_MAX, &err);
	if (err != NULL)
	{
		errno = 1;
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
