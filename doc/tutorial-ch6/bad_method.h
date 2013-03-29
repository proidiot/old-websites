#ifndef WEBSITES_BAD_METHOD_H
#define WEBSITES_BAD_METHOD_H

#include <microhttpd.h>

#ifdef DEBUG
#include "debug.h"
#define bad_method(c,m) _debug_int_ret(__FILE__,__LINE__,_bad_method((c),m),"bad_methpd")
#else
#define bad_methpd(c,m) _bad_method((c),m)
#endif

int _bad_method(struct MHD_Connection* connection, const char* methods);

#endif
