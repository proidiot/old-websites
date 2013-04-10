#ifndef WEBSITES_MULTI_FORM_H
#define WEBSITES_MULTI_FORM_H

#include <microhttpd.h>
#include "request_state.h"

#ifdef DEBUG
#include "debug.h"
#define gen_front(c,rs) _debug_int_ret(__FILE__,__LINE__,_gen_front((c),(rs)),"gen_front")
#define gen_name_form(c,rs) _debug_int_ret(__FILE__,__LINE__,_gen_name_form((c),(rs)),"gen_name_form")
#define gen_job_form(c,rs) _debug_int_ret(__FILE__,__LINE__,_gen_job_form((c),(rs)),"gen_job_form")
#define gen_result(c,rs) _debug_int_ret(__FILE__,__LINE__,_gen_result((c),(rs)),"gen_result")
#else
#define gen_front(c,rs) _gen_front((c),(rs))
#define gen_name_form(c,rs) _gen_name_form((c),(rs))
#define gen_job_form(c,rs) _gen_job_form((c),(rs))
#define gen_result(c,rs) _gen_result((c),(rs))
#endif

#define FORM_FRONT_URL "/front.html"
#define NAME_FORM_URL "/name.html"
#define JOB_FORM_URL "/job.html"
#define FORM_RESULT_URL "/result.html"

int _gen_front(struct MHD_Connection* connection, REQUEST_STATE rstate);

int _gen_name_form(struct MHD_Connection* connection, REQUEST_STATE rstate);

int _gen_job_form(struct MHD_Connection* connection, REQUEST_STATE rstate);

int _gen_result(struct MHD_Connection* connection, REQUEST_STATE rstate);

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
