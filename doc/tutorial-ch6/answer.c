#include "answer.h"

#include "state.h"
#include "simple_form.h"
#include "server_error.h"
#include "bad_method.h"
#include "not_found.h"
#include "method_options.h"
#include <stdlib.h>
#include <string.h>

#define POSTBUFFERSIZE 512 /*between 256 and 1024, just like the docs say*/
#define GETMETHODS MHD_HTTP_METHOD_GET ", " MHD_HTTP_METHOD_HEAD ", " MHD_HTTP_METHOD_OPTIONS
#define POSTMETHODS MHD_HTTP_METHOD_POST ", " MHD_HTTP_METHOD_OPTIONS
#define ALLMETHODS MHD_HTTP_METHOD_OPTIONS ", " MHD_HTTP_METHOD_GET ", " MHD_HTTP_METHOD_HEAD ", " MHD_HTTP_METHOD_POST

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
	if (strncmp(url, "/form.html", 11) == 0) {
		if (strncmp(method, MHD_HTTP_METHOD_OPTIONS, 25) == 0) {
			return method_options(connection, POSTMETHODS);
		} else if (strncmp(method, MHD_HTTP_METHOD_POST, 25) != 0) {
			return bad_method(connection, POSTMETHODS);
		} else if (*con_cls == NULL) {
			STATE state = (STATE)malloc(sizeof(struct STATESTRUCT));
			if (state == NULL) {
				return MHD_NO;
			}
	
			state->processor = MHD_create_post_processor(
					connection,
					POSTBUFFERSIZE,
					&form_data_iterator,
					(void*)state);
			if (state->processor == NULL) {
				free(state);
				return server_error(connection);
			}
	
			strncpy(state->method, method, 25);
			state->formdatalen = 0;

			*con_cls = (void*)state;
			return MHD_YES;
		} else if (*upload_data_size != 0) {
			STATE state = *con_cls;
			MHD_post_process(
					state->processor,
					upload_data,
					*upload_data_size);
			*upload_data_size = 0;
			return MHD_YES;
		} else {
			return gen_result(connection, *con_cls);
		}
	} else if (strncmp(url, "/index.html", 12) == 0
			|| strncmp(url, "/index.htm", 11) == 0
			|| strncmp(url, "/", 2) == 0) {
		if (strncmp(method, MHD_HTTP_METHOD_OPTIONS, 25) == 0) {
			return method_options(connection, GETMETHODS);
		} else if (strncmp(method, MHD_HTTP_METHOD_HEAD, 25) != 0
				&& strncmp(method, MHD_HTTP_METHOD_GET, 25)
					!= 0) {
			return bad_method(connection, GETMETHODS);
		} else if (*con_cls == NULL) {
			STATE state = (STATE)malloc(sizeof(struct STATESTRUCT));
			if (state == NULL) {
				return MHD_NO;
			}

			strncpy(state->method, method, 25);
			state->formdatalen = 0;

			*con_cls = (void*)state;
			return MHD_YES;
		} else {
			return gen_form(connection, "/form.html");
		}
	} else if (strncmp(method, MHD_HTTP_METHOD_OPTIONS, 25) == 0
			&& strncmp(url, "*", 2) == 0) {
		return method_options(connection, ALLMETHODS);
	} else {
		return not_found(connection, "/", "the front page");
	}

}

