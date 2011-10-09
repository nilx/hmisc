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
 * @file smem.h
 * @brief safe memory allocation
 *
 * This code comes from Enric Meinhardt's xmalloc()[1], with some
 * additional tweaks.
 *
 * [1]http://tools.ipol.im/wiki/author/code/fragments_in_c/
 */

#ifndef _SMEM_H
#define _SMEM_H

#include <stdlib.h>
#include <stdio.h>

/** @brief abort() wrapper macro with an error message */
#define _ABORT() do {					\
    fputs("not enough memory\n", stderr);		\
    fflush(NULL);                                       \
    abort();                                            \
    } while (0);

/** @brief safe malloc() wrapper */
static void *_smalloc(size_t size)
{
    void *memptr;

    if (NULL == (memptr = malloc(size)))
        _ABORT();
    return memptr;
}

/** @brief safe malloc() wrapper macro with safe casting */
#define SMALLOC(NB, TYPE)				\
    ((TYPE *) _smalloc((size_t) (NB) * sizeof(TYPE)))

/** @brief safe free() wrapper macro */
#define SFREE(PTR) do {				\
    if (NULL != PTR) {  			\
	free(PTR);				\
        PTR = NULL;				\
        }					\
    } while (0);

/** @brief safe realloc() wrapper */
static void *_srealloc(void *memptr, size_t size)
{
    void *newptr;

    if (NULL == (newptr = realloc(memptr, size)))
        _ABORT();
    return newptr;
}

/** @brief safe realloc() wrapper macro with safe casting */
#define SREALLOC(PTR, NB, TYPE)						\
    ((TYPE *) _srealloc((void *) (PTR), (size_t) (NB) * sizeof(TYPE)))

/** @brief safe calloc() wrapper */
static void *_scalloc(size_t nb, size_t size)
{
    void *memptr;

    if (NULL == (memptr = calloc(nb, size)))
        _ABORT();
    return memptr;
}

/** @brief safe calloc() wrapper macro with safe casting */
#define SCALLOC(NB, TYPE)                      \
    ((TYPE *) _scalloc(NB, sizeof(TYPE)))

#endif                          /* !_SMEM_H */
