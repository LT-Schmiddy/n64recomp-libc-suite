// Imported from musl Libc

#include <string.h>

char* __strchrnul(const char*, int);

char* rc_strchr(const char* s, int c)
{
	char* r = __strchrnul(s, c);
	return *(unsigned char*)r == (unsigned char)c ? r : 0;
}
