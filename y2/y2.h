#ifndef __SO_Y2_H
#define __SO_Y2_H

#if _SO_RUNTIME_BINDING
#	define Y2_EXPORT
#elif Y2_SO_EXPORTS
#	if _MSC_VER
#		define Y2_EXPORT __declspec(dllexport)
#	else
#		define Y2_EXPORT __attribute__((visibility("default")))
#	endif
#else
#	if _MSC_VER
#		define Y2_EXPORT __declspec(dllimport)
#	else
#		define Y2_EXPORT
#	endif
#endif

class Y2_EXPORT CxxReader2 {
	static int fd_opened;
	int fd;
	void *buf;
public:
	CxxReader2();
	CxxReader2(int);
	CxxReader2(const char *);
	~CxxReader2();
	int open2(const char *filename);
	int close2(int fd);
	int read2(int fd, void *buf, int bufLen);
};

#endif

