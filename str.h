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
 * @file str.h
 *
 * Tiny string manipulation utilities. There probably are plenty of
 * better and full-featured alternatives floating in the interwebs,
 * starting with bstrings.
 */

#ifndef _STR_H_
#define _STR_H_

#include <stdlib.h>
#include <string.h>

#ifndef EOS
#define EOS '\0'
#endif

#ifndef EOL
#define EOL '\n'
#endif

/**
 * @sbrief split a string in 2 parts
 *
 * pfx and sfx must be already allocated to input string length +1,
 * or NULL (and ignored)
 *
 * @param str string to split
 * @param sep separator character
 * @param pfx sfx prefix and suffix string pointers
 */
static void str_split2(const char *str, char sep, char *pfx, char *sfx)
{
    const char *start, *stop;

    /* get the prefix */
    start = str;
    stop = strchr(str, sep);
    if (NULL == stop)
        /* separator not found, get the whole string */
        stop = str + strlen(str);
    if (NULL != pfx) {
        strncpy(pfx, start, (size_t) (stop - start));
        pfx[stop - start] = '\0';
    }

    /* get the suffix */
    start = stop + 1;
    stop = str + strlen(str);
    if (stop < start)
        /* no separator */
        stop = start;
    if (NULL != sfx) {
        strncpy(sfx, start, (size_t) (stop - start));
        sfx[stop - start] = '\0';
    }

    return;
}

/**
 * @brief convert to uppercase
 *
 * Avoid ctype.h if we don't need heavy locale settings. We only suppose
 * the alphabetic characters are continuously encoded.
 */
static char *str_toupper(char *str)
{
    size_t i;
    char c;

    for (i = 0; i < strlen(str); i++) {
        c = str[i];
        if (c >= 'a' && c <= 'z')
            str[i] = c + 'A' - 'a';
    }

    return str;
}

/**
 * @brief convert to lowercase
 *
 * Avoid ctype.h if we don't need heavy locale settings. We only suppose
 * the alphabetic characters are continuously encoded.
 */
static char *str_tolower(char *str)
{
    size_t i;
    char c;

    for (i = 0; i < strlen(str); i++) {
        c = str[i];
        if (c >= 'A' && c <= 'Z')
            str[i] = c + 'a' - 'A';
    }

    return str;
}

#endif                          /* !_STR_H_ */
