// Pulled from musl libc, locale support removed

#include <ctype.h>

RECOMP_CTYPE_DEFINITION int rc_isalpha(int c)
{
	return ((unsigned)c | 32) - 'a' < 26;
}
