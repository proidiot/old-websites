#include "request_cleanup.h"

#include "state.h"
#include <stdlib.h>

void request_cleanup(
		void* cls,
		struct MHD_Connection* connection,
		void** con_cls,
		enum MHD_RequestTerminationCode rtc)
{
	STATE state = *con_cls;
	if (state != NULL) {
		if (strncmp(state->method, MHD_HTTP_METHOD_POST, 25) == 0) {
			MHD_destroy_post_processor(state->processor);
			if (state->formdatalen > 0) {
				free(state->formdata);
			}
		}
		free(state);
		*con_cls = NULL;
	}
}


