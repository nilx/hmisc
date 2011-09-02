#include <limits.h>

#if (defined(__STDC__) && defined (__STDC_VERSION__) \
     && (__STDC_VERSION__ >= 199901L))
/*
 * C99 defines int8_t, int16_t, ...
 * -> http://pubs.opengroup.org/onlinepubs/9699919799/basedefs/stdint.h.html
 */
#include <stdint.h>

#else
/*
 * The preprocessor uses long or unsigned long arithmetics
 * (K&R2 p. 232) and ULONG_MAX >= 4294967295 (K&R2 p. 257), so
 * preprocessor constants can be defined up to 4294967295 without
 * overflow. for clarity, _8BITS, _16BITS and _32BITS are explicitely
 * defined as unsigned long.
 */

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
#endif /* ULONG_MAX == _64BITS */
#endif /* ULONG_MAX > _56BITS */
#endif /* ULONG_MAX > _48BITS */
#endif /* ULONG_MAX > _40BITS */
#endif /* ULONG_MAX > _32BITS */

#ifdef _INT8_T
typedef _INT8_T int8_t;
typedef unsigned int8_t uint8_t;
#endif

#ifdef _INT16_T
typedef _INT16_T int16_t;
typedef unsigned int16_t uint16_t;
#endif

#ifdef _INT32_T
typedef _INT32_T int32_t;
typedef unsigned int32_t uint32_t;
#endif

#ifdef _INT64_T
typedef _INT64_T int64_t;
typedef unsigned int64_t uint64_t;
#endif

#endif /* !C99 */
