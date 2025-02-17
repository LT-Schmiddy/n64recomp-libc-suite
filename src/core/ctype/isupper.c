// Pulled from musl libc, locale support removed

#include <ctype.h>

RECOMP_CORE_DEFINITION int rc_isupper(int c)
{
	return (unsigned)c - 'A' < 26;
}
