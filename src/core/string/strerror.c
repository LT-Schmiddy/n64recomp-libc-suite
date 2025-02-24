// Modeled after musl libc with the use of the errid[] and errmsg[] trick

#include <errno.h>
#include <string.h>

#define E(a, b) ((unsigned char)a),
static const unsigned char errid[] = {
#include "__strerror.h"
};

#undef E
#define E(a, b) b "\0"
static const char errmsg[] =
#include "__strerror.h"
;

static const char* invalid_err = "No error information available.";

char* rc_strerror(int err_no)
{
	const char* s = NULL;
	int i;

	for(i = 0; errid[i] && errid[i] != err_no; i++)
	{
	}

	if(errid[i] != err_no)
	{
		s = invalid_err;
	}
	else
	{
		for(s = errmsg; i; s++, i--)
		{
			for(; *s; s++)
			{
			}
		}
	}

	return (char*)(uintptr_t)s;
}
