#include <string.h>

RECOMP_STRING_DEFINITION size_t rc_strxfrm(char* restrict dest, const char* restrict src, size_t n)
{
	size_t l = rc_strlen(src);
	if(n > l)
	{
		rc_strcpy(dest, src);
	}

	return l;
}
