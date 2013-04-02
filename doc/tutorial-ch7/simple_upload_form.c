#include "simple_upload_form.h"

#include "server_error.h"
#include "common_macros.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int _gen_form(
		struct MHD_Connection* connection,
		const char* post_url,
		DAEMON_STATE dstate)
{
	char* page = NEWSTRING;
	if (page == NULL) {
		return MHD_NO;
	}
	snprintf(
			page,
			BUFSIZ,
			"<html><body><h1>Simple Upload Form</h1>There are %d "
			"clients uploading right now.<br /><form "
			"action=\"%s\" method=\"POST\" "
			"enctype=\"multipart/form-data\"><fieldset><legend>"
			"Upload</legend>File to upload:<input name=\"file\" "
			"type=\"file\" /><br /><input type=\"submit\" "
			"value=\"Submit\" /></fieldset></form></body></html>",
			get_current_upload_clients(dstate),
			post_url);

	SHRINKSTR(page);

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
	if (!SMATCH(key, "file")) {
		return MHD_YES;
	} else {
		debug("Getting file: %s", filename);
		REQUEST_STATE rstate = cls;

		if (!request_file_opened(rstate)) {
			debug("File had not been opened.");
			if (!open_request_file(rstate, filename)) {
				debug("Unable to open file.");
				return MHD_NO;
			}
			debug("Able to open file.");
		}
		if (len > 0) {
			if (fwrite(data, len, sizeof(char), rstate->fd)==0) {
				debug("Unable to write.");
				return MHD_NO;
			} else {
				return MHD_YES;
			}
		} else {
			return MHD_YES;
		}
	}
}

int _gen_result(struct MHD_Connection* connection)
{
	const char* page = "<html><body><h1>Simple Upload Form Result</h1>"
		"File uploaded successfully.</body></html>";

	struct MHD_Response* response = MHD_create_response_from_buffer(
			strlen(page),
			(void*)page,
			MHD_RESPMEM_PERSISTENT);

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


