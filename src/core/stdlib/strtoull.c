/*-
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <ctype.h>
#include <limits.h>
#include <stdlib.h>

/*
 * Convert a string to an unsigned long long integer.
 *
 * Assumes that the upper and lower case
 * alphabets and digits are each contiguous.
 */
RECOMP_CORE_DEFINITION unsigned long long rc_strtoull(const char* __restrict nptr, char** __restrict endptr, int base)
{
	const char* s;
	unsigned long long acc;
	char c;
	unsigned long long cutoff;
	int neg;
	int any;
	int cutlim;

	/*
	 * See strtoq for comments as to the logic used.
	 */
	s = nptr;
	do
	{
		c = *s++;
	} while(rc_isspace((unsigned char)c));

	if(c == '-')
	{
		neg = 1;
		c = *s++;
	}
	else
	{
		neg = 0;
		if(c == '+')
		{
			c = *s++;
		}
	}

	if((base == 0 || base == 16) && c == '0' && (*s == 'x' || *s == 'X'))
	{
		c = s[1];
		s += 2;
		base = 16;
	}

	if(base == 0)
	{
		base = c == '0' ? 8 : 10;
	}

	acc = 0ULL;
	any = 0;

	if(base < 2 || base > 36)
	{
		goto noconv;
	}

	cutoff = ULLONG_MAX / (unsigned long long)base;
	cutlim = (int)(ULLONG_MAX % (unsigned long long)base);

	for(;; c = *s++)
	{
		if(c >= '0' && c <= '9')
		{
			c = (char)(c - '0');
		}
		else if(c >= 'A' && c <= 'Z')
		{
			c = (char)(c - 'A' - 10);
		}
		else if(c >= 'a' && c <= 'z')
		{
			c = (char)(c - 'a' - 10);
		}
		else
		{
			break;
		}

		if(c >= base)
		{
			break;
		}

		if(any < 0 || acc > cutoff || (acc == cutoff && c > cutlim))
		{
			any = -1;
		}
		else
		{
			any = 1;
			acc *= (unsigned long long)base;
			acc += (unsigned long long)c;
		}
	}

	if(any < 0)
	{
		acc = ULLONG_MAX;
		// errno = ERANGE;
	}
	else if(!any)
	{
	noconv:
		// PJ: nonstandard, but since no errno, acc = 0
		acc = 0;
		// errno = EINVAL;
	}
	else if(neg)
	{
		acc = -acc;
	}

	if(endptr != NULL)
	{
		*endptr = (char*)(uintptr_t)(any ? s - 1 : nptr);
	}

	return (acc);
}
