#ifndef WEBSITES_EXAMPLE_H
#define WEBSITES_EXAMPLE_H

#include <microhttpd.h>

int answer_to_connection(
	void* cls,
	struct MHD_Connection* connection,
	const char* url,
	const char* method,
	const char* version,
	const char* upload_data,
	size_t* upload_data_size,
	void** con_cls);

#endif
