// Pulled from musl libc, locale support removed

#include <ctype.h>

RECOMP_CTYPE_DEFINITION int rc_isxdigit(int c)
{
	return isdigit(c) || ((unsigned)c | 32) - 'a' < 6;
}
