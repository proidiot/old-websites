#include "request_state.h"

#include "html_encode.h"
#include "base64.h"
#include "debug.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define RAND_LEN 768
#define POST_BUFFER_SIZE 768

REQUEST_STATE new_REQUEST_STATE(
		DAEMON_STATE dstate,
		struct MHD_Connection* connection,
		const char* method,
		MHD_PostDataIterator posthandler)
{
	if (dstate == NULL) {
		debug("DAEMON_STATE was NULL");
		return NULL;
	}

	REQUEST_STATE rstate = (REQUEST_STATE)malloc(
			sizeof(struct REQUEST_STATE_STRUCT));
	if (rstate == NULL) {
		debug("Unable to allocate REQUEST_STATE");
		return NULL;
	}

	strncpy(rstate->method, method, 25);

	const char* cookie = MHD_lookup_connection_value(
			connection,
			MHD_COOKIE_KIND,
			COOKIE_NAME);
	if (cookie == NULL) {
		size_t len = RAND_LEN;
		unsigned char* buf = (unsigned char*)malloc(len);
		if (buf == NULL) {
			debug("Unable to allocate random buffer");
			rstate->was_error = TRUE;
			return rstate;
		}

		FILE* fd = fopen("/dev/urandom", "rb");
		if (fd == NULL) {
			debug("Unable to open random file");
			free(buf);
			rstate->was_error = TRUE;
			return rstate;
		}
		int res = fread(buf, 1, len, fd);
		fclose(fd);
		if (res != len) {
			debug("Did not read correct amount of randomness");
			rstate->was_error = TRUE;
			return rstate;
		}

		size_t enclen;
		rstate->cookie = base64_encode(&enclen, len, buf);
		free(buf);
	} else {
		rstate->cookie = (char*)malloc(strlen(cookie));
		strcpy(rstate->cookie, cookie);
	}

	rstate->session = get_session(dstate, rstate->cookie);

	rstate->name_set = FALSE;
	rstate->job_set = FALSE;

	rstate->was_error = FALSE;

	if (SMATCH(method, MHD_HTTP_METHOD_POST)) {
		rstate->processor = MHD_create_post_processor(
				connection,
				POST_BUFFER_SIZE,
				posthandler,
				(void*)rstate);
		if (rstate->processor == NULL) {
			debug("Unable to initialize POST processor");
			rstate->was_error = TRUE;
		}
	} else {
		rstate->processor = NULL;
	}

	return rstate;
}

void destroy_REQUEST_STATE(REQUEST_STATE rstate, DAEMON_STATE dstate)
{
	if (rstate != NULL) {
		if (rstate->processor != NULL) {
			MHD_destroy_post_processor(rstate->processor);
		}

		if (dstate != NULL && rstate->session != NULL) {
			save_session(dstate, rstate->cookie, rstate->session);
			free(rstate->cookie);
		}
		free(rstate->session);
	
		free(rstate);
	}
}

BOOL append_encoded_name(
		REQUEST_STATE rstate,
		const char* name,
		const size_t len)
{
	if (rstate->name_set) {
		size_t tlen = strlen(rstate->session->name)
			+ (strnlen(name, len) * HTML_ENCODE_MULTIPLIER)
			+ 1;
		char* tname = (char*)malloc(tlen);
		if (tname == NULL) {
			rstate->was_error = TRUE;
			return FALSE;
		}
		char* encoded_name = html_encode(name, len);
		if (encoded_name == NULL) {
			rstate->was_error = TRUE;
			free(tname);
			return FALSE;
		}
		snprintf(
				tname,
				tlen,
				"%s%s",
				rstate->session->name,
				encoded_name);
		free(rstate->session->name);
		SHRINKSAFESTR(tname);
		rstate->session->name = tname;
	} else {
		char* encoded_name = html_encode(name, len);
		if (encoded_name == NULL) {
			rstate->was_error = TRUE;
			return FALSE;
		}
		if (rstate->session->name_set) {
			free(rstate->session->name);
		}

		rstate->session->name = encoded_name;
		rstate->session->name_set = TRUE;
		rstate->name_set = TRUE;
	}
	return TRUE;
}

BOOL append_encoded_job(
		REQUEST_STATE rstate,
		const char* job,
		const size_t len)
{
	if (rstate->job_set) {
		size_t tlen = strlen(rstate->session->job)
			+ (strnlen(job, len) * HTML_ENCODE_MULTIPLIER)
			+ 1;
		char* tjob = (char*)malloc(tlen);
		if (tjob == NULL) {
			rstate->was_error = TRUE;
			return FALSE;
		}
		char* encoded_job = html_encode(job, len);
		if (encoded_job == NULL) {
			rstate->was_error = TRUE;
			free(tjob);
			return FALSE;
		}
		snprintf(
				tjob,
				tlen,
				"%s%s",
				rstate->session->job,
				encoded_job);
		free(rstate->session->job);
		SHRINKSAFESTR(tjob);
		rstate->session->job = tjob;
	} else {
		char* encoded_job = html_encode(job, len);
		if (encoded_job == NULL) {
			rstate->was_error = TRUE;
			return FALSE;
		}
		if (rstate->session->job_set) {
			free(rstate->session->job);
		}

		rstate->session->job = encoded_job;
		rstate->session->job_set = TRUE;
		rstate->job_set = TRUE;
	}
	return TRUE;
}

int send_cookie(REQUEST_STATE rstate, struct MHD_Response* response)
{
	size_t len = strlen(COOKIE_NAME) + 1 + strlen(rstate->cookie) + 1;
	char* cookie_string = (char*)malloc(len);
	if (cookie_string == NULL) {
		debug("Unable to allocate cookie string");
		return MHD_NO;
	}

	snprintf(cookie_string, len, "%s=%s", COOKIE_NAME, rstate->cookie);

	return MHD_add_response_header(
			response,
			MHD_HTTP_HEADER_SET_COOKIE,
			cookie_string);
}

