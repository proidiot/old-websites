#include "session.h"

#include <stdlib.h>
#include <string.h>

SESSION new_SESSION()
{
	SESSION s = (SESSION)malloc(sizeof(struct SESSION_STRUCT));
	if (s == NULL) {
		return NULL;
	}

	s->name = NULL;
	s->name_set = FALSE;

	s->job = NULL;
	s->job_set = FALSE;

	s->next_last_accessed = time(NULL);
	s->last_accessed = time(NULL);

	return s;
}

void destroy_SESSION(SESSION s)
{
	if (s != NULL) {
		if (s->name != NULL) {
			free(s->name);
		}
		if (s->job != NULL) {
			free(s->job);
		}
		free(s);
	}
}

SESSION copy_SESSION(SESSION s)
{
	SESSION copy = new_SESSION();
	if (copy == NULL) {
		return NULL;
	}
	
	if (s->name_set) {
		copy->name = (char*)malloc(strlen(s->name) + 1);
		if (copy->name == NULL) {
			free(copy);
			return NULL;
		}
		strcpy(copy->name, s->name);
		copy->name_set = TRUE;
	} else {
		copy->name_set = FALSE;
	}

	if (s->job_set) {
		copy->job = (char*)malloc(strlen(s->job) + 1);
		if (copy->job == NULL) {
			if (copy->name != NULL) {
				free(copy->name);
			}
			free(copy);
			return NULL;
		}
		strcpy(copy->job, s->job);
		copy->job_set = TRUE;
	} else {
		copy->job_set = FALSE;
	}

	copy->next_last_accessed = s->next_last_accessed;
	copy->last_accessed = s->last_accessed;

	return copy;
}

