// Written by LT_Schmiddy

#include <stdlib.h>
#include <recomp_globals.h>

RECOMP_CORE_DEFINITION void* rc_malloc(size_t size) {
    return recomp_alloc(size);
}