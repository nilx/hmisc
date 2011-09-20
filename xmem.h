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
 * @file xmem.h
 * @brief safe memory allocation
 *
 * This code comes from Enric Meinhardt's xmalloc()[1], following
 * further developments for io_png[2].
 *
 * [1]http://tools.ipol.im/wiki/author/code/fragments_in_c/
 * [2]http://dev.ipol.im/git/?p=nil/io_png.git
 */

#ifndef _XMEM_H
#define _XMEM_H

#include <stdlib.h>

/** @brief abort() wrapper macro with an error message */
#define _ABORT(MSG) do {                                        \
    fprintf(stderr, "%s:%04u : %s\n", __FILE__, __LINE__, MSG); \
    fflush(stderr);                                             \
    abort();                                                    \
    } while (0);

/** @brief safe malloc wrapper */
static void *_xmalloc(size_t size)
{
    void *memptr;

    if (NULL == (memptr = malloc(size)))
        _ABORT("not enough memory");
    return memptr;
}

/** @brief safe malloc wrapper macro with safe casting */
#define _XMALLOC(NB, TYPE)                                              \
    ((TYPE *) _xmalloc((size_t) (NB) * sizeof(TYPE)))

/** @brief safe realloc wrapper */
static void *_xrealloc(void *memptr, size_t size)
{
    void *newptr;

    if (NULL == (newptr = realloc(memptr, size)))
        _ABORT("not enough memory");
    return newptr;
}

/** @brief safe realloc wrapper macro with safe casting */
#define _XREALLOC(PTR, NB, TYPE)                             \
    ((TYPE *) _xrealloc((void *) (PTR), (size_t) (NB) * sizeof(TYPE)))

/** @brief safe calloc wrapper */
static void *_xcalloc(size_t nb, size_t size)
{
    void *memptr;

    if (NULL == (memptr = calloc(nb, size)))
        _ABORT("not enough memory");
    return memptr;
}

/** @brief safe calloc wrapper macro with safe casting */
#define _XCALLOC(NB, TYPE)                      \
    ((TYPE *) _xcalloc(NB, sizeof(TYPE))

#endif                          /* !_XMEM_H */
