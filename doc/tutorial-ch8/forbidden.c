#include "forbidden.h"

#include "common_macros.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int _forbidden(struct MHD_Connection* connection, const char* explanation)
{
	char* page = NEWSTRING;
	if (page == NULL) {
		return MHD_NO;
	}
	snprintf(
			page,
			BUFSIZ,
			"<html><body><h1>Forbidden</h1>The server will not "
			"complete the request.<br />%s</body></html>",
			explanation);

	SHRINKSTR(page);

	struct MHD_Response* response = MHD_create_response_from_buffer(
			strlen(page),
			(void*)page,
			MHD_RESPMEM_MUST_FREE);

	if (response != NULL) {
		int ret = MHD_queue_response(
				connection,
				MHD_HTTP_FORBIDDEN,
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

