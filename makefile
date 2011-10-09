# Copyright 2011 Nicolas Limare <nicolas.limare@cmla.ens-cachan.fr>
#
# Copying and distribution of this file, with or without
# modification, are permitted in any medium without royalty provided
# the copyright notice and this notice are preserved.  This file is
# offered as-is, without any warranty.

# headers
HDR	= debug.h tqsort.h xstdint.h xmtime.h smem.h
# pseudo-source code
SRC	= $(HDR:.h=.c)
# object code
OBJ	= $(HDR:.h=.o)
# test program
BIN	= hmisc

# C compiler optimization options
COPT    =
# complete C compiler options
CFLAGS  = $(COPT)
# preprocessor options
CPPFLAGS        = -DNDEBUG -D_XSTDINT_TEST

# default target: the test tools
default: $(BIN)

# .h->.c conversion
%.c	: %.h
	cp $< $@
# partial C compilation xxx.c -> xxx.o
%.o     : %.c
	$(CC) -c -o $@ $< $(CFLAGS) $(CPPFLAGS)
# final link
hmisc	: $(OBJ)
	$(CC) $^ $(LDFLAGS) -o $@

# cleanup
.PHONY  : clean distclean
clean   :
	$(RM) $(SRC) $(OBJ) *.plist
distclean       : clean
	$(RM) $(BIN)
	$(RM) -r srcdoc

################################################
# dev tasks
PROJECT	= hmish
-include	makefile.dev
