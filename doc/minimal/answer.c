#include "answer.h"

#include "bad_method.h"
#include "not_found.h"
#include "method_options.h"
#include "server_error.h"
#include "common_macros.h"
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>

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
	if (SMATCH_ANY(
				url,
				"/",
				"/index.htm",
				"/index.html")) {
		/* the requested url is for the front page */

		if (SMATCH(method, MHD_HTTP_METHOD_OPTIONS)) {
			/* the client wanted to know what this page supports */
			return method_options(
					connection,
					COMMA_SEPARATED_STRING_LITERALS(
						MHD_HTTP_METHOD_GET,
						MHD_HTTP_METHOD_HEAD
						MHD_HTTP_METHOD_OPTIONS));
		} else if (!SMATCH_ANY(
					method,
					MHD_HTTP_METHOD_GET,
					MHD_HTTP_METHOD_HEAD,
					MHD_HTTP_METHOD_OPTIONS)) {
			/* the client wanted to do something wierd */
			return bad_method(
					connection,
					COMMA_SEPARATED_STRING_LITERALS(
						MHD_HTTP_METHOD_GET,
						MHD_HTTP_METHOD_HEAD,
						MHD_HTTP_METHOD_OPTIONS));
		} else if (*con_cls == NULL) {
			/* 
			 * good so far...
			 * since this function is called over and over until a
			 * response is made, deferring until this function is
			 * called again gives microhttpd more time to process
			 * and another chance to find issues before we assume
			 * that everything is fine and send a response
			 */
			*con_cls = (void*)connection;

			return MHD_YES;
		} else {
			/* time to send the page */
			const char* page = "<html><body><h1>Hello, browser!"
				"</h1><img src=\"/picture.png\" /></body>"
				"</html>";
			struct MHD_Response* response;
			int ret;

			/* tell microhttpd that we want to send this page */
			response = MHD_create_response_from_buffer(
				strlen(page),
				(void*)page,
				MHD_RESPMEM_PERSISTENT);

			if (response != NULL) {
				/*
				 * microhttpd hasn't exploded yet,
				 * so start sending the response
				 */
				ret = MHD_queue_response(
						connection,
						MHD_HTTP_OK,
						response);
				/* alright, we're done sending our response */
				MHD_destroy_response(response);

				return ret;
			} else {
				/*
				 * something went seriously wrong, and there's
				 * no telling if we can even send an
				 * explanation to the client
				 */
				return MHD_NO;
			}
		}
	} else if (SMATCH(url, "/picture.png")) {
		/* it looks like the client asked for the picture */

		if (SMATCH(method, MHD_HTTP_METHOD_OPTIONS)) {
			/* 
			 * the client wanted to know what it can do with the
			 * picture
			 */
			return method_options(
					connection,
					COMMA_SEPARATED_STRING_LITERALS(
						MHD_HTTP_METHOD_GET,
						MHD_HTTP_METHOD_HEAD
						MHD_HTTP_METHOD_OPTIONS));
		} else if (!SMATCH_ANY(
					method,
					MHD_HTTP_METHOD_GET,
					MHD_HTTP_METHOD_HEAD,
					MHD_HTTP_METHOD_OPTIONS)) {
			/* the client wanted to do something wierd */
			return bad_method(
					connection,
					COMMA_SEPARATED_STRING_LITERALS(
						MHD_HTTP_METHOD_GET,
						MHD_HTTP_METHOD_HEAD,
						MHD_HTTP_METHOD_OPTIONS));
		} else if (*con_cls == NULL) {
			/* 
			 * good so far...
			 * since this function is called over and over until a
			 * response is made, deferring until this function is
			 * called again gives microhttpd more time to process
			 * and another chance to find issues before we assume
			 * that everything is fine and send a response
			 */
			*con_cls = (void*)connection;

			return MHD_YES;
		} else {
			/* time to send the picture */
			int fd;
			struct stat sbuf;
		
			if ((-1 == (fd = open("picture.png", O_RDONLY)))
					|| (0 != fstat(fd, &sbuf))) {
				/*
				 * something went wrong while we tried to open
				 * the file
				 */
				if (fd != -1) {
					close(fd);
				}
		
				return server_error(connection);
			} else {
				/* we were able to open the file */
				struct MHD_Response* response; 
				int ret;
				
				/* 
				 * tell microhttpd that we want to send this
				 * file
				 */
				response = MHD_create_response_from_fd_at_offset(
						sbuf.st_size,
						fd,
						0);
				
				if (response != NULL) {
					/* 
					 * microhttpd hasn't exploded yet,
					 * so let's add the MIME-type header
					 * */
					ret = MHD_add_response_header(
							response,
							MHD_HTTP_HEADER_CONTENT_TYPE,
							"image/png");
	
					if (ret != MHD_NO) {
						/* 
						 * we were able to add the
						 * header, so let's send the
						 * response
						 */
						ret = MHD_queue_response(
								connection,
								MHD_HTTP_OK,
								response);
					}
					/* we're done sending our response */
					MHD_destroy_response(response);
		
					return ret;
				} else {
					/*
					 * something went seriously wrong, and
					 * there's no telling if we can even
					 * send an explanation to the client
					 */
					return MHD_NO;
				}
			}
		}
	} else if (SMATCH(method, MHD_HTTP_METHOD_OPTIONS)
			&& SMATCH(url, "*")) {
		/* the client wants to know what all the server can do */
		return method_options(
				connection,
				COMMA_SEPARATED_STRING_LITERALS(
					MHD_HTTP_METHOD_OPTIONS,
					MHD_HTTP_METHOD_GET,
					MHD_HTTP_METHOD_HEAD));
	} else {
		/* the client asked for an invalid page */
		return not_found(connection, "/", "the front page");
	}
}

