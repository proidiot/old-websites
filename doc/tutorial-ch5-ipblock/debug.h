#ifndef WEBSITES_DEBUG_H
#define WEBSITES_DEBUG_H

#include <config.h>

void _print_debug_line(const char* file, const int line, const char* fmt, ...);

#ifdef DEBUG
#define debug(...) _print_debug_line(__FILE__,__LINE__,__VA_ARGS__)
#else
#define debug(...) /* Debugging disabled. */
#endif

#endif
