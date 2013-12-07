#include <err.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


#ifndef  NDEBUG
    #define TRACE( format, ...)
#else
    #define TRACE( format, ...)   printf( "%s::%s(%d)\n " format "\n", __FILE__, __FUNCTION__,  __LINE__)
#endif
