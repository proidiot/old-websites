#include "onconnect.h"

#include <stdio.h>
#include <microhttpd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int on_client_connect(
		void* cls,
		const struct sockaddr* addr,
		socklen_t addrlen)
{
	printf(
			"Received connection from %s\n",
			inet_ntoa((((struct sockaddr_in*)addr)->sin_addr)));
	return MHD_YES;
}

