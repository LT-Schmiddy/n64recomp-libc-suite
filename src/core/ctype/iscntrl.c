// Pulled from musl libc, locale support removed

#include <ctype.h>

RECOMP_CTYPE_DEFINITION int rc_iscntrl(int c)
{
	return (unsigned)c < 0x20 || c == 0x7f;
}
