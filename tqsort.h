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
 * @file tqsort.h
 * @brief numeric comparison functions and type-safe shortcuts to qsort()
 *
 * @author Nicolas Limare <nicolas.limare@cmla.ens-cachan.fr>
 *
 * @todo try some optimizations by bit twiddling and type punning
 */

#ifndef _TQSORT_H
#define _TQSORT_H

#include <stdlib.h>

/**
 * macros to define similar functions:
 *   static int _qcmp_XXX(const void *a, const void *b)
 * where the suffix defines the type of the scalars to be compared:
 * - _qcmp_char()   char
 * - _qcmp_shrt()   short
 * - _qcmp_int()    int
 * - _qcmp_long()   long
 * - _qcmp_uchar()  unsigned char
 * - _qcmp_ushrt()  unsigned short
 * - _qcmp_uint()   unsigned int
 * - _qcmp_ulong()  unsigned long
 * - _qcmp_flt()    float
 * - _qcmp_dbl()    double
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
QCMP(_qcmp_char, char);
QCMP(_qcmp_shrt, short);
QCMP(_qcmp_int, int);
QCMP(_qcmp_long, long);
QCMP(_qcmp_uchar, unsigned char);
QCMP(_qcmp_ushrt, unsigned short);
QCMP(_qcmp_uint, unsigned int);
QCMP(_qcmp_ulong, unsigned long);
QCMP(_qcmp_flt, float);
QCMP(_qcmp_dbl, double);

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
QSORT(qsort_char, _qcmp_char, char);
QSORT(qsort_shrt, _qcmp_shrt, short);
QSORT(qsort_int, _qcmp_int, int);
QSORT(qsort_long, _qcmp_long, long);
QSORT(qsort_uchar, _qcmp_uchar, unsigned char);
QSORT(qsort_ushrt, _qcmp_ushrt, unsigned short);
QSORT(qsort_uint, _qcmp_uint, unsigned int);
QSORT(qsort_ulong, _qcmp_ulong, unsigned long);
QSORT(qsort_flt, _qcmp_flt, float);
QSORT(qsort_dbl, _qcmp_dbl, double);

#undef QSORT

#endif                          /* !_TQSORT_H */
