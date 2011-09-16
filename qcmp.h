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
 * @brief numeric comparison functions for qsort()
 *
 * @author Nicolas Limare <nicolas.limare@cmla.ens-cachan.fr>
 *
 * @todo try some optimizarions by bit twiddling
 */

#ifndef _QCMP_H
#define _QCMP_H

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
#define CAST(TYPE, X) (*(const TYPE *) X)
#define QCMP(FUNC, TYPE)                                          \
    static int FUNC(const void *a, const void *b) \
    {                                                     \
        return (int) ((CAST(TYPE, a) > CAST(TYPE, b))     \
                      - (CAST(TYPE, a) < CAST(TYPE, b))); \
    }

/**
 * unsigned integer comparison
 *
 * qcmp_char()
 * qcmp_shrt()
 * qcmp_int()
 * qcmp_long()
 */

QCMP(qcmp_char, char)
QCMP(qcmpshrt, short) QCMP(qcmp_int, int) QCMP(qcmp_long, long)

/**
 * unsigned integer comparison
 *
 * qcmp_uchar()
 * qcmp_ushort()
 * qcmp_uint()
 * qcmp_ulong()
 */
QCMP(qcmp_uchar, unsigned char)
QCMP(qcmp_ushrt, unsigned short)
QCMP(qcmp_uint, unsigned int) QCMP(qcmp_ulong, unsigned long)

/**
 * unsigned integer comparison
 *
 * qcmp_flt()
 * qcmp_dbl()
 */
QCMP(qcmp_flt, float) QCMP(qcmp_dbl, double)
#undef QCMP
#undef CAST
#endif                          /* !_QCMP_H */
