// Pulled from musl libc, locale support removed

#include <ctype.h>

RECOMP_CTYPE_DEFINITION int rc_isdigit(int c)
{
	return (unsigned)c - '0' < 10;
}
