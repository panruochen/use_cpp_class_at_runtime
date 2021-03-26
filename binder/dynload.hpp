#if _SO_RUNTIME_BINDING

#include <string>
#include <string.h>

#if WIN32
#	include <windows.h>

#	define RTLD_NOW 0

static inline void *dlopen(const char *filename, int flags) {
	return LoadLibraryA(filename);
}

static inline void *dlsym(void *handle, const char *symbol) {
	return GetProcAddress((HMODULE)handle, symbol);
}

static inline std::string getLastError()
{
	std::string errString;
	LPVOID lpMsgBuf;
	DWORD dw = GetLastError();

	FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, dw, MAKELANGID(LANG_ENGLISH, SUBLANG_DEFAULT), (LPTSTR) &lpMsgBuf,
		0, NULL);

	errString = (char *) lpMsgBuf;
	LocalFree(lpMsgBuf);
	return errString;
}

#elif LINUX
#	include <dlfcn.h>

static inline std::string getLastError()
{
	std::string errString;
	errString = strerror(errno);
	return errString;
}

#endif

extern "C" struct InitEntry {
	void **fptr;
	const char *synName;
};

class CxxReader2;

struct DynBinder {
	int (*open1)(const char *fileName);
	int (*close1)(int fd);
	int (*read1)(int fd, void *buf, int bufLen);

	void (CxxReader2::*CxxReader2_constructor1)();
	void (CxxReader2::*CxxReader2_constructor2)(int);
	void (CxxReader2::*CxxReader2_constructor3)(const char *);
	void (CxxReader2::*CxxReader2_destructor)();

	int (CxxReader2::*open2)(const char *);
	int (CxxReader2::*close2)(int fd);
	int (CxxReader2::*read2)(int fd, void *buf, int bufLen);

	int init();
	inline DynBinder() {
		memset(this, 0, sizeof(*this));
	}
};

extern DynBinder *const dynBinder;

#define open1  dynBinder->open1
#define close1 dynBinder->close1
#define read1  dynBinder->read1

#endif
