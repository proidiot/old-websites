#ifndef WEBSITES_NOT_FOUND_H
#define WEBSITES_NOT_FOUND_H

#include <microhttpd.h>

#ifdef DEBUG
#include "debug.h"
#define not_found(c,u,d) _debug_int_ret(__FILE__,__LINE__,_not_found((c),u,d),"not_found")
#else
#define not_found(c,u,d) _not_found((c),u,d)
#endif

int _not_found(
		struct MHD_Connection* connection,
		const char* default_url,
		const char* url_description);

#endif
