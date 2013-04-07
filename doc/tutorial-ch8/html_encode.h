#ifndef WEBSITES_HTML_ENCODE_H
#define WEBSITES_HTML_ENCODE_H

#include <stdlib.h>

#define HTML_ENCODE_MULTIPLIER 6

char* html_encode(const char* string, const size_t length);

#endif
