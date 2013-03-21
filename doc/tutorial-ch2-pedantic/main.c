#include <microhttpd.h>
#include "example.h"

int main()
{
	struct MHD_Daemon* daemon;
	daemon = MHD_start_daemon(
		MHD_USE_SELECT_INTERNALLY | MHD_USE_PEDANTIC_CHECKS,
		8080,
		NULL,
		NULL,
		&answer_to_connection,
		NULL,
		MHD_OPTION_END);
	if (daemon == NULL) {
		return 1;
	}

	getchar();

	MHD_stop_daemon(daemon);
	return 0;
}

