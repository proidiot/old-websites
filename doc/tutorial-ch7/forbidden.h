#ifndef WEBSITES_FORBIDDEN_H
#define WEBSITES_FORBIDDEN_H

#include <microhttpd.h>

#ifdef DEBUG
#include "debug.h"
#define forbidden(c,e) _debug_int_ret(__FILE__,__LINE__,_forbidden((c),e),"forbidden: %s",e)
#else
#define forbidden(c,e) _forbidden((c),e)
#endif

int _forbidden(struct MHD_Connection* connection, const char* explanation);

#endif
