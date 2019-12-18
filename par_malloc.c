
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "xmalloc.h"
#include "opt_malloc.h"


void*
xmalloc(size_t bytes)
{
    return opt_malloc(bytes);
    //return 0;
}

void
xfree(void* ptr)
{
    opt_free(ptr);
}

void*
xrealloc(void* prev, size_t bytes)
{
    return opt_realloc(prev, bytes);
    //return 0;
}

