#ifndef BUBO_ASSERT_H
#define BUBO_ASSERT_H

#include <signal.h>

#ifdef DEBUG_MODE

#define BUBO_ASSERT(x, ...) { if(!x) { BUBO_ERROR("Application Failed: {0}", __VA_ARGS__); abort(); } }
#define BUBO_DEBUG_ASSERT(x, ...) { if(!x) { BUBO_DEBUG_ERROR("Application Failed: {0}\nFailure happened at:\nFile path: {1}\nFunction name: {2}\nLine number: {3}", __VA_ARGS__, __FILE__, __FUNCTION__, __LINE__); raise(SIGTRAP); } }

#else

#define BUBO_ASSERT(x, ...)
#define BUBO_DEBUG_ASSERT(x, ...)

#endif// DEBUG_MODE

#endif// BUBO_ASSERT_H
