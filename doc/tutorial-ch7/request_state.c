#include "request_state.h"

#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define POST_BUFFER_SIZE 512
#define FILE_SAVE_FOLDER "/tmp"

REQUEST_STATE new_REQUEST_STATE(
		struct MHD_Connection* connection,
		const char* method,
		MHD_PostDataIterator posthandler)
{
	REQUEST_STATE rstate = (REQUEST_STATE)malloc(
			sizeof(struct REQUEST_STATE_STRUCT));
	if (rstate == NULL) {
		return NULL;
	}

	strncpy(rstate->method, method, 25);

	rstate->fd = NULL;

	rstate->was_filename_issue = FALSE;
	rstate->was_error = FALSE;

	if (SMATCH(method, MHD_HTTP_METHOD_POST)) {
		rstate->processor = MHD_create_post_processor(
				connection,
				POST_BUFFER_SIZE,
				posthandler,
				(void*)rstate);
		if (rstate->processor == NULL) {
			rstate->was_error = TRUE;
		}
	} else {
		rstate->processor = NULL;
	}

	return rstate;
}

void destroy_REQUEST_STATE(REQUEST_STATE rstate)
{
	if (rstate->fd != NULL) {
		fclose(rstate->fd);
	}

	if (rstate->processor != NULL) {
		MHD_destroy_post_processor(rstate->processor);
	}

	free(rstate);
}

BOOL request_file_opened(REQUEST_STATE rstate)
{
	return rstate->fd != NULL;
}

BOOL open_request_file(REQUEST_STATE rstate, const char* filename)
{
	if (!(isalnum(filename[0]) || filename[0] == '-' || filename[0] == '_')
			|| strchr(filename, '/') != NULL
			|| strchr(filename, '$') != NULL
			|| strchr(filename, '\\') != NULL) {
		rstate->was_filename_issue = TRUE;
		return FALSE;
	}

	char* fullfilename = NEWSTRING;
	snprintf(fullfilename, BUFSIZ, FILE_SAVE_FOLDER "/%s", filename);
	SHRINKSTR(fullfilename);

	FILE* tfd = fopen(fullfilename, "rb");
	if (tfd != NULL) {
		fclose(tfd);
		rstate->was_filename_issue = TRUE;
		return FALSE;
	} else {
		rstate->fd = fopen(fullfilename, "ab");
		if (rstate->fd == NULL) {
			rstate->was_error = TRUE;
			return FALSE;
		} else {
			return TRUE;
		}
	}
}

