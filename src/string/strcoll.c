#include <string.h>

RECOMP_STRING_DEFINITION int rc_strcoll(const char* l, const char* r)
{
	return rc_strcmp(l, r);
}
