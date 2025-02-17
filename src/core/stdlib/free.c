// Written by LT_Schmiddy

#include <stdlib.h>
#include <recomp_globals.h>

RECOMP_STDLIB_DEFINITION void rc_free(void* ptr) {
    return recomp_free(ptr);
}