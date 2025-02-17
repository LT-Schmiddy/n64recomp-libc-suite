// Pulled from musl libc, locale support removed

#include <ctype.h>

RECOMP_CORE_DEFINITION int rc_isblank(int c)
{
	return (c == ' ' || c == '\t');
}
