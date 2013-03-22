#include <microhttpd.h>
#include "answer.h"
#include "onconnect.h"

int main()
{
	struct MHD_Daemon* daemon;
	daemon = MHD_start_daemon(
		MHD_USE_SELECT_INTERNALLY,
		8080,
		&on_client_connect,
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

