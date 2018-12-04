#ifndef __MACROS_H
#define __MACROS_H


#include "Logger.h"

#include <string.h>


#define INF_LOOP for (;;) {}

#define ENSURE(exp)         if (!(exp)) \
    { \
        Logger_Log(__FILENAME__, __LINE__, Error, "ASSERTION FAILED: "#exp); \
        INF_LOOP \
    } // @todo: Implement
#define UNREACHABLE()       INF_LOOP // @todo: Implement

#ifndef UNUSED
    #define UNUSED(x)   (void)x
#endif


#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)


typedef uint32_t Timestamp_t; // @todo: MOVE THIS
typedef struct Timestamp_s
{
    bool hasValue;
    Timestamp_t value;
} OptionalTimestamp_t; // @todo: MOVE THIS


#endif // __MACROS_H
