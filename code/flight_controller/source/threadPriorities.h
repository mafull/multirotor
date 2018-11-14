#ifndef __THREAD_PRIORITIES_H
#define __THREAD_PRIORITIES_H

// Thread priorities - higher number => higher priority
#define THREAD_PRIORITY_CONTROL         4u
#define THREAD_PRIORITY_IMU             3u
#define THREAD_PRIORITY_INITIALISATION  2u // Only thread running at the time
#define THREAD_PRIORITY_LOGGER          2u

#endif // __THREAD_PRIORITIES_H
