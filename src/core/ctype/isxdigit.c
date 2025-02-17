// Pulled from musl libc, locale support removed

#include <ctype.h>

RECOMP_CORE_DEFINITION int rc_isxdigit(int c)
{
	return rc_isdigit(c) || ((unsigned)c | 32) - 'a' < 6;
}
