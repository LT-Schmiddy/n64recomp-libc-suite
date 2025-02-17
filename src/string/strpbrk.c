#include <string.h>

char* rc_strpbrk(const char* s, const char* b)
{
	s += rc_strcspn(s, b);
	return *s ? (char*)(uintptr_t)s : 0;
}
