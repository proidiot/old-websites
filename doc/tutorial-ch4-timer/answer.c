#include "answer.h"

#include <config.h>
#include <string.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <math.h>
#include <stdlib.h>

#define MIMETYPE "image/png"
#define DONETIME 60
#define REFRESHTIME 5
#define TIMECHUNKS 10

#ifdef DEBUG
void _print_debug_line(const char* file, const int line, const char* fmt, ...)
{
	char temp[BUFSIZ];
	va_list ap;
	va_start(ap, fmt);
	vsprintf(temp, fmt, ap);
	fprintf(stderr, "DEBUG: %s:%d: %s\n", file, line, temp);
}
#define debug(...) _print_debug_line(__FILE__,__LINE__,__VA_ARGS__)
#else
#define debug(...) /* Debugging disabled. */
#endif

int save_host_value(
		void* cls,
		enum MHD_ValueKind kind,
		const char* key,
		const char* value)
{
	if (strncmp(key, "Host", 5) == 0
			&& strnlen(value, BUFSIZ - 16) < BUFSIZ - 16) {
		char* host = (char*)malloc(BUFSIZ - 16);
		strncpy(host, value, BUFSIZ - 16);
		*((char**)cls) = host;
	}
	return MHD_YES;
}

int internal_server_error(struct MHD_Connection* connection)
{
	const char* errorstr = "<html><body>An internal error has occured!"
		"</body></html>";

	struct MHD_Response* response = MHD_create_response_from_buffer(
			strlen(errorstr),
			(void*)errorstr,
			MHD_RESPMEM_PERSISTENT);

	if (response != NULL) {
		int ret = MHD_queue_response(
				connection,
				MHD_HTTP_INTERNAL_SERVER_ERROR,
				response);
		MHD_destroy_response(response);

		return ret;
	} else {
		return MHD_NO;
	}
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
	unsigned char* buffer = NULL;
	struct MHD_Response* response;

	int fd;
	int ret;
	struct stat sbuf;

	if (0 != strncmp(method, "GET", 4)) {
		debug("Receied a non-GET request.");
		return MHD_NO;
	}

	if (strncmp(url, "/red.png", 9) == 0) {
		debug("Request for red.png.");
		if ((-1 == (fd = open("red.png", O_RDONLY)))
				|| (0 != fstat(fd, &sbuf))) {
			if (fd != -1) {
				close(fd);
			}
	
			debug("Unable to get red.png.");
			return internal_server_error(connection);
		}
	
		response = MHD_create_response_from_fd_at_offset(
				sbuf.st_size,
				fd,
				0);
		MHD_add_response_header(response, "Content-Type", MIMETYPE);
		ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
		MHD_destroy_response(response);
	} else if (strncmp(url, "/green.png", 11) == 0) {
		debug("Request for green.png.");
		if ((-1 == (fd = open("green.png", O_RDONLY)))
				|| (0 != fstat(fd, &sbuf))) {
			if (fd != -1) {
				close(fd);
			}
	
			debug("Unable to get green.png.");
			return internal_server_error(connection);
		}
	
		response = MHD_create_response_from_fd_at_offset(
				sbuf.st_size,
				fd,
				0);
		MHD_add_response_header(response, "Content-Type", MIMETYPE);
		ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
		MHD_destroy_response(response);
	} else if (strncmp(url, "/index.html", 12) == 0
			|| strncmp(url, "/index.htm", 11) == 0
			|| strncmp(url, "/", 2) == 0) {
		debug("Request for index.");
		const time_t now = time(NULL);
		const char* top = "<html><body>";
		const char* ttop = "<table><tr>";
		const char* red = "<td><img src=\"/red.png\" /></td>";
		const char* green = "<td><img src=\"/green.png\" /></td>";
		const char* tbottom = "</tr></table>";
		const char* done = "Done";
		const char* bottom = "</body></html>";
		char* tpage;
		int refresh = (1 == 1);
		char* page = (char*)malloc(BUFSIZ);
		if (page == NULL) {
			debug("Unable to malloc the page.");
			return internal_server_error(connection);
		}

		tpage = stpcpy(page, top);
		if (now >= *((time_t*)cls) + DONETIME) {
			debug("Timer has finished.");
			refresh = (0 == 1);
			tpage = stpcpy(tpage, done);
		} else {
			debug("Timer is still going.");
			int i = 0;
			float span = DONETIME / (1.0 * TIMECHUNKS);
			tpage = stpcpy(tpage, ttop);
			for (i = 0; i < TIMECHUNKS; i++) {
				if (*((time_t*)cls) + ceil((i + 1) * span)
						<= now) {
					tpage = stpcpy(tpage, green);
				} else {
					tpage = stpcpy(tpage, red);
				}
			}
			tpage = stpcpy(tpage, tbottom);
		}
		tpage = stpcpy(tpage, bottom);
		debug("HTML constructed.");

		response = MHD_create_response_from_buffer(
				tpage - page,
				page,
				MHD_RESPMEM_MUST_FREE);
		if (response == NULL) {
			free(page);
			debug("Unable to get the response.");
			return internal_server_error(connection);
		}
		
		if (refresh) {
			char* hoststring = NULL;
			MHD_get_connection_values(
					connection,
					MHD_HEADER_KIND,
					&save_host_value,
					&hoststring);

			if (hoststring != NULL) {
				char* refline = (char*)malloc(BUFSIZ);
				sprintf(
						refline,
						"%d; url=http://%s/",
						REFRESHTIME,
						hoststring);
				MHD_add_response_header(
						response,
						"Refresh",
						refline);


				ret = MHD_queue_response(
						connection,
						MHD_HTTP_OK,
						response);
				MHD_destroy_response(response);
				free(hoststring);
			} else {
				debug("Unable to get the host string.");
				return internal_server_error(connection);
			}
		} else {
			ret = MHD_queue_response(
					connection,
					MHD_HTTP_OK,
					response);
			MHD_destroy_response(response);
		}

		debug("Message sent.");
	} else {
		debug("Request for something else.");
		const char* errorstr = "<html><body>You have reached this "
			"page in error. You should go to the "
			"<a href=\"/\">index</a>.</body></html>";

		response = MHD_create_response_from_buffer(
				strlen(errorstr),
				(void*)errorstr,
				MHD_RESPMEM_PERSISTENT);

		if (response != NULL) {
			ret = MHD_queue_response(
					connection,
					MHD_HTTP_NOT_FOUND,
					response);
			MHD_destroy_response(response);
		} else {
			return MHD_NO;
		}
	}

	return ret;
}

