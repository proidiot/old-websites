#include "example.h"

#include <string.h>
#include <stdio.h>

int print_out_key(
		void* cls,
		enum MHD_ValueKind kind,
		const char* key,
		const char* value)
{
	printf("%s: %s\n", key, value);
	return MHD_YES;
}

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
	printf(
			"New %s request for %s using version %s\n",
			method,
			url,
			version);

	MHD_get_connection_values(
			connection,
			MHD_HEADER_KIND,
			&print_out_key,
			NULL);

	return MHD_NO;
}

