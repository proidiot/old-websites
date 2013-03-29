#ifndef WEBSITES_DEBUG_H
#define WEBSITES_DEBUG_H

void _print_debug_line(const char* file, const int line, const char* fmt, ...);

int _debug_int_ret(const char* file, const int line, int ret, const char* fmt, ...);

#ifdef DEBUG
#define debug(...) _print_debug_line(__FILE__,__LINE__,__VA_ARGS__)
#else
#define debug(...) /* Debugging disabled. */
#endif

#endif
