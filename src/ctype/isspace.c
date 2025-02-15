// Pulled from musl libc, locale support removed

#include <ctype.h>

RECOMP_CTYPE_DEFINITION int rc_isspace(int c)
{
	return c == ' ' || (unsigned)c - '\t' < 5;
}
