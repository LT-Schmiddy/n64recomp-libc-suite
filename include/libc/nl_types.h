#ifndef __NL_TYPES_H
#define __NL_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <recomp_libc.h>

#define NL_SETD 1
#define NL_CAT_LOCALE 1

typedef int nl_item;
typedef void* nl_catd;

#ifndef DISABLE_UNIMPLEMENTED_LIBC_APIS
nl_catd catopen(const char*, int);
char* catgets(nl_catd, int, int, const char*);
int catclose(nl_catd);
#endif

#ifdef __cplusplus
}
#endif

#endif // __NL_TYPES_H
