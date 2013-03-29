#ifndef WEBSITES_REQUEST_CLEANUP_H
#define WEBSITES_REQUEST_CLEANUP_H

#include <microhttpd.h>

void request_cleanup(
		void* cls,
		struct MHD_Connection* connection,
		void** con_cls,
		enum MHD_RequestTerminationCode rtc);

#endif
