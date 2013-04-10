#ifndef WEBSITES_DAEMON_STATE_H
#define WEBSITES_DAEMON_STATE_H

#include "common_macros.h"
#include "session.h"
#include <Judy.h>

typedef struct DAEMON_STATE_STRUCT {
	unsigned int max_upload_clients;
	unsigned int current_upload_clients;
	unsigned int upload_client_multiplier;
	unsigned int max_clients;
	unsigned int current_clients;
	Pvoid_t sessions;
} * DAEMON_STATE;

DAEMON_STATE new_DAEMON_STATE(
		const unsigned int max_clients,
		const unsigned int max_upload_clients,
		const unsigned int upload_client_multiplier);

void destroy_DAEMON_STATE(DAEMON_STATE dstate);

BOOL added_client_overloads(DAEMON_STATE dstate);

BOOL added_upload_client_overloads(
		DAEMON_STATE dstate,
		BOOL client_already_counted);

unsigned int get_current_upload_clients(DAEMON_STATE dstate);

unsigned int get_current_clients(DAEMON_STATE dstate);

void client_load_dropping(DAEMON_STATE dstate);

void upload_client_load_dropping(DAEMON_STATE dstate);

SESSION get_session(DAEMON_STATE dstate, const char* cookie);

void save_session(DAEMON_STATE dstate, const char* cookie, SESSION session);

void freshen_sessions(DAEMON_STATE dstate);

#endif
