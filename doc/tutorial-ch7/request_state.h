#ifndef WEBSITES_REQUEST_STATE_H
#define WEBSITES_REQUEST_STATE_H

#include <microhttpd.h>

#include "common_macros.h"
#include <stdio.h>

typedef struct REQUEST_STATE_STRUCT {
	char method[25];
	struct MHD_PostProcessor* processor;
	FILE* fd;
	BOOL was_filename_issue;
	BOOL was_error;
} * REQUEST_STATE;

REQUEST_STATE new_REQUEST_STATE(
		struct MHD_Connection* connection,
		const char* method,
		MHD_PostDataIterator posthandler);

void destroy_REQUEST_STATE(REQUEST_STATE rstate);

BOOL request_file_opened(REQUEST_STATE rstate);

BOOL open_request_file(REQUEST_STATE rstate, const char* filename);

#endif
