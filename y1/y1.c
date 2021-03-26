#include "y1.h"
#include <string.h>

int open1(const char *filename) {
	return 1;
}

int close1(int fd) {
	if(fd != 1) return -1;
	return 0;
}

int read1(int fd, void *buf, int buflen) {
	if(fd != 1) return -1;
	strncpy(buf, "--y1--", buflen);
	return strlen(buf);
}


