#include <microhttpd.h>
#include "answer.h"
#include "request_cleanup.h"
#include "daemon_state.h"

#define MAX_CLIENTS 50
#define MAX_UPLOAD_CLIENTS 2
#define UPLOAD_MULTIPLIER 24

int main()
{
	struct MHD_Daemon* daemon;
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
		return 1;
	}

	getchar();

	MHD_stop_daemon(daemon);
	destroy_DAEMON_STATE(dstate);
	return 0;
}

