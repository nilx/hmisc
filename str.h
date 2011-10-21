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

/* splint config */
/*@ -fcnuse -varuse @*/

#include <stdlib.h>
#include <string.h>

#ifndef EOS
#define EOS '\0'
#endif

#ifndef EOL
#define EOL '\n'
#endif

#define MAX(A, B) ((A) > (B) ? (A) : (B))

/**
 * @brief split a string at the first or last occurence of a char
 */
static void _str_split2(const char *str, char sep,
                        char *pfx, char *sfx, int first)
{
    const char *bgn, *mid, *end;
    size_t len;

    bgn = str;
    end = str + strlen(str);
    mid = (first ? strchr(str, sep) : strrchr(str, sep));

    if (NULL == mid) {
        /* separator not found, copy str to pfx, empty sfx */
        if (NULL != pfx)
            strcpy(pfx, str);
        if (NULL != sfx)
            sfx[0] = '\0';
        return;
    }

    /* get the prefix */
    if (NULL != pfx) {
        len = (size_t) MAX(mid - bgn, 0);
        strncpy(pfx, bgn, len);
        pfx[len] = EOS;
    }

    /* get the suffix */
    mid += 1;
    if (NULL != sfx) {
        len = (size_t) MAX(end - mid, 0);
        strncpy(sfx, mid, len);
        sfx[len] = EOS;
    }

    return;
}

/**
 * @sbrief split a string at the first occurence of a char
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
    int first = 1;
    _str_split2(str, sep, pfx, sfx, first);
    return;
}

/**
 * @sbrief split a string at the last occurence of a char
 *
 * pfx and sfx must be already allocated to input string length +1,
 * or NULL (and ignored)
 *
 * @param str string to split
 * @param sep separator character
 * @param pfx sfx prefix and suffix string pointers
 */
static void str_rsplit2(const char *str, char sep, char *pfx, char *sfx)
{
    int first = 0;
    _str_split2(str, sep, pfx, sfx, first);
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

/**
 * @brief match at the end of a string
 */
static int str_endswith(const char *str, const char *match)
{
    return (0 == strcmp(match, str + strlen(str) - strlen(match)));
}

/*@ =fcnuse =varuse @*/

#endif                          /* !_STR_H_ */
