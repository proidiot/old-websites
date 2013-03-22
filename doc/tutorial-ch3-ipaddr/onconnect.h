#ifndef WEBSITES_ONCONNECT_H
#define WEBSITES_ONCONNECT_H

#include <sys/socket.h>

int on_client_connect(
		void* cls,
		const struct sockaddr* addr,
		socklen_t addrlen);

#endif

