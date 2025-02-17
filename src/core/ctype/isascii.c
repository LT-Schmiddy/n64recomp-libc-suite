// Pulled from musl libc

#include <ctype.h>

RECOMP_CORE_DEFINITION int rc_isascii(int c)
{
	return !(c & ~0x7f);
}
