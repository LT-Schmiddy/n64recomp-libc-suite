// Pulled from musl libc

#include <ctype.h>

RECOMP_CTYPE_DEFINITION int rc_toascii(int c)
{
	return c & 0x7f;
}
