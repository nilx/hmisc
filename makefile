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
GCC_32	= -m32
GCC_64	= -m64
ICC	= icc -Wall -Werror
ICC_C89	= -std=c89
ICC_C99	= -std=c99
ICC_32	= -m32
ICC_64	= -m64
SUNCC	= suncc -Xc -errwarn
SUNCC_C89	= -xc99=none
SUNCC_C99	= -xc99=all
SUNCC_32	= -m32
SUNCC_64	= -m64
PATHCC	= pathcc -Wall -Werror
PATHCC_C89	= -std=c89
PATHCC_C99	= -std=c99
TCC	= tcc -Wall -Werror
TCC_C89	= 
NWCC	= nwcc
NWCC_C89	= -ansi
NWCC_C99	=

HDR	= c89stdint.h
SRC	= $(HDR:.h=.c)
BIN	= $(SRC:.c=)

# default target: the test
default: test

# test program compilation
$(SRC)	: $(HDR)
	cp $< $@
$(BIN)	: $(SRC)
	$(CC) -D_C89STDINT_TEST $< -I. -o $@

.PHONY	: test cctest
# compiler test
test	:
	@$(MAKE) -s CC="$(GCC) $(GCC_C89) $(GCC_32)" cctest
	@$(MAKE) -s CC="$(GCC) $(GCC_C99) $(GCC_32)" cctest
	@$(MAKE) -s CC="$(GCC) $(GCC_C89) $(GCC_64)" cctest
	@$(MAKE) -s CC="$(GCC) $(GCC_C99) $(GCC_64)" cctest
#        icc -m32 requires another compiler binary
#        @$(MAKE) -s CC="$(ICC) $(ICC_C89) $(ICC_32)" cctest
#        @$(MAKE) -s CC="$(ICC) $(ICC_C99) $(ICC_32)" cctest
	@$(MAKE) -s CC="$(ICC) $(ICC_C89) $(ICC_64)" cctest
	@$(MAKE) -s CC="$(ICC) $(ICC_C99) $(ICC_64)" cctest
	@$(MAKE) -s CC="$(SUNCC) $(SUNCC_C89) $(SUNCC_32)" cctest
	@$(MAKE) -s CC="$(SUNCC) $(SUNCC_C99) $(SUNCC_32)" cctest
	@$(MAKE) -s CC="$(SUNCC) $(SUNCC_C89) $(SUNCC_64)" cctest
	@$(MAKE) -s CC="$(SUNCC) $(SUNCC_C99) $(SUNCC_64)" cctest
	@$(MAKE) -s CC="$(PATHCC) $(PATHCC_C89)" cctest
	@$(MAKE) -s CC="$(PATHCC) $(PATHCC_C99)" cctest
#        nwcc uses the gcc preprocessor
#        @$(MAKE) -s CC="$(NWCC) $(NWCC_C89)" cctest
#        @$(MAKE) -s CC="$(NWCC) $(NWCC_C99)" cctest
	@$(MAKE) -s CC="$(TCC) $(TCC_C89)" cctest
cctest	:
	@if [ $$(which $(CC)) ]; then \
		($(MAKE) -s -B $(BIN) && ./$(BIN)) \
			&& echo passed: $(CC) \
			|| echo FAILED: $(CC); \
	fi
	@$(MAKE) -s distclean

# cleanup
.PHONY	: clean distclean
clean	:
	$(RM) $(BIN)
	$(RM) $(SRC)
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
