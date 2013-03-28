#include "connect.h"

#include "badlist.h"
#include <stdio.h>
#include <microhttpd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int on_client_connect(
		void* cls,
		const struct sockaddr* addr,
		socklen_t addrlen)
{
	return is_blacklisted((BADLIST)cls, addr) ? MHD_NO : MHD_YES;
}

