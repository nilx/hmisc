# Copyright 2011 Nicolas Limare <nicolas.limare@cmla.ens-cachan.fr>
#
# Copying and distribution of this file, with or without
# modification, are permitted in any medium without royalty provided
# the copyright notice and this notice are preserved.  This file is
# offered as-is, without any warranty.

# headers
HDR	= debug.h tqsort.h xstdint.h xmtime.h smem.h str.h
# pseudo-source code
SRC	= $(addprefix example/, $(HDR:.h=.c))
# object code
OBJ	= $(SRC:.c=.o)
# binary executable programs
BIN	= $(filter example/%, $(SRC:.c=))

# C compiler optimization options
COPT    =
# complete C compiler options
CFLAGS  = $(COPT)
# preprocessor options
CPPFLAGS        = -I. -DNDEBUG
# linker options
LDFLAGS	=
# libraries
LDLIBS	= -lm

# default target: the test tools
default: $(BIN)

# dependencies
-include makefile.dep

# partial C compilation xxx.c -> xxx.o
%.o	: %.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) -o $@ $<

# final link of an example program
example/%	: example/%.o
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

# cleanup
.PHONY  : clean distclean
clean   :
	$(RM) $(OBJ) *.plist
distclean       : clean
	$(RM) $(BIN)
	$(RM) -r srcdoc

################################################
# dev tasks
PROJECT	= hmish
-include	makefile.dev
