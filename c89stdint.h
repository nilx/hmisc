/**
 * @file c89stdint.h
 *
 * This file tries to provide the exact-width integer type definitions
 * specified in the C99 standard[1] for use with C89 (ANSI C). Only the
 * the exact-width type definitions (int8_t, int16_t, ...) and limits
 * (INT8_MAX, ...) are provided, not the min-width, fastest, other
 * limits, ... This file tries to rely only on C89 standards.
 *
 * pstdint.h[2] is another similar code, more ambitious (mode type
 * definitions, printf symbols). It uses compiler-specific macros.
 *
 * - if you write C99 code, you can #include <stdint.h> and
 *   explicitely select C99 in your compiler flags;
 * - if you write C89 code but you want exact-width types, you can
 *   #include <c89stdint.h> and scplicitely select C89 in your
 *   compiler flags;
 * - if you write some code that should be usable on a C89 or C99
 *   compiler and you exact-width types, you can #include
 *   <c89stdint.h> and it will use the C99 stdint.h when compiled on a
 *   C99 compiler.
 *
 * [1]http://pubs.opengroup.org/onlinepubs/9699919799/basedefs/stdint.h.html
 * [2]http://www.azillionmonkeys.com/qed/pstdint.h
 *
 */

#ifndef _C89STDINT_H_
#define _C89STDINT_H_

#if (! defined(__STDC__))
/*
 * The compiler is not C89 compatible, we can't expect any reliable
 * behaviour, let's give up early.
 */
#error The compiler needs to implement at least the C89 standard.
#endif

#if (defined (__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L))
/* The file is processed by a C99 compiler, let's use stdint.h. */
#include <stdint.h>

#else
/*
 * The file is processed by a C89 compiler, we can use type limits
 * specified by the C89 standard (K&R2 p. 257.)
 *
 * For the moment, we suppose that the machine uses binary
 * representations and two's complement. Signed and unsigned limits
 * for a N bits type are supposed to always follow
 * - UXXX_MAX = 1 << N - 1
 * - XXX_MAX = 1 << (N - 1) - 1
 * - XXX_MIN = - XXX_MAX
 *
 * C89 minimum magnitudes are
 * - UCHAR_MAX >= 255 = 1 << 8 - 1
 * - USHRT_MAX >= 255 = 1 << 16 - 1
 * - UINT_MAX  >= 255 = 1 << 16 - 1
 * - ULONG_MAX >= 255 = 1 << 32 - 1
 *
 * Moreover, the preprocessor evaluation of #if lines uses long
 * arithmetics for integer constants. For clarity all the preprocessor
 * integer constants are defined as unsigned long.
 */
#include <limits.h>

/* 8 bits type */
#define _8BITS  255UL
#if UCHAR_MAX == _8BITS
#define _INT8_T char
#endif

/* 16 bits type */
#define _16BITS 65535UL
#if UCHAR_MAX == _16BITS
#define _INT16_T char
#elif USHRT_MAX == _16BITS
#define _INT16_T short
#elif UINT_MAX == _16BITS
#define _INT16_T int
#endif

/* 32 bits type */
#define _32BITS 4294967295UL
#if UCHAR_MAX == _32BITS
#define _INT32_T char
#elif USHRT_MAX == _32BITS
#define _INT32_T short
#elif UINT_MAX == _32BITS
#define _INT32_T int
#elif ULONG_MAX == _32BITS
#define _INT32_T long
#endif

/*
 * Gradually test bit width by increments of 8bits. If we have more
 * than N bits, we probably have at lease N+8 bits, then the
 * compiler must accept contants on N+8 bits.
 * This is needed because on a 32bit system, the preprocessor may
 * not support definitions like
 *   #define _64BITS 18446744073709551615UL
 * and the compilers don't handle consistently tests like
 *   #if (1UL << 63)
 *
 * TODO: use right-shift instead
 */
#if ULONG_MAX > _32BITS
#define _40BITS 1099511627775UL
#if ULONG_MAX > _40BITS
#define _48BITS 281474976710655UL
#if ULONG_MAX > _48BITS
#define _56BITS 72057594037927935UL
#if ULONG_MAX > _56BITS
/* 64 bits type */
#define _64BITS 18446744073709551615UL
#if UCHAR_MAX == _64BITS
#define _INT64_T char
#elif USHRT_MAX == _64BITS
#define _INT64_T short
#elif UINT_MAX == _64BITS
#define _INT64_T int
#elif ULONG_MAX == _64BITS
#define _INT64_T long
#endif                          /* ULONG_MAX == _64BITS */
#endif                          /* ULONG_MAX > _56BITS */
#endif                          /* ULONG_MAX > _48BITS */
#endif                          /* ULONG_MAX > _40BITS */
#endif                          /* ULONG_MAX > _32BITS */

#ifdef _INT8_T
typedef _INT8_T int8_t;
typedef unsigned _INT8_T uint8_t;
#define INT8_MAX 127;
#define INT8_MIN (-127);
#define UINT8_MAX 255;
#undef _INT8_T
#endif

#ifdef _INT16_T
typedef _INT16_T int16_t;
typedef unsigned _INT16_T uint16_t;
#define INT16_MAX 32767;
#define INT16_MIN (-32767);
#define UINT16_MAX 65535;
#undef _INT16_T
#endif

#ifdef _INT32_T
typedef _INT32_T int32_t;
typedef unsigned _INT32_T uint32_t;
#define INT32_MAX 2147483647;
#define INT32_MIN (-2147483647);
#define UINT32_MAX 4294967295;
#undef _INT32_T
#endif

#ifdef _INT64_T
typedef _INT64_T int64_t;
typedef unsigned _INT64_T uint64_t;
#define INT64_MAX 9223372036854775807;
#define INT64_MIN (-9223372036854775807);
#define UINT64_MAX 18446744073709551615;
#undef _INT64_T
#endif

#endif                          /* !C99 */

#endif /* !_C89STDINT_H_ */
