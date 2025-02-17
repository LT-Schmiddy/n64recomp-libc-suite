// Imported from musl Libc

#include <string.h>

char* __strchrnul(const char*, int);

RECOMP_CORE_DEFINITION char* rc_strchr(const char* s, int c)
{
	char* r = __strchrnul(s, c);
	return *(unsigned char*)r == (unsigned char)c ? r : 0;
}
