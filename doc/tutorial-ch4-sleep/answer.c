#include "answer.h"

#include <string.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define FILENAME "picture.png"
#define MIMETYPE "image/png"

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
	unsigned char* buffer = NULL;
	struct MHD_Response* response;

	int fd;
	int ret;
	struct stat sbuf;

	if (0 != strncmp(method, "GET", 4)) {
		return MHD_NO;
	}

	if ((-1 == (fd = open(FILENAME, O_RDONLY)))
			|| (0 != fstat(fd, &sbuf))) {
		if (fd != -1) {
			close(fd);
		}

		const char* errorstr = "<html><body>An internal error has "
			"occured!</body></html>";

		response = MHD_create_response_from_buffer(
				strlen(errorstr),
				(void*)errorstr,
				MHD_RESPMEM_PERSISTENT);

		if (response != NULL) {
			ret = MHD_queue_response(
					connection,
					MHD_HTTP_INTERNAL_SERVER_ERROR,
					response);
			MHD_destroy_response(response);

			return ret;
		} else {
			return MHD_NO;
		}

	}

	if (strncmp(url, "/big.png", 9) == 0) {
		sleep(30);
	}

	response = MHD_create_response_from_fd_at_offset(sbuf.st_size, fd, 0);
	MHD_add_response_header(response, "Content-Type", MIMETYPE);
	ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
	MHD_destroy_response(response);

	return ret;
}

