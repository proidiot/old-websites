#include <microhttpd.h>
#include "answer.h"

int main()
{
	struct MHD_Daemon* daemon;
	time_t start = time(NULL);
	daemon = MHD_start_daemon(
		MHD_USE_SELECT_INTERNALLY,
		8080,
		NULL,
		NULL,
		&answer_to_connection,
		&start,
		MHD_OPTION_END);
	if (daemon == NULL) {
		return 1;
	}

	getchar();

	MHD_stop_daemon(daemon);
	return 0;
}

