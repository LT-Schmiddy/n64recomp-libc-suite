#ifndef __RECOMP_LIBC__
#define __RECOMP_LIBC__
#include <modding.h>

#define RECOMP_LIBC_CTYPE_MOD_ID "recomp_libc_ctype"

#ifdef RECOMP_IS_BUILDING_CTYPE
    #define RECOMP_CTYPE_DECLARATION
    #define RECOMP_CTYPE_DEFINITION RECOMP_EXPORT
#else
    #define RECOMP_CTYPE_DECLARATION(func_dec) RECOMP_IMPORT(RECOMP_LIBC_CTYPE_MOD_ID, func_dec);
    #define RECOMP_CTYPE_DEFINITION
#endif
#endif