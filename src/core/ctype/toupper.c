// Pulled from musl libc, locale support removed

#include <ctype.h>

RECOMP_CORE_DEFINITION int rc_toupper(int c)
{
	if(rc_islower(c))
	{
		return c & 0x5f;
	}
	return c;
}
