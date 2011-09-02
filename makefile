# Copyright 2011 Nicolas Limare <nicolas.limare@cmla.ens-cachan.fr>
#
# Copying and distribution of this file, with or without
# modification, are permitted in any medium without royalty provided
# the copyright notice and this notice are preserved.  This file is
# offered as-is, without any warranty.

# source code, C language
CSRC	= tester.c
# header, C language
CHDR	= c89stdint.h
# source code, all languages (only C here)
SRC	= $(CSRC)
# object files (partial compilation)
OBJ	= $(CSRC:.c=.o)
# binary executable programs
BIN	= $(CSRC:.c=)

# default target: the example programs
default: $(BIN)

# C compilation
tester	: tester.c c89stdint.h
	$(CC) $< -c -I. -o $@

# cleanup
.PHONY	: clean distclean scrub
clean	:
	$(RM) $(OBJ)
	$(RM) *.flag
distclean	: clean
	$(RM) $(BIN)
	$(RM) -r srcdoc

################################################
# compilers

GCC	= gcc -pedantic -Wall -Wextra -Werror
GCC_C89	= -std=c89
GCC_C99	= -std=c99
ICC	= icc -Wall -Werror
ICC_C89	= -std=c89
ICC_C99	= -std=c99
SUNCC	= suncc -Xc -errwarn
SUNCC_C89	= -xc99=none
SUNCC_C99	= -xc99=all
TCC	= tcc -Wall -Werror
TCC_C89	= 
TCC_C99	= 
NWCC	= nwcc
NWCC_C89	= -ansi

# default compiler
CC	= cc -ansi

################################################
# extra tasks

PROJECT	= c89stdint
DATE	= $(shell date -u +%Y%m%d)
RELEASE_TAG   = 0.$(DATE)

.PHONY	: srcdoc lint beautify test release
# source documentation
srcdoc	: $(CSRC) $(CHDR)
	doxygen doc/doxygen.conf
# code cleanup
beautify	: $(CSRC) $(CHDR)
	for FILE in $^; do \
		expand $$FILE | sed 's/[ \t]*$$//' > $$FILE.$$$$ \
		&& indent -kr -i4 -l78 -nut -nce -sob -sc \
			$$FILE.$$$$ -o $$FILE \
		&& rm $$FILE.$$$$; \
	done
# static code analysis
lint	: $(CSRC) $(CHDR)
	for FILE in $^; do \
		clang --analyze -ansi -I. $$FILE || exit 1; done;
	for FILE in $^; do \
		splint -ansi-lib -weak -I. $$FILE || exit 1; done;
	$(RM) *.plist
# code tests
test	: $(CSRC) $(CHDR)

# release tarball
release	: beautify lint test distclean
	git archive --format=tar --prefix=$(PROJECT)-$(RELEASE_TAG)/ HEAD \
	        | gzip > ../$(PROJECT)-$(RELEASE_TAG).tar.gz
