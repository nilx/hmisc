#include <limits.h>

#ifdef __STDC__
#ifdef __STDC_VERSION__
#if __STDC_VERSION__ >= 199901L
/* C99 already defines int8_t, int16_t, ... */
#define HAVE_TYPEDEFS
#endif
#endif
#endif


#ifndef HAVE_TYPEDEFS
/*
 * what is the cpp integer constant capacity?
 * how to avoid overflows?
 */
#define _8BITS  255
#define _16BITS 65535L
#define _32BITS 4294967295UL
#define _64BITS 18446744073709551615UL

#if UCHAR_MAX == _8BITS
#define _UINT8_T char
#endif

#if UCHAR_MAX == _16BITS /* unlikely, but possible */
#define _UINT16_T char
#elif USHRT_MAX == _16BITS
#define _UINT16_T short
#elif UINT_MAX == _16BITS
#define _UINT16_T int
#endif

#if UCHAR_MAX == _32BITS /* VERY unlikely, but ... */
#define _UINT32_T char
#elif USHRT_MAX == _32BITS
#define _UINT32_T short
#elif UINT_MAX == _32BITS
#define _UINT32_T int
#elif ULONG_MAX == _32BITS
#define _UINT32_T long
#endif

#if UCHAR_MAX == _64BITS /* would be crazy, but ... */
#define _UINT64_T char
#elif USHRT_MAX == _64BITS
#define _UINT64_T short
#elif UINT_MAX == _64BITS
#define _UINT64_T int
#elif ULONG_MAX == _64BITS
#define _UINT64_T long
#endif

#ifdef _UINT8_T
typedef _UINT8_T uint8_t;
#else
typedef _UINT8_T _UNDEFINED;
#endif

#ifdef _UINT16_T
typedef _UINT16_T uint16_t;
#else
typedef _UINT16_T _UNDEFINED;
#endif

#ifdef _UINT32_T
typedef _UINT32_T uint32_t;
#else
typedef _UINT32_T _UNDEFINED;
#endif

#ifdef _UINT64_T
typedef _UINT64_T uint64_t;
#else
typedef _UINT64_T _UNDEFINED;
#endif

typedef unsigned int8_t uint8_t;
typedef unsigned int16_t uint16_t;
typedef unsigned int32_t uint32_t;
typedef unsigned int64_t uint64_t;

#endif /* !HAVE_TYPEDEFS */
