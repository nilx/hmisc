# Copyright 2011 Nicolas Limare <nicolas.limare@cmla.ens-cachan.fr>
#
# Copying and distribution of this file, with or without
# modification, are permitted in any medium without royalty provided
# the copyright notice and this notice are preserved.  This file is
# offered as-is, without any warranty.

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
NWCC	= nwcc
NWCC_C89	= -ansi
NWCC_C99	=
TCC	= tcc -Wall -Werror
TCC_C89	= 

# default target: the test
default: test

# test program compilation
tester	: tester.c c89stdint.h
	$(CC) $< -I. -o $@

.PHONY	: test cctest
# compiler test
test	:
	$(MAKE) CC="$(GCC) $(GCC_C89)" cctest
	$(MAKE) CC="$(GCC) $(GCC_C99)" cctest
	$(MAKE) CC="$(ICC) $(ICC_C89)" cctest
	$(MAKE) CC="$(ICC) $(ICC_C99)" cctest
	$(MAKE) CC="$(SUNCC) $(SUNCC_C89)" cctest
	$(MAKE) CC="$(SUNCC) $(SUNCC_C99)" cctest
	$(MAKE) CC="$(NWCC) $(NWCC_C89)" cctest
	$(MAKE) CC="$(NWCC) $(NWCC_C99)" cctest
	$(MAKE) CC="$(TCC) $(TCC_C99)" cctest
	$(MAKE) distclean
cctest	:
	if [ $$(which $(CC)) ]; then $(MAKE) -B tester; ./tester; fi

# cleanup
.PHONY	: clean distclean
clean	:
	$(RM) tester
distclean	: clean

################################################
# extra tasks

PROJECT	= c89stdint
DATE	= $(shell date -u +%Y%m%d)
RELEASE_TAG   = 0.$(DATE)

.PHONY	: lint beautify release
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
# release tarball
release	: beautify lint test distclean
	git archive --format=tar --prefix=$(PROJECT)-$(RELEASE_TAG)/ HEAD \
	        | gzip > ../$(PROJECT)-$(RELEASE_TAG).tar.gz
