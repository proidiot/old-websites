#include "debug.h"

#include <stdio.h>
#include <stdarg.h>

void _print_debug_line(const char* file, const int line, const char* fmt, ...)
{
	char temp[BUFSIZ];
	va_list ap;
	va_start(ap, fmt);
	vsprintf(temp, fmt, ap);
	fprintf(
			stderr,
			"DEBUG: %X: %s:%d: %s\n",
			time(NULL),
			file,
			line,
			temp);
}

int _debug_int_ret(
		const char* file,
		const int line,
		int ret,
		const char* fmt,
		...)
{
	char temp[BUFSIZ];
	va_list ap;
	va_start(ap, fmt);
	vsprintf(temp, fmt, ap);
	fprintf(
			stderr,
			"DEBUG: %X: %s:%d: %s\n",
			time(NULL),
			file,
			line,
			temp);
	return ret;
}

