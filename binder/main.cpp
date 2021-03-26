#include <stdio.h>
#include "y1.h"
#include "y2.h"
#include "dynload.hpp"

int main()
{
#if _SO_RUNTIME_BINDING
	if(dynBinder->init() != 0) {
		fprintf(stderr, "Binder initialization failed\n");
		exit(1);
	}
#endif

	int n;
	int fd1, fd2;
	CxxReader2 fr2_a, fr2_b(7), fr2_c("Z");
	char buf[128];

	fd1 = open1("FD1");
	fd2 = fr2_a.open2("FD2");
	printf("FD1 = %d, FD2 = %d\n", fd1, fd2);

	n = read1(fd1, buf, sizeof(buf));
	printf("read1 : %s : %d\n", buf, n);

	n = fr2_a.read2(fd2, buf, sizeof(buf));
	printf("read2 : %s : %d\n", buf, n);

	n = fr2_b.read2(fd2, buf, sizeof(buf));
	printf("read2 : %s : %d\n", buf, n);

	n = fr2_c.read2(fd2, buf, sizeof(buf));
	printf("read2 : %s : %d\n", buf, n);

	n = close1(fd1);
	printf("close1() = %d\n", n);

	n = fr2_a.close2(fd2);
	printf("close2() = %d\n", n);

	n = fr2_b.close2(fd2);
	printf("close2() = %d\n", n);

	n = fr2_c.close2(fd2);
	printf("close2() = %d\n", n);

	return 0;
}
