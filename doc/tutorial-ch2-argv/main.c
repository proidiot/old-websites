#include <microhttpd.h>
#include "example.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
	if (argc != 2) {
		fprintf(stderr, "USAGE: %s STRING\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	struct MHD_Daemon* daemon;
	daemon = MHD_start_daemon(
		MHD_USE_SELECT_INTERNALLY,
		8080,
		NULL,
		NULL,
		&answer_to_connection,
		argv[1],
		MHD_OPTION_END);
	if (daemon == NULL) {
		return 1;
	}

	getchar();

	MHD_stop_daemon(daemon);
	return 0;
}

