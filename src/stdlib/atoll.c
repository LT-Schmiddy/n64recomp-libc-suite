#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>

RECOMP_STDLIB_DEFINITION long long atoll(const char* str)
{
	long long val = 0;
	bool neg = false;

	while(rc_isspace(*str))
	{
		str++;
	}

	switch(*str)
	{
		case '-':

			neg = true;
		// Intentional fallthrough
		case '+':
			str++;
		default:
			// Intentional fallthrough
			;
	}

	while(rc_isdigit(*str))
	{
		val = (10 * val) + (*str++ - '0');
	}

	return neg ? -val : val;
}
