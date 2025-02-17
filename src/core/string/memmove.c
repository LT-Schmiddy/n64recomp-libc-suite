#include <string.h>

RECOMP_CORE_DEFINITION void* __attribute__((weak)) rc_memmove(void* s1, const void* s2, size_t n)
{
	return rc_memcpy(s1, s2, n);
}
