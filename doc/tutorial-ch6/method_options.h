#ifndef WEBSITES_METHOD_OPTIONS_H
#define WEBSITES_METHOD_OPTIONS_H

#include <microhttpd.h>

#ifdef DEBUG
#include "debug.h"
#define method_options(c,m) _debug_int_ret(__FILE__,__LINE__,_method_options((c),m),"method_options")
#else
#define method_options(c,m) _method_options((c),m)
#endif

int _method_options(struct MHD_Connection* connection, const char* methods);

#endif

