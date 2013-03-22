#include "example.h"

#include <stdio.h>
#include <string.h>
#include <time.h>

int answer_to_connection(
		void* cls,
		struct MHD_Connection* connection,
		const char* url,
		const char* method,
		const char* version,
		const char* upload_data,
		size_t* upload_data_size,
		void** con_cls)
{
	char page[BUFSIZ];
	char* (*fp)(const time_t*) = NULL;
	fp = cls;
	time_t now = time(NULL);
	sprintf(page, "<html><body>%s</body></html>", fp(&now));
	struct MHD_Response* response;
	int ret;

	response = MHD_create_response_from_buffer(
			strlen(page),
			(void*)page,
			MHD_RESPMEM_PERSISTENT);

	ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
	MHD_destroy_response(response);

	return ret;
}

