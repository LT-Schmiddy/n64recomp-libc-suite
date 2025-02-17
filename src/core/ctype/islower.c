// Pulled from musl libc, locale support removed

#include <ctype.h>

RECOMP_CORE_DEFINITION int rc_islower(int c)
{
	return (unsigned)c - 'a' < 26;
}
