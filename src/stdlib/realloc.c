#include <stdlib.h>
#include <string.h>

RECOMP_STDLIB_DEFINITION void* rc_realloc(void* ptr, size_t size)
{
	void* new_data = NULL;

	if(size)
	{
		if(!ptr)
		{
			return malloc(size);
		}

		new_data = malloc(size);
		if(new_data)
		{
			memcpy(new_data, ptr, size); // TODO: unsafe copy...
			free(ptr); // we always move the data. free.
		}
	}

	return new_data;
}

RECOMP_STDLIB_DEFINITION void* reallocf(void* ptr, size_t size)
{
	void* p = rc_realloc(ptr, size);

	if((p == NULL) && (ptr != NULL))
	{
		free(ptr);
	}

	return p;
}
