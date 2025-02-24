#include <assert.h>
#include <errno.h>
#include <string.h>

RECOMP_CORE_DEFINITION int rc_strerror_r(int err_no, char* buffer, size_t buffer_size)
{
	int r = 0;
	char* err_msg = rc_strerror(err_no);
	size_t length = rc_strlen(err_msg);

	assert(buffer);

	if(length >= buffer_size)
	{
		if(buffer_size)
		{
			// -1 so we don't copy an extra byte...
			rc_memcpy(buffer, err_msg, buffer_size - 1);
			// since we will null terminate the string
			buffer[buffer_size - 1] = 0;
		}

		r = ERANGE;
	}
	else
	{
		// +1 for null termination
		rc_memcpy(buffer, err_msg, length + 1);
	}

	return r;
}
