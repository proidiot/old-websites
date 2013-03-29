#ifndef WEBSITES_SIMPLE_FORM_H
#define WEBSITES_SIMPLE_FORM_H

#include <microhttpd.h>
#include "state.h"

#ifdef DEBUG
#include "debug.h"
#define gen_form(c,u) _debug_int_ret(__FILE__,__LINE__,_gen_form((c),u),"gen_form")
#define gen_result(c,s) _debug_int_ret(__FILE__,__LINE__,_gen_result((c),(s)),"gen_result")
#else
#define gen_form(c,u) _gen_form((c),u)
#define gen_result(c,s) _gen_result((c),(s))
#endif

int _gen_form(struct MHD_Connection* connection, const char* post_url);

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

int _gen_result(struct MHD_Connection* connection, STATE state);

#endif
