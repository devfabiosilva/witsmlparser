#ifndef CWS_MEMORY_H
 #define CWS_MEMORY_H
#include <stdlib.h>

void *cws_malloc(size_t);
void *cws_realloc(void *, size_t);
size_t cws_is_aligned(size_t);

#endif

