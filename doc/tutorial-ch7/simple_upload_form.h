#ifndef WEBSITES_SIMPLE_UPLOAD_FORM_H
#define WEBSITES_SIMPLE_UPLOAD_FORM_H

#include <microhttpd.h>
#include "request_state.h"
#include "daemon_state.h"

#ifdef DEBUG
#include "debug.h"
#define gen_form(c,u,ds) _debug_int_ret(__FILE__,__LINE__,_gen_form((c),u,(ds)),"gen_form")
#define gen_result(c) _debug_int_ret(__FILE__,__LINE__,_gen_result((c)),"gen_result")
#else
#define gen_form(c,u) _gen_form((c),u)
#define gen_result(c) _gen_result((c))
#endif

int _gen_form(
		struct MHD_Connection* connection,
		const char* post_url,
		DAEMON_STATE dstate);

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

int _gen_result(struct MHD_Connection* connection);

#endif
