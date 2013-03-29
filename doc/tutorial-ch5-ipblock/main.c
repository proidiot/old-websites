#include <microhttpd.h>
#include "answer.h"
#include "connect.h"
#include "badlist.h"
#include "debug.h"

int main()
{
	struct MHD_Daemon* daemon;
	BADLIST list = new_BADLIST();
	daemon = MHD_start_daemon(
		MHD_USE_SELECT_INTERNALLY,
		8080,
		&on_client_connect,
		list,
		&answer_to_connection,
		list,
		MHD_OPTION_END);
	if (daemon == NULL) {
		return 1;
	}

	getchar();

	free(list);
	MHD_stop_daemon(daemon);
	return 0;
}

