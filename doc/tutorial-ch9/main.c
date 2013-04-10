#include <microhttpd.h>
#include "answer.h"
#include "request_cleanup.h"
#include "daemon_state.h"
#include "debug.h"
#include "load_file.h"
#include <string.h>
#include <signal.h>
#include <stdlib.h>

#define MAX_CLIENTS 50
#define MAX_UPLOAD_CLIENTS 50
#define UPLOAD_MULTIPLIER 3
#define FRESHEN_SESSIONS_FREQUENCY 30
#define SSL_KEY_FILE "ssl_key.pem"
#define SSL_CERT_FILE "ssl_cert.pem"

BOOL killed;

void catch(int signal)
{
	debug("Caught signal %d: %s", signal, strsignal(signal));
	if (signal != SIGALRM) {
		killed = TRUE;
	}
}

int main()
{
	sigset_t empty_sigset;
	struct MHD_Daemon* daemon;
	char* ssl_key;
	char* ssl_cert;
	size_t file_len = 0;

	killed = FALSE;
	signal(SIGHUP, SIG_IGN);
	signal(SIGINT, &catch);
	signal(SIGTERM, &catch);
	signal(SIGALRM, &catch);
	sigemptyset(&empty_sigset);

	ssl_key = load_file(&file_len, SSL_KEY_FILE);
	if (file_len == 0 || ssl_key == NULL || SMATCH(ssl_key, "")) {
		debug("Unable to load key file");
		return EXIT_FAILURE;
	}

	ssl_cert = load_file(&file_len, SSL_CERT_FILE);
	if (file_len == 0 || ssl_cert == NULL || SMATCH(ssl_cert, "")) {
		debug("Unable to load cert file");
		free(ssl_key);
		return EXIT_FAILURE;
	}

	debug("Starting daemon...");
	DAEMON_STATE dstate = new_DAEMON_STATE(
			MAX_CLIENTS,
			MAX_UPLOAD_CLIENTS,
			UPLOAD_MULTIPLIER);
	daemon = MHD_start_daemon(
#ifdef DEBUG
		MHD_USE_DEBUG |
#endif
		MHD_USE_SSL |
		MHD_USE_SELECT_INTERNALLY,
		8080,
		NULL,
		NULL,
		&answer_to_connection,
		(void*)dstate,
		MHD_OPTION_NOTIFY_COMPLETED,
		&request_cleanup,
		(void*)dstate,
		MHD_OPTION_HTTPS_MEM_KEY,
		ssl_key,
		MHD_OPTION_HTTPS_MEM_CERT,
		ssl_cert,
		MHD_OPTION_END);

	if (daemon == NULL) {
		debug("Unable to start daemon.");
		destroy_DAEMON_STATE(dstate);
		free(ssl_cert);
		free(ssl_key);
		return EXIT_FAILURE;
	} else {
		debug("Daemon has been started.");

		alarm(FRESHEN_SESSIONS_FREQUENCY);
		while (sigsuspend(&empty_sigset) && !killed) {
			freshen_sessions(dstate);
			alarm(FRESHEN_SESSIONS_FREQUENCY);
		}
	
		debug("Stopping daemon...");
		MHD_stop_daemon(daemon);
		destroy_DAEMON_STATE(dstate);
		free(ssl_cert);
		free(ssl_key);

		debug("Daemon has been stopped.");
		return EXIT_SUCCESS;
	}
}

