#include "simple_form.h"

#include "server_error.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int _gen_form(struct MHD_Connection* connection, const char* post_url)
{
	char* page = (char*)malloc(BUFSIZ);
	sprintf(
			page,
			"<html><body><h1>Simple Form</h1>What is your name?"
			"<form action=\"%s\" method=\"POST\">"
			"<input name=\"name\" type=\"text\" />"
			"<input type=\"submit\" value=\"Submit\" />"
			"</form></body></html>",
			post_url);


	struct MHD_Response* response = MHD_create_response_from_buffer(
			strlen(page),
			(void*)page,
			MHD_RESPMEM_MUST_FREE);

	if (response != NULL) {
		int ret = MHD_queue_response(
				connection,
				MHD_HTTP_OK,
				response);
		MHD_destroy_response(response);
		return ret;
	} else {
		return server_error(connection);
	}
}

int form_data_iterator(
		void* cls,
		enum MHD_ValueKind kind,
		const char* key,
		const char* filename,
		const char* mime_type,
		const char* encoding,
		const char* data,
		uint64_t offset,
		size_t len)
{
	if (strncmp(key, "name", 5) != 0) {
		return MHD_YES;
	} else {
		STATE state = cls;
		if (len > 0 && len < BUFSIZ - 64) {
			state->formdata = (char*)malloc(BUFSIZ - 64);
			if (state->formdata == NULL) {
				state->formdatalen = 0;
				return MHD_NO;
			}
			strncpy(state->formdata, data + offset, len);
			state->formdatalen = strnlen(state->formdata, len);
			state->formdata = realloc(
					state->formdata,
					state->formdatalen);
		} else {
			state->formdatalen = 0;
		}

		return MHD_NO;
	}
}

int _gen_result(struct MHD_Connection* connection, STATE state)
{
	if (state->formdatalen <= 0
			|| (strnlen(state->formdata, state->formdatalen)
					== state->formdatalen
				&& *((char*)state->formdata
						+ state->formdatalen)
					!= '\0')
			|| BUFSIZ - 64 <= state->formdatalen) {
		return server_error(connection);
	}

	char* page = (char*)malloc(BUFSIZ);
	snprintf(
			page,
			BUFSIZ,
			"<html><body><h1>Simple Form Result</h1>Welcome %s!"
			"</body></html>",
			(char*)state->formdata);


	struct MHD_Response* response = MHD_create_response_from_buffer(
			strlen(page),
			(void*)page,
			MHD_RESPMEM_MUST_FREE);

	if (response != NULL) {
		int ret = MHD_queue_response(
				connection,
				MHD_HTTP_OK,
				response);
		MHD_destroy_response(response);
		return ret;
	} else {
		return MHD_NO;
	}
}


