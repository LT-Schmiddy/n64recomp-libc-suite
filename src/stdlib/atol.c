#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>

RECOMP_STDLIB_DEFINITION long rc_atol(const char* str)
{
	long val = 0;
	bool neg = false;

	while(rc_isspace(*str))
	{
		str++;
	}

	switch(*str)
	{
		case '-':
			neg = true;
			/* fall through */
		case '+':
			str++;
		default:
			break;
	}

	while(rc_isdigit(*str))
	{
		val = (10 * val) + (*str++ - '0');
	}

	return neg ? -val : val;
}
