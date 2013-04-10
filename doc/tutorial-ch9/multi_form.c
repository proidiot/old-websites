#include "multi_form.h"

#include "server_error.h"
#include "common_macros.h"
#include "debug.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int _gen_front(struct MHD_Connection* connection, REQUEST_STATE rstate)
{
	if (rstate == NULL || rstate->session == NULL) {
		return server_error(connection);
	}
	SESSION session = rstate->session;

	const char* top = "<html><body><h1>Session-Based Form Example</h1>"
		"This form uses a session cookie to keep track of your "
		"progress.";
	const char* no_data = "<br />Please click the button below to begin.";
	const char* partial_data = "<br />Please click the button below to "
		"complete the form.";
	const char* welcome = "<br />Welcome back, %s!";
	const char* form_start = "<br /><form action=\"";
	const char* form_middle = "\" method=\"POST\" "
		"enctype=\"multipart/form-data\"><fieldset><legend>Multi-Page "
		"Form</legend><input type=\"submit\" value=\"";
	const char* form_end = "\" /></fieldset></form></body></html>";
	const char* begin = "Begin &gt;";
	const char* continue_val = "Continue &gt;";
	const char* modify = "Modify &gt;";
	char* page;

	size_t len = strlen(top)
		+ strlen(form_start)
		+ strlen(form_middle)
		+ strlen(form_end) + 1;

	if (session->name_set && session->job_set) {
		size_t tlen = strlen(welcome) - 2 + strlen(session->name) + 1;
		char* twelcome = (char*)malloc(tlen);
		if (twelcome == NULL) {
			return server_error(connection);
		}
		snprintf(twelcome, tlen, welcome, session->name);
		len += tlen - 1 + strlen(NAME_FORM_URL) + strlen(modify);
		page = (char*)malloc(len);
		if (page == NULL) {
			free(twelcome);
			return server_error(connection);
		}
		snprintf(
				page,
				len,
				"%s%s%s%s%s%s%s",
				top,
				twelcome,
				form_start,
				NAME_FORM_URL,
				form_middle,
				modify,
				form_end);
		free(twelcome);
	} else if (session->name_set) {
		size_t tlen = strlen(welcome) - 2 + strlen(session->name) + 1;
		char* twelcome = (char*)malloc(tlen);
		if (twelcome == NULL) {
			return server_error(connection);
		}
		snprintf(twelcome, tlen, welcome, session->name);
		len += tlen - 1
			+ strlen(partial_data)
			+ strlen(JOB_FORM_URL)
			+ strlen(continue_val);
		page = (char*)malloc(len);
		if (page == NULL) {
			free(twelcome);
			return server_error(connection);
		}
		snprintf(
				page,
				len,
				"%s%s%s%s%s%s%s%s",
				top,
				twelcome,
				partial_data,
				form_start,
				JOB_FORM_URL,
				form_middle,
				continue_val,
				form_end);
		free(twelcome);
	} else if (session->job_set) {
		len += strlen(partial_data)
			+ strlen(NAME_FORM_URL)
			+ strlen(continue_val);
		page = (char*)malloc(len);
		if (page == NULL) {
			return server_error(connection);
		}
		snprintf(
				page,
				len,
				"%s%s%s%s%s%s%s",
				top,
				partial_data,
				form_start,
				NAME_FORM_URL,
				form_middle,
				continue_val,
				form_end);
	} else {
		len += strlen(no_data) + strlen(NAME_FORM_URL) + strlen(begin);
		page = (char*)malloc(len);
		if (page == NULL) {
			return server_error(connection);
		}
		snprintf(
				page,
				len,
				"%s%s%s%s%s%s%s",
				top,
				no_data,
				form_start,
				NAME_FORM_URL,
				form_middle,
				begin,
				form_end);
	}

	struct MHD_Response* response = MHD_create_response_from_buffer(
			strnlen(page, len),
			(void*)page,
			MHD_RESPMEM_MUST_FREE);

	if (response != NULL) {
		int ret = send_cookie(rstate, response);
		if (ret != MHD_NO) {
			ret = MHD_queue_response(
					connection,
					MHD_HTTP_OK,
					response);
		}
		MHD_destroy_response(response);
		return ret;
	} else {
		free(page);
		return server_error(connection);
	}
}

int _gen_name_form(struct MHD_Connection* connection, REQUEST_STATE rstate)
{
	if (rstate == NULL || rstate->session == NULL) {
		return server_error(connection);
	}
	SESSION session = rstate->session;

	const char* top = "<html><body><h1>Session-Based Form Example</h1>"
		"This form uses a session cookie to keep track of your "
		"progress.";
	const char* form_start = "<br /><form action=\"";
	const char* form_middle = "\" method=\"POST\" "
		"enctype=\"multipart/form-data\"><fieldset><legend>Multi-Page "
		"Form</legend>Please enter your name:<br /><input "
		"type=\"text\" name=\"name\" value=\"";
	const char* form_submit = "\" /><br /><input type=\"submit\" value=\"";
	const char* form_end = "\" /></fieldset></form></body></html>";
	const char* next = "Next &gt;";
	const char* finish = "Finish";
	const char* url;
	const char* old_name;
	const char* submit_val;

	if (session->name_set) {
		url = JOB_FORM_URL;
		old_name = session->name;
		submit_val = next;
	} else if (session->job_set) {
		url = FORM_RESULT_URL;
		old_name = "";
		submit_val = finish;
	} else {
		url = JOB_FORM_URL;
		old_name = "";
		submit_val = next;
	}

	size_t len = strlen(top)
		+ strlen(form_start)
		+ strlen(url)
		+ strlen(form_middle)
		+ strlen(old_name)
		+ strlen(form_submit)
		+ strlen(submit_val)
		+ strlen(form_end) + 1;

	char* page = (char*)malloc(len);
	if (page == NULL) {
		return server_error(connection);
	}
	snprintf(
			page,
			len,
			"%s%s%s%s%s%s%s%s",
			top,
			form_start,
			url,
			form_middle,
			old_name,
			form_submit,
			submit_val,
			form_end);

	struct MHD_Response* response = MHD_create_response_from_buffer(
			strnlen(page, len),
			(void*)page,
			MHD_RESPMEM_MUST_FREE);

	if (response != NULL) {
		int ret = send_cookie(rstate, response);
		if (ret != MHD_NO) {
			ret = MHD_queue_response(
					connection,
					MHD_HTTP_OK,
					response);
		}
		MHD_destroy_response(response);
		return ret;
	} else {
		free(page);
		return server_error(connection);
	}
}

