#ifndef WEBSITES_SERVER_ERROR_H
#define WEBSITES_SERVER_ERROR_H

#include <microhttpd.h>

#ifdef DEBUG
#include "debug.h"
#define server_error(c) _debug_int_ret(__FILE__,__LINE__,_server_error(c),"server_error")
#else
#define server_error(c) _server_error(c)
#endif

int _server_error(struct MHD_Connection* connection);

#endif
