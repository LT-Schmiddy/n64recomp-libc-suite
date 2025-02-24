/*-
 * Copyright (c) 1990, 1993
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

#include <strings.h>

/*
 * Find Last Set bit
 */
#if defined(__clang__)
RECOMP_CORE_DEFINITION int rc_flsll(long long mask)
{
#if __has_builtin(__builtin_flsll)
	return __builtin_flsll(mask);
#elif __has_builtin(__builtin_clzll)
	if(mask == 0)
	{
		return (0);
	}

	return ((int)sizeof(mask) << 3) - __builtin_clzll((unsigned long long)mask);
#else
	int bit;

	if(mask == 0)
	{
		return (0);
	}

	for(bit = 1; mask != 1; bit++)
	{
		mask = (unsigned long long)mask >> 1;
	}

	return (bit);
#endif
}

#else // not __clang__

RECOMP_CORE_DEFINITION int rc_flsll(long long mask)
{
	if(mask == 0)
	{
		return (0);
	}

	return ((int)sizeof(mask) << 3) - __builtin_clzll((unsigned long long)mask);
}

#endif // if __clang__
