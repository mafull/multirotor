#ifndef __MACROS_H
#define __MACROS_H


#include <string.h>


#define INF_LOOP for (;;) {}

#define ENSURE(exp)         if (!(exp)) { INF_LOOP } // @todo: Implement
#define UNREACHABLE()       INF_LOOP // @todo: Implement

#ifndef UNUSED
    #define UNUSED(x)   (void)x
#endif


#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)


#endif // __MACROS_H
