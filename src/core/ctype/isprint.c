// Pulled from musl libc, locale support removed

#include <ctype.h>

RECOMP_CORE_DEFINITION int rc_isprint(int c)
{
	return (unsigned)c - 0x20 < 0x5f;
}
