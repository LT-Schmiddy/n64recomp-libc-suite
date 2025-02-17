#ifndef __RECOMP_LIBC__
#define __RECOMP_LIBC__
#include <modding.h>

#ifndef ENABLE_UNIMPLEMENTED_LIBC_APIS
#define DISABLE_UNIMPLEMENTED_LIBC_APIS 
#endif

#define RECOMP_LIBC_CORE_MOD_ID "recomp_libc_core"

#ifdef RECOMP_IS_BUILDING_core
#define RECOMP_CORE_DECLARATION(func_dec) func_dec
#define RECOMP_CORE_DEFINITION RECOMP_EXPORT
#else
#define RECOMP_CORE_DECLARATION(func_dec) RECOMP_IMPORT(RECOMP_LIBC_CORE_MOD_ID, func_dec);
#define RECOMP_CORE_DEFINITION
#endif


#endif // __RECOMP_LIBC__
