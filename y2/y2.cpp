#include "y2.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int CxxReader2::fd_opened = 1;
static const char *fixedBuf = "CxxReader2";

CxxReader2::CxxReader2() {
	buf = (char *) fixedBuf;
}

CxxReader2::CxxReader2(int v) {
	const int N = 128;
	buf = malloc(N);
	snprintf((char *)buf, N, "CxxReader2-%d", v);
}

CxxReader2::CxxReader2(const char *v) {
	const int N = 256;
	buf = malloc(N);
	snprintf((char *)buf, N, "CxxReader2-%s", v);
}

CxxReader2::~CxxReader2()
{
	if(buf != NULL && buf != fixedBuf)
		free(buf);
}

int CxxReader2::open2(const char *filename) {
	return ++fd_opened;
}

int CxxReader2::close2(int fd) {
	if(fd < fd_opened) return -1;
	if(fd_opened > 2) --fd_opened;
	return 0;
}

int CxxReader2::read2(int fd, void *buf, int buflen) {
	if(fd < fd_opened) return -1;
	strncpy((char *)buf, (char *)this->buf, buflen);
	return strlen((char *)buf);
}
