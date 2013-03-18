#ifndef __BLIB_PLATFORM_CONFIG_INCLUDED__
#define __BLIB_PLATFORM_CONFIG_INCLUDED__

#if defined(__BLIB_OSTYPE__)
#undef __BLIB_OSTYPE__
#endif
#if defined(_AIX)
#undef __BLIB_AIX__
#define __BLIB_AIX__		1
#define __BLIB_OSTYPE__ 'AIX'
#endif
#if defined(__BEOS__)
#undef __BLIB_BEOS__
#define __BLIB_BEOS__	1
#define __BLIB_OSTYPE__ 'BEOS'
#endif
#if defined(__HAIKU__)
#undef __BLIB_HAIKU__
#define __BLIB_HAIKU__ 1
#define __BLIB_OSTYPE__ 'HAIK'
#endif
#if defined(bsdi) || defined(__bsdi) || defined(__bsdi__)
#undef __BLIB_BSDI__
#define __BLIB_BSDI__	1
#define __BLIB_OSTYPE__ 'BSDI'
#endif
#if defined(_arch_dreamcast)
#undef __BLIB_DREAMCAST__
#define __BLIB_DREAMCAST__	1
#define __BLIB_OSTYPE__ 'DRMC'
#endif
#if defined(__FreeBSD__) || defined(__FreeBSD_kernel__) || defined(__DragonFly__)
#undef __BLIB_FREEBSD__
#define __BLIB_FREEBSD__	1
#define __BLIB_OSTYPE__ 'FBSD'
#endif
#if defined(hpux) || defined(__hpux) || defined(__hpux__)
#undef __BLIB_HPUX__
#define __BLIB_HPUX__	1
#define __BLIB_OSTYPE__ 'HPUX'
#endif
#if defined(sgi) || defined(__sgi) || defined(__sgi__) || defined(_SGI_SOURCE)
#undef __BLIB_IRIX__
#define __BLIB_IRIX__	1
#define __BLIB_OSTYPE__ 'SGI'
#endif
#if defined(linux) || defined(__linux) || defined(__linux__)
#undef __BLIB_LINUX__
#define __BLIB_LINUX__	1
#define __BLIB_OSTYPE__ 'LNUX'
#endif
#if defined(__APPLE__)
#undef __BLIB_MACOSX__
#define __BLIB_MACOSX__	1
#define __BLIB_OSTYPE__ 'APPL'
#elif defined(macintosh)
#undef __BLIB_MACOS__
#define __BLIB_MACOS__	1
#define __BLIB_OSTYPE__ 'MAC'
#endif
#if defined(__NetBSD__)
#undef __BLIB_NETBSD__
#define __BLIB_NETBSD__	1
#define __BLIB_OSTYPE__ 'NBSD'
#endif
#if defined(__OpenBSD__)
#undef __BLIB_OPENBSD__
#define __BLIB_OPENBSD__	1
#define __BLIB_OSTYPE__ 'OBSD'
#endif
#if defined(__OS2__)
#undef __BLIB_OS2__
#define __BLIB_OS2__		1
#define __BLIB_OSTYPE__ 'OS2'
#endif
#if defined(osf) || defined(__osf) || defined(__osf__) || defined(_OSF_SOURCE)
#undef __BLIB_OSF__
#define __OSF__		1
#define __BLIB_OSTYPE__ 'OSF'
#endif
#if defined(__QNXNTO__)
#undef __BLIB_QNXNTO__
#define __BLIB_QNXNTO__	1
#define __BLIB_OSTYPE__ 'QNXN'
#endif
#if defined(riscos) || defined(__riscos) || defined(__riscos__)
#undef __BLIB_RISCOS__
#define __BLIB_RISCOS__	1
#define __BLIB_OSTYPE__ 'RISC'
#endif
#if defined(__SVR4)
#undef __BLIB_SOLARIS__
#define __BLIB_SOLARIS__	1
#define __BLIB_OSTYPE__ 'SVR4'
#endif
#if defined(WIN32) || defined(_WIN32)
#undef __BLIB_WIN32__
#define __BLIB_WIN32__	1
#define __BLIB_OSTYPE__ 'WN32'
#endif
#if (defined(_WIN64) && (defined(_M_AMD64) || defined(_M_X64))) || defined(__x86_64__)
#undef __BLIB_PLATFORM64__
#define __BLIB_PLATFORM64__ 1
#define __BLIB_OSTYPE__ 'WN64'
#endif

#if defined(__linux__)     || defined(__unix__)    || \
      defined(__OpenBSD__)   || defined(__FreeBSD__) || defined(__NetBSD__) || \
      defined(__DragonFly__) || defined(__BSD__)     || defined(__FREEBSD__) || \
      defined(__APPLE__)
#undef __BLIB_POSIX__
#define __BLIB_POSIX__ 1
#endif

#endif// __BLIB_PLATFORM_CONFIG_INCLUDED__
