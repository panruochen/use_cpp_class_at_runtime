#include "y2.h"
#include "dynload.hpp"

static DynBinder __dynBinder;
DynBinder *const dynBinder = &__dynBinder;

CxxReader2::CxxReader2() {
	(this->*dynBinder->CxxReader2_constructor1)();
}

CxxReader2::CxxReader2(int v) {
	(this->*dynBinder->CxxReader2_constructor2)(v);
}

CxxReader2::CxxReader2(const char *v) {
	(this->*dynBinder->CxxReader2_constructor3)(v);
}

CxxReader2::~CxxReader2() {
	(this->*dynBinder->CxxReader2_destructor)();
}

int CxxReader2::open2(const char *filename) {
	return (this->*dynBinder->open2)(filename);
}

int CxxReader2::close2(int fd) {
	return (this->*dynBinder->close2)(fd);
}

int CxxReader2::read2(int fd, void *buf, int bufLen) {
	return (this->*dynBinder->read2)(fd, buf, bufLen);
}

int DynBinder::init()
{
#define _MAKE_ENTRY(x) \
	{ (void **) &x, #x }

	InitEntry initTabA[] = {
		_MAKE_ENTRY(open1),
		_MAKE_ENTRY(read1),
		_MAKE_ENTRY(close1),
		{NULL, NULL},
	};

	InitEntry initTabB[] = {
#if WIN32
		{ (void **)&CxxReader2_constructor1, "??0CxxReader2@@QAE@XZ"},
		{ (void **)&CxxReader2_constructor2, "??0CxxReader2@@QAE@H@Z"},
		{ (void **)&CxxReader2_constructor3, "??0CxxReader2@@QAE@PBD@Z"},
		{ (void **)&CxxReader2_destructor, "??1CxxReader2@@QAE@XZ"},
		{ (void **)&open2, "?open2@CxxReader2@@QAEHPBD@Z"},
		{ (void **)&read2, "?read2@CxxReader2@@QAEHHPAXH@Z"},
		{ (void **)&close2, "?close2@CxxReader2@@QAEHH@Z"},
#else
		{ (void **)&CxxReader2_constructor1, "_ZN10CxxReader2C1Ev"},
		{ (void **)&CxxReader2_constructor2, "_ZN10CxxReader2C1Ei"},
		{ (void **)&CxxReader2_constructor3, "_ZN10CxxReader2C1EPKc"},
		{ (void **)&CxxReader2_destructor, "_ZN10CxxReader2D1Ev"},
		{ (void **)&open2, "_ZN10CxxReader25open2EPKc"},
		{ (void **)&read2, "_ZN10CxxReader25read2EiPvi"},
		{ (void **)&close2, "_ZN10CxxReader26close2Ei"},
#endif
		{NULL, NULL},
	};

#undef _MAKE_ENTRY

	void *initTable[][2] = {
#if WIN32
		{ (void *)initTabA, (void *)"y1.dll" },
		{ (void *)initTabB, (void *)"y2.dll" },
#else
		{ (void *)initTabA, (void *)"liby1.so" },
		{ (void *)initTabB, (void *)"liby2.so" },
#endif
		{ NULL, NULL },
	};

	for(unsigned int m = 0; ; m++) {
		InitEntry *const initTab = (InitEntry *) initTable[m][0];
		const char *const modName = (const char *) initTable[m][1];
		void *module;

		if(modName == NULL || initTab == NULL)
			break;

		module = dlopen(modName, RTLD_NOW);
		if(module == NULL) {
			fprintf(stderr, "Can not load library \"%s\": %s\n", modName, getLastError().c_str());
			return -1;
		}

		for(unsigned int i = 0; ; i++) {
			void **ptr = (void **) initTab[i].fptr;
			const char *synName = (const char *) initTab[i].synName;

			if (ptr == NULL || synName == NULL)
				break;

			*ptr = (void *) dlsym(module, synName);
			if(*ptr == NULL) {
				fprintf(stderr, "Can not resolve symbol \"%s\"\n", synName);
				return -1;
			}
		}
	}

	return 0;
}

