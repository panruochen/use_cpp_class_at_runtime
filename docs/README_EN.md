Use C++ classes at run-time
===========================

***The repo*** shows a trick to use C++ class member functions by run-time dynamic linking as if these member functions are explicitly called by load-time dynamic linking.<br>


BUILD AND RUN
=============
```
# lauch vs2015 x86|x64 Native Tool command prompt
python3 test.py
```

You should have python3, cmake, g++ (5.4 or higher), clang or msvc2015 (or higher) installed.


DESCRIPTIONS
==================================
The compiler generates mangled functions names for C++ member functions. For example
```
class Foo {
	int foo1();
};
```
The mangled name for Foo::foo1 is _ZN3Foo4foo1Ev. To call Foo::foo1 at run-time, we usually declare a function pointer and assign it by calling dlsym
```
void *handle = dlopen("libfoo.so", RTLD_NOW);
int (Foo:: *ptr_to_foo1)(void) = dlsym(handle, "_ZN3Foo4foo1Ev");
// call Foo::foo1
(fooObject->*ptr_to_foo1)();
```
It works but the code looks weird. Fortunately we can improve it by implementing a Foo class of replacement, routing function calls to the real Foo class through function pointers:
```
void *handle = dlopen("libfoo.so", RTLD_NOW);
int (Foo:: *ptr_to_foo1)(void) = dlsym(handle, "_ZN3Foo4foo1Ev");

class Foo { // The Foo class of myself, must have the same name.
	int foo1() { return (this->*ptr_to_foo1)(); }
};
```
Now in our main code, we can simply use
```
fooObject->foo1();
```

Every member function (including constructors and destructors) that is not inlined should have a function pointer.<br>
Use any data to initialize constant members in the constructors to satisfy the compiler. These constant data members will be correctly initialized again while the real constructor is called. For example:
```
// The real Foo class
class Foo {
	const int m;
public:
	Foo(int v);
};

void (Foo:: *foo_contructor1)(void) = dlsym(handle, "_ZN3FooC1Ei");
// My stub Foo class
class Foo {
	const int m;
public:
	Foo(int v) : m(0) { (this->*foo_contructor1)(); }
};

```

Use undname or c++filt tool to demangle function names.

About Me
========
Pan Ruochen <ijkxyz@msn.com>
