/*
 * Copyright (c) 2011 Apple, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 *
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 *
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 *
 * @APPLE_LICENSE_HEADER_END@
 */

#include <string.h>

RECOMP_CORE_DEFINITION char* rc_strncpy(char* __restrict dst, const char* __restrict src, size_t maxlen)
{
	const size_t srclen = rc_strnlen(src, maxlen);
	if(srclen < maxlen)
	{
		//  The stpncpy() and strncpy() functions copy at most maxlen
		//  characters from src into dst.
		rc_memcpy(dst, src, srclen);
		//  If src is less than maxlen characters long, the remainder
		//  of dst is filled with '\0' characters.
		rc_memset(dst + srclen, 0, maxlen - srclen);
	}
	else
	{
		//  Otherwise, dst is not terminated.
		rc_memcpy(dst, src, maxlen);
	}

	//  The rc_strcpy() and strncpy() functions return dst.
	return dst;
}
