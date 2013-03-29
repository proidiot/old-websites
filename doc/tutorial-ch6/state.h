#ifndef WEBSITES_STATE_H
#define WEBSITES_STATE_H

#include <microhttpd.h>

typedef struct STATESTRUCT {
	char method[25];
	struct MHD_PostProcessor* processor;
	void* formdata;
	size_t formdatalen;
} * STATE;

#endif
