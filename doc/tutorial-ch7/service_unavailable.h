#ifndef WEBSITES_SERVICE_UNAVAILABLE_H
#define WEBSITES_SERVICE_UNAVAILABLE_H

#include <microhttpd.h>

#ifdef DEBUG
#include "debug.h"
#define service_unavailable(c) _debug_int_ret(__FILE__,__LINE__,_service_unavailable(c),"service_unavailable")
#else
#define service_unavailable(c) _service_unavailable(c)
#endif

int _service_unavailable(struct MHD_Connection* connection);

#endif
