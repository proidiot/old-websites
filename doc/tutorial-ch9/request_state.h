#ifndef WEBSITES_REQUEST_STATE_H
#define WEBSITES_REQUEST_STATE_H

#include <microhttpd.h>

#include "common_macros.h"
#include "session.h"
#include "daemon_state.h"
#include <stdio.h>

#define COOKIE_NAME "SESSION"

typedef struct REQUEST_STATE_STRUCT {
	char method[25];
	struct MHD_PostProcessor* processor;
	char* cookie;
	SESSION session;
	BOOL name_set;
	BOOL job_set;
	BOOL was_error;
} * REQUEST_STATE;

REQUEST_STATE new_REQUEST_STATE(
		DAEMON_STATE dstate,
		struct MHD_Connection* connection,
		const char* method,
		MHD_PostDataIterator posthandler);

void destroy_REQUEST_STATE(REQUEST_STATE rstate, DAEMON_STATE dstate);

BOOL append_encoded_name(
		REQUEST_STATE rstate,
		const char* name,
		const size_t len);

BOOL append_encoded_job(
		REQUEST_STATE rstate,
		const char* job,
		const size_t len);

int send_cookie(REQUEST_STATE rstate, struct MHD_Response* response);

#endif
