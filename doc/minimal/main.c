#include <microhttpd.h>
#include "answer.h"
#include "common_macros.h"
#include "debug.h"
#include <string.h>
#include <signal.h>
#include <stdlib.h>

#define SERVER_PORT 80

void catch(int signal)
{
	// signal catching has to happen in a function, so here's a function
	debug("Caught signal %d: %s", signal, strsignal(signal));
}

int main()
{
	struct MHD_Daemon* daemon;
	sigset_t empty_sigset;

	// signal catching stuff
	signal(SIGHUP, SIG_IGN);
	signal(SIGINT, &catch);
	signal(SIGTERM, &catch);
	sigemptyset(&empty_sigset);

	debug("Starting daemon...");
	// microhttpd stuff
	daemon = MHD_start_daemon(
#ifdef DEBUG
		MHD_USE_DEBUG |
#endif
		MHD_USE_SELECT_INTERNALLY,
		SERVER_PORT,
		NULL,
		NULL,
		&answer_to_connection,
		NULL,
		MHD_OPTION_END);

	if (daemon == NULL) {
		// microhttpd exploded
		perror("Unable to start daemon.");
		return EXIT_FAILURE;
	} else {
		debug("Daemon has been started.");

		// signal-aware sleep
		sigsuspend(&empty_sigset);
	
		debug("Stopping daemon...");
		// microhttpd stuff
		MHD_stop_daemon(daemon);

		debug("Daemon has been stopped.");
		return EXIT_SUCCESS;
	}
}

