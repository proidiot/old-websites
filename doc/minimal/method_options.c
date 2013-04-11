#include "method_options.h"

#include <stdarg.h>

int _method_options(struct MHD_Connection* connection, const char* methods)
{
	struct MHD_Response* response = MHD_create_response_from_buffer(
			0,
			NULL,
			MHD_RESPMEM_PERSISTENT);

	if (response != NULL) {
		int ret = MHD_add_response_header(
				response,
				MHD_HTTP_HEADER_ALLOW,
				methods);
		if (ret != MHD_NO) {
			ret = MHD_queue_response(
					connection,
					MHD_HTTP_OK,
					response);
		}
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

