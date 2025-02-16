#ifndef _SIZE_T
#define _SIZE_T
#if defined(_MIPS_SZLONG) && (_MIPS_SZLONG == 64)
typedef unsigned long size_t;
#else
typedef unsigned int size_t;
#endif
#endif
