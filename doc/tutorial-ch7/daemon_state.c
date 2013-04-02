#include "daemon_state.h"

#include <stdlib.h>

//TODO: add semaphore locks to allow multithreading

DAEMON_STATE new_DAEMON_STATE(
		const unsigned int max_clients,
		const unsigned int max_upload_clients,
		const unsigned int upload_client_multiplier)
{
	DAEMON_STATE dstate = (DAEMON_STATE)malloc(
			sizeof(struct DAEMON_STATE_STRUCT));
	if (dstate == NULL) {
		return NULL;
	}
	dstate->max_clients = max_clients;
	dstate->max_upload_clients= max_upload_clients;
	dstate->upload_client_multiplier = upload_client_multiplier;
	dstate->current_clients = 0;
	dstate->current_upload_clients = 0;

	return dstate;
}

void destroy_DAEMON_STATE(DAEMON_STATE dstate)
{
	free(dstate);
}

BOOL added_client_overloads(DAEMON_STATE dstate)
{
	dstate->current_clients++;
	return dstate->current_clients > dstate->max_clients;
}

BOOL added_upload_client_overloads(
		DAEMON_STATE dstate,
		BOOL client_already_counted)
{
	if (client_already_counted) {
		dstate->current_clients += dstate->upload_client_multiplier -1;
	} else {
		dstate->current_clients += dstate->upload_client_multiplier;
	}
	dstate->current_upload_clients++;
	return dstate->current_upload_clients > dstate->max_upload_clients
		|| dstate->current_clients > dstate->max_clients;
}

unsigned int get_current_upload_clients(DAEMON_STATE dstate)
{
	return dstate->current_upload_clients;
}

unsigned int get_current_clients(DAEMON_STATE dstate)
{
	return dstate->current_clients;
}

void client_load_dropping(DAEMON_STATE dstate)
{
	dstate->current_clients--;
}

void upload_client_load_dropping(DAEMON_STATE dstate)
{
	dstate->current_clients -= dstate->upload_client_multiplier;
	dstate->current_upload_clients--;
}

