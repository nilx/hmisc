/*
 * Copyright (c) 2011, Pascal Getreuer <pascal.getreuer@cmla.ens-cachan.fr>
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
 * @file xtime.h
 *
 * Portable high-precision xtime() clock with millisecond precision.
 * On Windows or POSIX systems, native high-precision calls are
 * used. On other systems we use the standatd libc time() function
 * with very bad precision (1 second) and we set the macro
 * XTIME_LOW_PRECISION, but the code can still compile with calls to
 * xtime().
 *
 * This is the calendar time, so these measures will be influenced by
 * external factors such as the presence of other computing-intensive
 * processes, the disk access time, and multithreading.
 */

#ifndef _XTIME_H_
#define _XTIME_H_

/*
 * OS DETECTION
 */

#if (! defined(__STDC__))
/*
 * The compiler is not C89 compatible, we can't expect any reliable
 * behaviour, let's give up early.
 */
#error The compiler needs to implement at least the C89 standard.

#elif (defined(_WIN32) || defined(__WIN32__) \
     || defined(__TOS_WIN__) || defined(__WINDOWS__))
/* from http://predef.sourceforge.net/preos.html#sec25 */

#define XTIME_WINDOWS

#elif (defined(__unix__) || defined(__unix))
/* from http://predef.sourceforge.net/preos.html#sec47 */

#include <unistd.h>
#if (defined(_POSIX_VERSION) && (_POSIX_VERSION >= 200112L))

#define XTIME_POSIX

#endif                          /* posix test */
#endif                          /* windows/unix test */

/*
 * OS-DEPENDANT IMPLEMENTATION
 */

#define _ul unsigned long       /* temporary, for shorter lines */

#if defined(XTIME_WINDOWS)      /* Windows implementation */

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
/**
 * @brief millisecond timer for Windows using GetSystemTime()
 */
static unsigned long xtime()
{
    static SYSTEMTIME t;
    GetSystemTime(&t);
    return (_ul) ((_ul) t.wMilliseconds
                  + 1000 * ((_ul) t.wSecond
                            + 60 * ((_ul) t.wMinute
                                    + 60 * ((ul) t.wHour
                                            + 24 * (_ul) t.wDay))));
}

#elif defined(XTIME_POSIX)      /* POSIX implementation */

#include <sys/time.h>
/**
 * @brief millisecond timer for POSIX using gettimeofday()
 */
static unsigned long xtime()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return (unsigned long) (t.tv_usec / 1000 + t.tv_sec * 1000);
}

#else                           /* C89 libc implementation */

#include <time.h>
#define XTIME_LOW_PRECISION
/**
 * @brief pseudo-millisecond timer for C89 using time()
 *
 * This timer grows by increments of 1000 milliseconds.
 */
static unsigned long xtime()
{
    time_t rawtime;
    struct tm *t;

    time(&rawtime);
    t = localtime(&rawtime);
    return (_ul) (1000 * ((_ul) t->tm_sec
                          + 60 * ((_ul) t->tm_min +
                                  +60 * ((_ul) t->tm_hour +
                                         +24 * (_ul) t->tm_mday))));
}

#endif                          /* implementations */

#undef _ul

#endif                          /* !_XTIME_H_ */
