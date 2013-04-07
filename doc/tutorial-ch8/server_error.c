#include "server_error.h"

#include <string.h>

int _server_error(struct MHD_Connection* connection)
{
	const char* errorstr = "<html><body><h1>Internal Server Error</h1>An "
		"internal server error has prevented this page from being "
		"constructed correctly.</body></html>";

	struct MHD_Response* response = MHD_create_response_from_buffer(
			strlen(errorstr),
			(void*)errorstr,
			MHD_RESPMEM_PERSISTENT);

	if (response != NULL) {
		int ret = MHD_queue_response(
				connection,
				MHD_HTTP_INTERNAL_SERVER_ERROR,
				response);
		MHD_destroy_response(response);

		return ret;
	} else {
		return MHD_NO;
	}
}

