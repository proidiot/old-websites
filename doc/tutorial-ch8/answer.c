#include "answer.h"

#include "request_state.h"
#include "multi_form.h"
#include "server_error.h"
#include "bad_method.h"
#include "not_found.h"
#include "method_options.h"
#include "service_unavailable.h"
#include "daemon_state.h"
#include "common_macros.h"
#include "forbidden.h"
#include "debug.h"
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
	} else if (SMATCH_ANY(
				url,
				FORM_FRONT_URL,
				"/",
				"/index.htm",
				"/index.html")) {
		if (SMATCH(method, MHD_HTTP_METHOD_OPTIONS)) {
			return method_options(
					connection,
					COMMA_SEPARATED_STRING_LITERALS(
						MHD_HTTP_METHOD_GET,
						MHD_HTTP_METHOD_HEAD
						MHD_HTTP_METHOD_POST,
						MHD_HTTP_METHOD_OPTIONS));
		} else if (!SMATCH_ANY(
					method,
					MHD_HTTP_METHOD_GET,
					MHD_HTTP_METHOD_HEAD,
					MHD_HTTP_METHOD_POST,
					MHD_HTTP_METHOD_OPTIONS)) {
			return bad_method(
					connection,
					COMMA_SEPARATED_STRING_LITERALS(
						MHD_HTTP_METHOD_GET,
						MHD_HTTP_METHOD_HEAD,
						MHD_HTTP_METHOD_POST,
						MHD_HTTP_METHOD_OPTIONS));
		} else if (rstate == NULL
				&& SMATCH(method, MHD_HTTP_METHOD_POST)
				&& added_upload_client_overloads(
					dstate,
					TRUE)) {
			return service_unavailable(connection);
		} else if (rstate == NULL) {
			rstate = new_REQUEST_STATE(
					dstate,
					connection,
					method, 
					&form_data_iterator);
			if (rstate == NULL) {
				debug("Unable to create new REQUEST_STATE");
				return MHD_NO;
			}

			*con_cls = (void*)rstate;

			return MHD_YES;
		} else if (*upload_data_size != 0) {
			MHD_post_process(
					rstate->processor,
					upload_data,
					*upload_data_size);
			*upload_data_size = 0;
			return MHD_YES;
		} else if (rstate->was_error) {
			return server_error(connection);
		} else {
			return gen_front(connection, rstate);
		}
	} else if (SMATCH(url, NAME_FORM_URL)) {
		if (SMATCH(method, MHD_HTTP_METHOD_OPTIONS)) {
			return method_options(
					connection,
					COMMA_SEPARATED_STRING_LITERALS(
						MHD_HTTP_METHOD_GET,
						MHD_HTTP_METHOD_HEAD
						MHD_HTTP_METHOD_POST,
						MHD_HTTP_METHOD_OPTIONS));
		} else if (!SMATCH_ANY(
					method,
					MHD_HTTP_METHOD_GET,
					MHD_HTTP_METHOD_HEAD,
					MHD_HTTP_METHOD_POST,
					MHD_HTTP_METHOD_OPTIONS)) {
			return bad_method(
					connection,
					COMMA_SEPARATED_STRING_LITERALS(
						MHD_HTTP_METHOD_GET,
						MHD_HTTP_METHOD_HEAD,
						MHD_HTTP_METHOD_POST,
						MHD_HTTP_METHOD_OPTIONS));
		} else if (rstate == NULL
				&& SMATCH(method, MHD_HTTP_METHOD_POST)
				&& added_upload_client_overloads(
					dstate,
					TRUE)) {
			return service_unavailable(connection);
		} else if (rstate == NULL) {
			rstate = new_REQUEST_STATE(
					dstate,
					connection,
					method, 
					&form_data_iterator);
			if (rstate == NULL) {
				debug("Unable to create new REQUEST_STATE");
				return MHD_NO;
			}

			*con_cls = (void*)rstate;

			return MHD_YES;
		} else if (*upload_data_size != 0) {
			MHD_post_process(
					rstate->processor,
					upload_data,
					*upload_data_size);
			*upload_data_size = 0;
			return MHD_YES;
		} else if (rstate->was_error) {
			return server_error(connection);
		} else {
			return gen_name_form(connection, rstate);
		}
	} else if (SMATCH(url, JOB_FORM_URL)) {
		if (SMATCH(method, MHD_HTTP_METHOD_OPTIONS)) {
			return method_options(
					connection,
					COMMA_SEPARATED_STRING_LITERALS(
						MHD_HTTP_METHOD_GET,
						MHD_HTTP_METHOD_HEAD
						MHD_HTTP_METHOD_POST,
						MHD_HTTP_METHOD_OPTIONS));
		} else if (!SMATCH_ANY(
					method,
					MHD_HTTP_METHOD_GET,
					MHD_HTTP_METHOD_HEAD,
					MHD_HTTP_METHOD_POST,
					MHD_HTTP_METHOD_OPTIONS)) {
			return bad_method(
					connection,
					COMMA_SEPARATED_STRING_LITERALS(
						MHD_HTTP_METHOD_GET,
						MHD_HTTP_METHOD_HEAD,
						MHD_HTTP_METHOD_POST,
						MHD_HTTP_METHOD_OPTIONS));
		} else if (rstate == NULL
				&& SMATCH(method, MHD_HTTP_METHOD_POST)
				&& added_upload_client_overloads(
					dstate,
					TRUE)) {
			return service_unavailable(connection);
		} else if (rstate == NULL) {
			rstate = new_REQUEST_STATE(
					dstate,
					connection,
					method, 
					&form_data_iterator);
			if (rstate == NULL) {
				debug("Unable to create new REQUEST_STATE");
				return MHD_NO;
			}

			*con_cls = (void*)rstate;

			return MHD_YES;
		} else if (*upload_data_size != 0) {
			MHD_post_process(
					rstate->processor,
					upload_data,
					*upload_data_size);
			*upload_data_size = 0;
			return MHD_YES;
		} else if (rstate->was_error) {
			return server_error(connection);
		} else {
			return gen_job_form(connection, rstate);
		}
	} else if (SMATCH(url, FORM_RESULT_URL)) {
		if (SMATCH(method, MHD_HTTP_METHOD_OPTIONS)) {
			return method_options(
					connection,
					COMMA_SEPARATED_STRING_LITERALS(
						MHD_HTTP_METHOD_GET,
						MHD_HTTP_METHOD_HEAD
						MHD_HTTP_METHOD_POST,
						MHD_HTTP_METHOD_OPTIONS));
		} else if (!SMATCH_ANY(
					method,
					MHD_HTTP_METHOD_GET,
					MHD_HTTP_METHOD_HEAD,
					MHD_HTTP_METHOD_POST,
					MHD_HTTP_METHOD_OPTIONS)) {
			return bad_method(
					connection,
					COMMA_SEPARATED_STRING_LITERALS(
						MHD_HTTP_METHOD_GET,
						MHD_HTTP_METHOD_HEAD,
						MHD_HTTP_METHOD_POST,
						MHD_HTTP_METHOD_OPTIONS));
		} else if (rstate == NULL
				&& SMATCH(method, MHD_HTTP_METHOD_POST)
				&& added_upload_client_overloads(
					dstate,
					TRUE)) {
			return service_unavailable(connection);
		} else if (rstate == NULL) {
			rstate = new_REQUEST_STATE(
					dstate,
					connection,
					method, 
					&form_data_iterator);
			if (rstate == NULL) {
				debug("Unable to create new REQUEST_STATE");
				return MHD_NO;
			}

			*con_cls = (void*)rstate;

			return MHD_YES;
		} else if (*upload_data_size != 0) {
			MHD_post_process(
					rstate->processor,
					upload_data,
					*upload_data_size);
			*upload_data_size = 0;
			return MHD_YES;
		} else if (rstate->was_error) {
			return server_error(connection);
		} else {
			return gen_result(connection, rstate);
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