int _gen_job_form(struct MHD_Connection* connection, REQUEST_STATE rstate)
{
	if (rstate == NULL || rstate->session == NULL) {
		return server_error(connection);
	}
	SESSION session = rstate->session;

	const char* top = "<html><body><h1>Session-Based Form Example</h1>"
		"This form uses a session cookie to keep track of your "
		"progress.";
	const char* form_start = "<br /><form action=\"";
	const char* form_middle = "\" method=\"POST\" "
		"enctype=\"multipart/form-data\"><fieldset><legend>Multi-Page "
		"Form</legend>Please enter your job:<br /><input "
		"type=\"text\" name=\"job\" value=\"";
	const char* form_submit = "\" /><br /><input type=\"submit\" value=\"";
	const char* form_end = "\" /></fieldset></form></body></html>";
	const char* next = "Next &gt;";
	const char* finish = "Finish";
	const char* url;
	const char* old_job;
	const char* submit_val;

	if (session->job_set) {
		old_job = session->job;
	} else {
		old_job = "";
	}
	if (!session->name_set) {
		url = NAME_FORM_URL;
		submit_val = next;
	} else {
		url = FORM_RESULT_URL;
		submit_val = finish;
	}

	size_t len = strlen(top)
		+ strlen(form_start)
		+ strlen(url)
		+ strlen(form_middle)
		+ strlen(old_job)
		+ strlen(form_submit)
		+ strlen(submit_val)
		+ strlen(form_end) + 1;

	char* page = (char*)malloc(len);
	if (page == NULL) {
		return server_error(connection);
	}
	snprintf(
			page,
			len,
			"%s%s%s%s%s%s%s%s",
			top,
			form_start,
			url,
			form_middle,
			old_job,
			form_submit,
			submit_val,
			form_end);

	struct MHD_Response* response = MHD_create_response_from_buffer(
			strnlen(page, len),
			(void*)page,
			MHD_RESPMEM_MUST_FREE);

	if (response != NULL) {
		int ret = send_cookie(rstate, response);
		if (ret != MHD_NO) {
			ret = MHD_queue_response(
					connection,
					MHD_HTTP_OK,
					response);
		}
		MHD_destroy_response(response);
		return ret;
	} else {
		free(page);
		return server_error(connection);
	}
}

int _gen_result(struct MHD_Connection* connection, REQUEST_STATE rstate)
{
	if (rstate == NULL || rstate->session == NULL) {
		return server_error(connection);
	} else if (!(rstate->session->name_set && rstate->session->job_set)) {
		return _gen_front(connection, rstate);
	}
	SESSION session = rstate->session;

	const char* fpage = "<html><body><h1>Session-Based Form Example</h1>"
		"This form uses a session cookie to keep track of your "
		"progress.<br />You have completed the form!<br />The "
		"information we have retrieved is:<ul><li>Your name is: %s"
		"</li><li>Your job is: %s</li></ul><br />You can return to the "
		"<a href=\"%s\">home page</a> if you like.</body></html>";

	size_t len = strlen(fpage) - 6 + 1
		+ strlen(session->name)
		+ strlen(session->job)
		+ strlen(FORM_FRONT_URL);

	char* page = (char*)malloc(len);
	if (page == NULL) {
		return server_error(connection);
	}

	snprintf(
			page,
			len,
			fpage,
			session->name,
			session->job,
			FORM_FRONT_URL);

	struct MHD_Response* response = MHD_create_response_from_buffer(
			strlen(page),
			(void*)page,
			MHD_RESPMEM_MUST_FREE);

	if (response != NULL) {
		int ret = send_cookie(rstate, response);
		if (ret != MHD_NO) {
			ret = MHD_queue_response(
					connection,
					MHD_HTTP_OK,
					response);
		}
		MHD_destroy_response(response);
		return ret;
	} else {
		free(page);
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
	REQUEST_STATE rstate = cls;
	SESSION session = rstate->session;
	if (session == NULL) {
		rstate->was_error = TRUE;
		return MHD_NO;
	}

	if (!SMATCH_ANY(key, "name", "job")) {
		return MHD_YES;
	} else if (SMATCH(key, "name")) {
		if (append_encoded_name(rstate, data, len)) {
			debug("Able to append name.");
			return MHD_YES;
		} else {
			debug("Unable to append name.");
			return MHD_NO;
		}
	} else {
		if (append_encoded_job(rstate, data, len)) {
			debug("Able to append job.");
			return MHD_YES;
		} else {
			debug("Unable to append job.");
			return MHD_NO;
		}
	}
}


