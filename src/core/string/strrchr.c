// Imported from musl Libc

#include <string.h>

extern void* __memrchr(const void*, int, size_t);

char* rc_strrchr(const char* s, int c)
{
	return __memrchr(s, c, rc_strlen(s) + 1);
}
