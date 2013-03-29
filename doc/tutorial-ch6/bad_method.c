#include "bad_method.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int _bad_method(struct MHD_Connection* connection, const char* methods)
{
	char* page = (char*)malloc(BUFSIZ);
	sprintf(
			page,
			"<html><body><h1>Method Not Allowed</h1>The method "
			"that was specified by the request is not one of the "
			"request methods that are allowed.<br />The allowed "
			"request methods are: %s</body></html>",
			methods);


	struct MHD_Response* response = MHD_create_response_from_buffer(
			strlen(page),
			(void*)page,
			MHD_RESPMEM_MUST_FREE);

	if (response != NULL) {
		int ret = MHD_add_response_header(
				response,
				MHD_HTTP_HEADER_ALLOW,
				methods);
		if (ret != MHD_NO) {
			ret = MHD_queue_response(
					connection,
					MHD_HTTP_METHOD_NOT_ALLOWED,
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

