/*
 * Copyright (c) 2011, Nicolas Limare <nicolas.limare@cmla.ens-cachan.fr>
 * All rights reserved.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under, at your option, the terms of the GNU General Public
 * License as published by the Free Software Foundation, either
 * version 3 of the License, or (at your option) any later version, or
 * the terms of the simplified BSD license.
 *
 * You should have received a copy of these licenses along this
 * program. If not, see <http://www.gnu.org/licenses/> and
 * <http://www.opensource.org/licenses/bsd-license.html>.
 */

/**
 * @file qcmp.h
 * @brief numeric comparison functions and type-safe shortcuts to qsort()
 *
 * @author Nicolas Limare <nicolas.limare@cmla.ens-cachan.fr>
 *
 * @todo try some optimizations by bit twiddling
 */

#ifndef _QCMP_H
#define _QCMP_H

#include <stdlib.h>

/**
 * macros to define similar functions:
 *   static int qcmp_XXX(const void *a, const void *b)
 * where the suffix defines the type of the scalars to be compared:
 * - qcmp_char()   char
 * - qcmp_shrt()   short
 * - qcmp_int()    int
 * - qcmp_long()   long
 * - qcmp_uchar()  unsigned char
 * - qcmp_ushrt()  unsigned short
 * - qcmp_uint()   unsigned int
 * - qcmp_ulong()  unsigned long
 * - qcmp_flt()    float
 * - qcmp_dbl()    double
 */
/*
 * The last line it results in a declaration when QCMP(FOO, BAR); is
 * expanded. This is not really useful, but it maintains a correct
 * indentation when processing the source with the indent program.
 */
#define CAST(TYPE, X) (*(const TYPE *) X)
#define QCMP(FUNC, TYPE)                                  \
    static int FUNC(const void *a, const void *b)         \
    {                                                     \
        return (int) ((CAST(TYPE, a) > CAST(TYPE, b))     \
                      - (CAST(TYPE, a) < CAST(TYPE, b))); \
    }                                                     \
    static int FUNC(const void *a, const void *b)

/**
 * define all the qcmp variants
 */
QCMP(qcmp_char, char);
QCMP(qcmp_shrt, short);
QCMP(qcmp_int, int);
QCMP(qcmp_long, long);
QCMP(qcmp_uchar, unsigned char);
QCMP(qcmp_ushrt, unsigned short);
QCMP(qcmp_uint, unsigned int);
QCMP(qcmp_ulong, unsigned long);
QCMP(qcmp_flt, float);
QCMP(qcmp_dbl, double);

#undef QCMP
#undef CAST

/**
 * macros to define similar shortcut functions:
 *   static void qsort_XXX(TYPE *base, size_t n)
 * where the suffix defines the type of the scalars to be sorted.
 */

#define QSORT(FUNC, CMP, TYPE)                           \
    static void FUNC(TYPE *base, size_t n)               \
    {                                                    \
        qsort((void *) base, n, sizeof(TYPE), CMP);      \
    }                                                    \
    static void FUNC(TYPE *base, size_t n)

/**
 * define all the qsort variants
 */
QSORT(qsort_char, qcmp_char, char);
QSORT(qsort_shrt, qcmp_shrt, short);
QSORT(qsort_int, qcmp_int, int);
QSORT(qsort_long, qcmp_long, long);
QSORT(qsort_uchar, qcmp_uchar, unsigned char);
QSORT(qsort_ushrt, qcmp_ushrt, unsigned short);
QSORT(qsort_uint, qcmp_uint, unsigned int);
QSORT(qsort_ulong, qcmp_ulong, unsigned long);
QSORT(qsort_flt, qcmp_flt, float);
QSORT(qsort_dbl, qcmp_dbl, double);

#undef QSORT

#endif                          /* !_QCMP_H */
