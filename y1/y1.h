#ifndef __SO_Y1_H
#define __SO_Y1_H

#if Y1_SO_EXPORTS
#	if _MSC_VER
#		define Y1_EXPORT __declspec(dllexport)
#	else
#		define Y1_EXPORT __attribute__((visibility("default")))
#	endif
#else
#	if _MSC_VER
#		define Y1_EXPORT __declspec(dllimport)
#	else
#		define Y1_EXPORT
#	endif
#endif

#ifndef EXTERN_C
#	if __cplusplus
#		define EXTERN_C extern "C"
#	else
#		define EXTERN_C
#	endif
#endif

EXTERN_C Y1_EXPORT int open1(const char *filename);
EXTERN_C Y1_EXPORT int close1(int fd);
EXTERN_C Y1_EXPORT int read1(int fd, void *buf, int buflen);

#endif

