#include "badlist.h"

#include "debug.h"
#include <netinet/in.h>
#include <arpa/inet.h>

#ifndef TRUE
#define TRUE (1==1)
#endif
#ifndef FALSE
#define FALSE (0==1)
#endif

typedef struct BADITEMSTRUCT {
	unsigned short count;
	time_t last;
} * BADITEM;

BADLIST new_BADLIST()
{
	BADLIST list = (BADLIST)malloc(sizeof(Pvoid_t));
	*list = NULL;
	return list;
}

int bad_add(BADLIST list, const struct sockaddr* addr)
{
	char* addr_s = inet_ntoa(
			((const struct sockaddr_in*)addr)->sin_addr);
	Word_t* pval;
	BADITEM item;

	JSLG(pval, *list, addr_s);

	if (pval == NULL) {
		item = (BADITEM)malloc(sizeof(struct BADITEMSTRUCT));
		JSLI(pval, *list, addr_s);
		*pval = (Word_t)item;

		item->count = 1;
	} else {
		item = (BADITEM)*pval;
		if (item->last + BLACKLIST_WINDOW < time(NULL)) {
			item->count = 1;
		} else {
			item->count++;
		}
	}
	item->last = time(NULL);

	debug("address: %s consecutive bad attempts: %d", addr_s, item->count);
	return item->count;
}

void bad_rem(BADLIST list, const struct sockaddr* addr)
{
	char* addr_s = inet_ntoa(
			((const struct sockaddr_in*)addr)->sin_addr);
	int res = 0;

	JSLD(res, *list, addr_s);
	if (res != 0) {
		debug("address removed from bad list: %s", addr_s);
	}
}

int is_blacklisted(BADLIST list, const struct sockaddr* addr)
{
	char* addr_s = inet_ntoa(
			((const struct sockaddr_in*)addr)->sin_addr);
	Word_t* pval;

	JSLG(pval, *list, addr_s);

	if (pval == NULL) {
		return FALSE;
	} else {
		BADITEM item = (BADITEM)*pval;
		if (item->count < BLACKLIST_THRESHOLD) {
			return FALSE;
		} else if (item->last + BLACKLIST_DURATION >= time(NULL)) {
			debug(
					"connection attempt from blacklisted "
					"address: %s",
					addr_s);
			return TRUE;
		} else {
			debug("blacklisting expired from address: %s", addr_s);
			int res = 0;
			free(item);
			JSLD(res, *list, addr_s);
			return FALSE;
		}
	}
}

