#include"load_file.h"

#include "debug.h"
#include <stdio.h>

unsigned char* load_file(size_t* load_len, const char* filename)
{
	if (strnlen(filename, BUFSIZ) == BUFSIZ) {
		debug("Unable to open file: name is too long");
		*load_len = 0;
		return "";
	}

	long size = 0;
	FILE* fd = fopen(filename, "rb");
	if (fd == NULL) {
		debug("Unable to open file");
		*load_len = 0;
		return "";
	}
	if ((0 != fseek(fd, 0, SEEK_END)) || (-1 == (size = ftell(fd)))) {
		debug("Unable to find EOF in file: %s", filename);
		fclose(fd);
		*load_len = 0;
		return "";
	} else {
		fclose(fd);
	}

	if (size == 0) {
		debug("Empty file: %s", filename);
		*load_len = 0;
		return "";
	}

	unsigned char* buffer = (unsigned char*)malloc(size);
	if (buffer == NULL) {
		debug("Unable to malloc buffer");
		*load_len = 0;
		return "";
	}

	fd = fopen(filename, "rb");
	if (fd == NULL) {
		debug("Unable to open file again (very odd): %s", filename);
		free(buffer);
		*load_len = 0;
		return "";
	}

	if (size != fread(buffer, 1, size, fd)) {
		debug("Unable to read all bytes from file: %s", filename);
		free(buffer);
		fclose(fd);
		*load_len = 0;
		return "";
	} else {
		fclose(fd);
		*load_len = size;
		return buffer;
	}
}

