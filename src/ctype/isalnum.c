// Pulled from musl libc, locale support removed

#include <ctype.h>

RECOMP_CTYPE_DEFINITION int rc_isalnum(int c)
{
	return rc_isalpha(c) || rc_isdigit(c);
}
