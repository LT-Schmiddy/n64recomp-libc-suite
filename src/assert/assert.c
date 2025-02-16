#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

// __attribute__((noreturn, weak)) void __assert_fail(const char* expr, const char* file,
RECOMP_ASSERT_DEFINITION __attribute__((weak)) void __assert_fail(const char* expr, const char* file,
												   unsigned int line, const char* function)
{
	printf("Assertion failed: %s (%s: %s: %u)\n", expr, file, function, line);
	// abort();
}
