#ifndef __RECOMP_LIBC__
#define __RECOMP_LIBC__
#include <modding.h>

#ifndef ENABLE_UNIMPLEMENTED_LIBC_APIS
#define DISABLE_UNIMPLEMENTED_LIBC_APIS 
#endif
#ifdef RECOMP_IS_BUILDING_combined
#define RECOMP_IS_BUILDING_assert
#define RECOMP_IS_BUILDING_ctype
#define RECOMP_IS_BUILDING_printf
#define RECOMP_IS_BUILDING_stdlib
#define RECOMP_IS_BUILDING_string
#define RECOMP_IS_BUILDING_strings

#define RECOMP_LIBC_ASSERT_MOD_ID "recomp_libc_combined"
#define RECOMP_LIBC_CTYPE_MOD_ID "recomp_libc_combined"
#define RECOMP_LIBC_PRINTF_MOD_ID "recomp_libc_combined"
#define RECOMP_LIBC_STDLIB_MOD_ID "recomp_libc_combined"
#define RECOMP_LIBC_STRING_MOD_ID "recomp_libc_combined"
#define RECOMP_LIBC_STRINGS_MOD_ID "recomp_libc_combined"

#else
#define RECOMP_LIBC_ASSERT_MOD_ID "recomp_libc_assert"
#define RECOMP_LIBC_CTYPE_MOD_ID "recomp_libc_ctype"
#define RECOMP_LIBC_PRINTF_MOD_ID "recomp_libc_printf"
#define RECOMP_LIBC_STDLIB_MOD_ID "recomp_libc_stdlib"
#define RECOMP_LIBC_STRING_MOD_ID "recomp_libc_string"
#define RECOMP_LIBC_STRINGS_MOD_ID "recomp_libc_strings"
#endif


// ASSERT:
#ifdef RECOMP_IS_BUILDING_assert
    #define RECOMP_ASSERT_DECLARATION(func_dec) func_dec
    #define RECOMP_ASSERT_DEFINITION RECOMP_EXPORT
#else
    #define RECOMP_ASSERT_DECLARATION(func_dec) RECOMP_IMPORT(RECOMP_LIBC_ASSERT_MOD_ID, func_dec);
    #define RECOMP_ASSERT_DEFINITION
#endif


// CTYPE:
#ifdef RECOMP_IS_BUILDING_ctype
    #define RECOMP_CTYPE_DECLARATION(func_dec) func_dec
    #define RECOMP_CTYPE_DEFINITION RECOMP_EXPORT
#else
    #define RECOMP_CTYPE_DECLARATION(func_dec) RECOMP_IMPORT(RECOMP_LIBC_CTYPE_MOD_ID, func_dec);
    #define RECOMP_CTYPE_DEFINITION
#endif

//PRINTF
#ifdef RECOMP_IS_BUILDING_printf
    #define RECOMP_PRINTF_DECLARATION(func_dec) func_dec
    #define RECOMP_PRINTF_DEFINITION RECOMP_EXPORT
#else
    #define RECOMP_PRINTF_DECLARATION(func_dec) RECOMP_IMPORT(RECOMP_LIBC_PRINTF_MOD_ID, func_dec);
    #define RECOMP_PRINTF_DEFINITION
#endif


//STDLIB
#ifdef RECOMP_IS_BUILDING_stdlib
    #define RECOMP_STDLIB_DECLARATION(func_dec) func_dec
    #define RECOMP_STDLIB_DEFINITION RECOMP_EXPORT
#else
    #define RECOMP_STDLIB_DECLARATION(func_dec) RECOMP_IMPORT(RECOMP_LIBC_STDLIB_MOD_ID, func_dec);
    #define RECOMP_STDLIB_DEFINITION
#endif

//STRING
#ifdef RECOMP_IS_BUILDING_string
    #define RECOMP_STRING_DECLARATION(func_dec) func_dec
    #define RECOMP_STRING_DEFINITION RECOMP_EXPORT
#else
    #define RECOMP_STRING_DECLARATION(func_dec) RECOMP_IMPORT(RECOMP_LIBC_STRING_MOD_ID, func_dec);
    #define RECOMP_STRING_DEFINITION
#endif

//STRINGS
#ifdef RECOMP_IS_BUILDING_strings
    #define RECOMP_STRINGS_DECLARATION(func_dec) func_dec
    #define RECOMP_STRINGS_DEFINITION RECOMP_EXPORT
#else
    #define RECOMP_STRINGS_DECLARATION(func_dec) RECOMP_IMPORT(RECOMP_LIBC_STRINGS_MOD_ID, func_dec);
    #define RECOMP_STRINGS_DEFINITION
#endif


#endif // __RECOMP_LIBC__
