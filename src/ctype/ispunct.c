// Pulled from musl libc, locale support removed

#include <ctype.h>

RECOMP_CTYPE_DEFINITION int rc_ispunct(int c)
{
	return rc_isgraph(c) && !rc_isalnum(c);
}
