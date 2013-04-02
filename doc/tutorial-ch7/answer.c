#include "answer.h"

#include "request_state.h"
#include "simple_upload_form.h"
#include "server_error.h"
#include "bad_method.h"
#include "not_found.h"
#include "method_options.h"
#include "service_unavailable.h"
#include "daemon_state.h"
#include "common_macros.h"
#include "forbidden.h"
#include <stdlib.h>
#include <string.h>

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
	DAEMON_STATE dstate = (DAEMON_STATE)cls;
	REQUEST_STATE rstate = (REQUEST_STATE)*con_cls;

	if (rstate == NULL && added_client_overloads(dstate)) {
		return service_unavailable(connection);
	} else if (SMATCH(url, "/form.html")) {
		if (SMATCH(method, MHD_HTTP_METHOD_OPTIONS)) {
			return method_options(
					connection,
					COMMA_SEPARATED_STRING_LITERALS(
						MHD_HTTP_METHOD_POST,
						MHD_HTTP_METHOD_OPTIONS));
		} else if (!SMATCH(method, MHD_HTTP_METHOD_POST)) {
			return bad_method(
					connection,
					COMMA_SEPARATED_STRING_LITERALS(
						MHD_HTTP_METHOD_POST,
						MHD_HTTP_METHOD_OPTIONS));
		} else if (rstate == NULL
				&& added_upload_client_overloads(
					dstate,
					TRUE)) {
			return service_unavailable(connection);
		} else if (rstate == NULL) {
			rstate = new_REQUEST_STATE(
					connection,
					method, 
					&form_data_iterator);
			if (rstate == NULL) {
				return MHD_NO;
			}

			*con_cls = (void*)rstate;

			if (rstate->was_error) {
				return server_error(connection);
			} else {
				return MHD_YES;
			}
		} else if (*upload_data_size != 0) {
			MHD_post_process(
					rstate->processor,
					upload_data,
					*upload_data_size);
			*upload_data_size = 0;
			return MHD_YES;
		} else if (rstate->was_filename_issue) {
			return forbidden(
					connection,
					"The server is unable to use the "
					"given filename. Please try a "
					"different file name.");
		} else if (rstate->was_error) {
			return server_error(connection);
		} else {
			return gen_result(connection);
		}
	} else if (SMATCH_ANY(url, "/index.html", "/index.htm", "/")) {
		if (SMATCH(method, MHD_HTTP_METHOD_OPTIONS)) {
			return method_options(
					connection,
					COMMA_SEPARATED_STRING_LITERALS(
						MHD_HTTP_METHOD_GET,
						MHD_HTTP_METHOD_HEAD,
						MHD_HTTP_METHOD_OPTIONS));
		} else if (!SMATCH_ANY(
					method,
					MHD_HTTP_METHOD_HEAD,
					MHD_HTTP_METHOD_GET)) {
			return bad_method(
					connection,
					COMMA_SEPARATED_STRING_LITERALS(
						MHD_HTTP_METHOD_GET,
						MHD_HTTP_METHOD_HEAD,
						MHD_HTTP_METHOD_OPTIONS));
		} else if (rstate == NULL) {
			rstate = new_REQUEST_STATE(connection, method, NULL);
			if (rstate == NULL) {
				return MHD_NO;
			}

			*con_cls = (void*)rstate;

			if (rstate->was_error) {
				return server_error(connection);
			} else {
				return MHD_YES;
			}
		} else {
			return gen_form(connection, "/form.html", dstate);
		}
	} else if (SMATCH(method, MHD_HTTP_METHOD_OPTIONS)
			&& SMATCH(url, "*")) {
		return method_options(
				connection,
				COMMA_SEPARATED_STRING_LITERALS(
					MHD_HTTP_METHOD_OPTIONS,
					MHD_HTTP_METHOD_GET,
					MHD_HTTP_METHOD_HEAD,
					MHD_HTTP_METHOD_POST));
	} else {
		return not_found(connection, "/", "the front page");
	}
}

