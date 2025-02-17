// Pulled from musl libc, locale support removed

#include <ctype.h>

RECOMP_CTYPE_DEFINITION int rc_isgraph(int c)
{
	return (unsigned)c - 0x21 < 0x5e;
}
