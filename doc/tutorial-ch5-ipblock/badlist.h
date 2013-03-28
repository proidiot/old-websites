#ifndef WEBSITE_BADLIST_H
#define WEBSITE_BADLIST_H

#include <Judy.h>
#include <sys/socket.h>

#define BLACKLIST_THRESHOLD 4
#define BLACKLIST_WINDOW 30
#define BLACKLIST_DURATION 300

typedef Pvoid_t BADLIST;

BADLIST new_BADLIST();

int bad_add(BADLIST list, const struct sockaddr* addr);

int is_blacklisted(BADLIST list, const struct sockaddr* addr);

#endif
