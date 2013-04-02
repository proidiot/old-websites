#include <microhttpd.h>
#include "answer.h"
#include "request_cleanup.h"
#include "daemon_state.h"
#include "debug.h"
#include <string.h>
#include <signal.h>
#include <stdlib.h>

#define MAX_CLIENTS 50
#define MAX_UPLOAD_CLIENTS 2
#define UPLOAD_MULTIPLIER 24

void catch(int signal)
{
	debug("Caught signal %d: %s", signal, strsignal(signal));
}

int main()
{
	sigset_t empty_sigset;
	struct MHD_Daemon* daemon;

	signal(SIGHUP, SIG_IGN);
	signal(SIGINT, &catch);
	signal(SIGTERM, &catch);
	sigemptyset(&empty_sigset);

	debug("Starting daemon...");
	DAEMON_STATE dstate = new_DAEMON_STATE(
			MAX_CLIENTS,
			MAX_UPLOAD_CLIENTS,
			UPLOAD_MULTIPLIER);
	daemon = MHD_start_daemon(
		MHD_USE_SELECT_INTERNALLY,
		8080,
		NULL,
		NULL,
		&answer_to_connection,
		(void*)dstate,
		MHD_OPTION_NOTIFY_COMPLETED,
		&request_cleanup,
		(void*)dstate,
		MHD_OPTION_END);

	if (daemon == NULL) {
		debug("Unable to start daemon.");
		destroy_DAEMON_STATE(dstate);
		return EXIT_FAILURE;
	} else {
		debug("Daemon has been started.");

		sigsuspend(&empty_sigset);
	
		debug("Stopping daemon...");
		MHD_stop_daemon(daemon);
		destroy_DAEMON_STATE(dstate);

		debug("Daemon has been stopped.");
		return EXIT_SUCCESS;
	}
}

