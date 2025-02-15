// Pulled from musl libc, locale support removed

#include <ctype.h>

RECOMP_CTYPE_DEFINITION int rc_tolower(int c)
{
	if(rc_isupper(c))
	{
		return c | 32;
	}

	return c;
}
