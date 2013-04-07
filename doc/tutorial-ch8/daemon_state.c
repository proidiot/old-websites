#include "daemon_state.h"

#include <stdlib.h>
#include <string.h>

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

	dstate->sessions = NULL;

	return dstate;
}

void destroy_DAEMON_STATE(DAEMON_STATE dstate)
{
	if (dstate->sessions != NULL) {
		uint8_t index[BUFSIZ];
		Word_t* pval;
		strcpy(index, "");
		JSLF(pval, dstate->sessions, index);
		while (pval != NULL) {
			int temp;
			destroy_SESSION((SESSION)*pval);
			JSLD(temp, dstate->sessions, index);
			JSLN(pval, dstate->sessions, index);
		}
	}
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

SESSION get_session(DAEMON_STATE dstate, const char* cookie)
{
	if (cookie == NULL || strnlen(cookie, BUFSIZ) == 0) {
		return NULL;
	}
	Word_t* pval;
	JSLG(pval, dstate->sessions, cookie);
	if (pval == NULL) {
		return new_SESSION();
	} else {
		return copy_SESSION((SESSION)*pval);
	}
}

void save_session(DAEMON_STATE dstate, const char* cookie, SESSION session)
{
	if (cookie == NULL
			|| strnlen(cookie, BUFSIZ) == 0
			|| session == NULL) {
		return;
	}

	SESSION new_session;
	SESSION old_session;

	Word_t* pval;
	JSLG(pval, dstate->sessions, cookie);

	if (pval != NULL) {
		new_session = new_SESSION();
		old_session = (SESSION)*pval;

		if (session->name_set
				&& (old_session->last_accessed
						<= session->last_accessed
					|| old_session->next_last_accessed
						< session->next_last_accessed
					|| !old_session->name_set
					|| 0 == strcmp(
						old_session->name,
						session->name))) {
			new_session->name = (char*)malloc(
					strlen(session->name) + 1);
			strcpy(new_session->name, session->name);
			new_session->name_set = TRUE;
		} else if (old_session->name_set) {
			new_session->name = (char*)malloc(
					strlen(old_session->name) + 1);
			strcpy(new_session->name, old_session->name);
			new_session->name_set = TRUE;
		} else {
			new_session->name_set = FALSE;
		}

		if (session->job_set
				&& (old_session->last_accessed
						<= session->last_accessed
					|| old_session->next_last_accessed
						< session->next_last_accessed
					|| !old_session->job_set
					|| 0 == strcmp(
						old_session->job,
						session->job))) {
			new_session->job = (char*)malloc(
					strlen(session->job) + 1);
			strcpy(new_session->job, session->job);
			new_session->job_set = TRUE;
		} else if (old_session->job_set) {
			new_session->job = (char*)malloc(
					strlen(old_session->job) + 1);
			strcpy(new_session->job, old_session->job);
			new_session->job_set = TRUE;
		} else {
			new_session->job_set = FALSE;
		}

		new_session->next_last_accessed = MAX(
				old_session->last_accessed,
				session->last_accessed);
		new_session->last_accessed = time(NULL);
	} else {
		old_session = NULL;
		new_session = copy_SESSION(session);
	}

	JSLI(pval, dstate->sessions, cookie);

	*pval = (Word_t)new_session;

	if (old_session != NULL) {
		destroy_SESSION(old_session);
	}
}

void freshen_sessions(DAEMON_STATE dstate)
{
	uint8_t index[BUFSIZ];
	Word_t* pval;
	strcpy(index, "");
	JSLF(pval, dstate->sessions, index);
	while (pval != NULL) {
		SESSION session = (SESSION)*pval;
		int temp;
		if (session == NULL) {
			JSLD(temp, dstate->sessions, index);
		} else if (session->last_accessed + SESSION_LIFE < time(NULL)) {
			destroy_SESSION(session);
			JSLD(temp, dstate->sessions, index);
		}
		JSLN(pval, dstate->sessions, index);
	}
}

