#ifndef __MACROS_H
#define __MACROS_H

#define INF_LOOP for (;;) {}

#define ENSURE(exp)         if (!(exp)) { INF_LOOP } // @todo: Implement
#define UNREACHABLE()       INF_LOOP // @todo: Implement


#endif // __MACROS_H
