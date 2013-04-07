#include "service_unavailable.h"

#include <string.h>

int _service_unavailable(struct MHD_Connection* connection)
{
	const char* errorstr = "<html><body><h1>Service Unavailable</h1>The "
		"server is unable to respond to requests at this time.<br />"
		"Please try again later.</body></html>";

	struct MHD_Response* response = MHD_create_response_from_buffer(
			strlen(errorstr),
			(void*)errorstr,
			MHD_RESPMEM_PERSISTENT);

	if (response != NULL) {
		int ret = MHD_queue_response(
				connection,
				MHD_HTTP_SERVICE_UNAVAILABLE,
				response);
		if (ret != MHD_NO) {
			ret = MHD_add_response_footer(
					response,
					MHD_HTTP_HEADER_CONNECTION,
					"close");
		}
		MHD_destroy_response(response);

		return ret;
	} else {
		return MHD_NO;
	}
}

