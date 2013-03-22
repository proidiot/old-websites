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
	struct MHD_Response* response;
	int ret;

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

	if (strncmp(url, "/index.html", BUFSIZ) == 0
			|| strncmp(url, "/index.htm", BUFSIZ) == 0
			|| strncmp(url, "/", BUFSIZ) == 0) {
		const char* page = "<html><body>This site contains this page "
			"and <a href=\"/another.html\">another</a>.</body>"
			"</html>";
	
		response = MHD_create_response_from_buffer(
				strlen(page),
				(void*)page,
				MHD_RESPMEM_PERSISTENT);
	
		ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
	} else if (strncmp(url, "/another.html", BUFSIZ) == 0) {
		const char* page = "<html><body>This another page. There is "
			"also an <a href=\"/index.html\">index page</a>."
			"</body></html>";
	
		response = MHD_create_response_from_buffer(
				strlen(page),
				(void*)page,
				MHD_RESPMEM_PERSISTENT);
	
		ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
	} else {
		const char* page = "<html><body>You have reached this page in "
			"error. You should go to the "
			"<a href=\"/index.html\">index</a>.</body></html>";
	
		response = MHD_create_response_from_buffer(
				strlen(page),
				(void*)page,
				MHD_RESPMEM_PERSISTENT);
	
		ret = MHD_queue_response(
				connection,
				MHD_HTTP_NOT_FOUND,
				response);
	}
	
	MHD_destroy_response(response);

	return ret;
}

