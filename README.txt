% Cbits

# OVERVIEW

Hmisc is a collection bits of C code, providing tiny tools and
facilities:

debug.h:
  NDEBUG-aware printf macros and routines to measure cycles and CPU
  time for profiling.

tqsort.h:
  Type-specific versions of qsort().

xstdint.h:
  Cross-platform definition of exact-width integers as defined in the
  C99 standard but usable with C89.

xmtime.h:
  Cross-platform millisecond timer for Windows and POSIX. On other
  systems, this precision timer is emulated with the standard libc
  low-precision time functions.

smem.h:
  Failsafe memory allocation.

str.h:
  String utilities.

# LICENSE

See each source file.

# USAGE

These headers are written for a local use by header inclusion only. No
need to compile, everything is local to the compilation unit (source
file), just include the header you need where you need it.

See each source file for derails.

# TODO

Add a test suite and some examples.

Add other bits of code:
- xio.h: robust file handling
  cf. http://tools.ipol.im/wiki/author/code/fragments_in_c/)
- mt.h: mersenne twister, from http://dev.ipol.im/git/?p=nil/mt.git
- bit twiddling, cf. http://bits.stephan-brumme.com/
- snprintf.h: poor man's snprintf()

# ABOUT THIS FILE

Copyright 2011 Nicolas Limare <nicolas.limare@cmla.ens-cachan.fr>

Copying and distribution of this file, with or without modification,
are permitted in any medium without royalty provided the copyright
notice and this notice are preserved.  This file is offered as-is,
without any warranty.
