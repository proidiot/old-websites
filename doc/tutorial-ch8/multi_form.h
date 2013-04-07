#ifndef WEBSITES_MULTI_FORM_H
#define WEBSITES_MULTI_FORM_H

#include <microhttpd.h>
#include "request_state.h"
#include "daemon_state.h"

#ifdef DEBUG
#include "debug.h"
#define gen_front(c,s) _debug_int_ret(__FILE__,__LINE__,_gen_front((c),(s)),"gen_front")
#define gen_name_form(c,s) _debug_int_ret(__FILE__,__LINE__,_gen_name_form((c),(s)),"gen_name_form")
#define gen_job_form(c,s) _debug_int_ret(__FILE__,__LINE__,_gen_job_form((c),(s)),"gen_job_form")
#define gen_result(c,s) _debug_int_ret(__FILE__,__LINE__,_gen_result((c),(s)),"gen_result")
#else
#define gen_front(c,s) _gen_front((c),(s))
#define gen_name_form(c,s) _gen_name_form((c),(s))
#define gen_job_form(c,s) _gen_job_form((c),(s))
#define gen_result(c,s) _gen_result((c),(s))
#endif

#define FORM_FRONT_URL "/front.html"
#define NAME_FORM_URL "/name.html"
#define JOB_FORM_URL "/job.html"
#define FORM_RESULT_URL "/result.html"

int _gen_front(struct MHD_Connection* connection, SESSION session);

int _gen_name_form(struct MHD_Connection* connection, SESSION session);

int _gen_job_form(struct MHD_Connection* connection, SESSION session);

int _gen_result(struct MHD_Connection* connection, SESSION session);

int form_data_iterator(
		void* cls,
		enum MHD_ValueKind kind,
		const char* key,
		const char* filename,
		const char* mime_type,
		const char* encoding,
		const char* data,
		uint64_t offset,
		size_t len);

#endif
