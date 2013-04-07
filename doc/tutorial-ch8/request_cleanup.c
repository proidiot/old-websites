#include "request_cleanup.h"

#include "request_state.h"
#include "daemon_state.h"
#include <stdlib.h>

void request_cleanup(
		void* cls,
		struct MHD_Connection* connection,
		void** con_cls,
		enum MHD_RequestTerminationCode rtc)
{
	DAEMON_STATE dstate = (DAEMON_STATE)cls;
	REQUEST_STATE rstate = *con_cls;
	if (rstate != NULL) {
		if (strncmp(rstate->method, MHD_HTTP_METHOD_POST, 25) == 0) {
			upload_client_load_dropping(dstate);
		} else {
			client_load_dropping(dstate);
		}
		destroy_REQUEST_STATE(rstate, dstate);
		*con_cls = NULL;
	} else {
		client_load_dropping(dstate);
	}
}


