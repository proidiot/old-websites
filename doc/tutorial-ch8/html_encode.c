#include "html_encode.h"

#include "common_macros.h"
#include <stdio.h>
#include <string.h>

char* html_encode(const char* string, const size_t length)
{
	size_t reallen = strnlen(string, length);
	unsigned int i = 0;
	char* encoded = (char*)malloc((reallen * HTML_ENCODE_MULTIPLIER) + 1);
	if (encoded == NULL) {
		return NULL;
	}
	char* tencoded = encoded;

	char* temp = (char*)malloc(HTML_ENCODE_MULTIPLIER + 1);
	if (temp == NULL) {
		free(encoded);
		return NULL;
	}

	for (i = 0; i < reallen; i++) {
		snprintf(
				temp,
				HTML_ENCODE_MULTIPLIER + 1,
				isalnum(string[i]) ? "%1c" : "&#x%2X;",
				string[i]);
		tencoded = stpcpy(tencoded, temp);
	}

	free(temp);

	SHRINKSAFESTR(encoded);

	return encoded;
}

