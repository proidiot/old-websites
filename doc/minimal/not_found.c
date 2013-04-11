#include "not_found.h"

#include "common_macros.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <stdlib.h>

int _not_found(
		struct MHD_Connection* connection,
		const char* default_url,
		const char* url_description)
{
	char* error_page = NEWSTRING;
	if (error_page == NULL) {
		return MHD_NO;
	}
	snprintf(
			error_page, 
			BUFSIZ,
			"<html><body><h1>Page Not Found</h1>The page that was "
			"requested does not exist.<br />A page that does "
			"exist is <a href=\"%s\">%s</a>.</body></html>",
			default_url,
			url_description);

	SHRINKSTR(error_page);

	struct MHD_Response* response = MHD_create_response_from_buffer(
			strlen(error_page),
			(void*)error_page,
			MHD_RESPMEM_MUST_FREE);

	if (response != NULL) {
		int ret = MHD_queue_response(
				connection,
				MHD_HTTP_NOT_FOUND,
				response);
		MHD_destroy_response(response);
		return ret;
	} else {
		free(error_page);
		return MHD_NO;
	}
}

