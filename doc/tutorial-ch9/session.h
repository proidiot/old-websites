#ifndef WEBSITES_SESSION_H
#define WEBSITES_SESSION_H

#include "common_macros.h"
#include <time.h>

#define SESSION_LIFE (30 * 60)

typedef struct SESSION_STRUCT {
	char* name;
	BOOL name_set;
	char* job;
	BOOL job_set;
	time_t last_accessed;
	time_t next_last_accessed;
} * SESSION;

SESSION new_SESSION();

void destroy_SESSION(SESSION s);

SESSION copy_SESSION(SESSION s);

#endif
