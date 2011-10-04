# Copyright 2011 Nicolas Limare <nicolas.limare@cmla.ens-cachan.fr>
#
# Copying and distribution of this file, with or without
# modification, are permitted in any medium without royalty provided
# the copyright notice and this notice are preserved.  This file is
# offered as-is, without any warranty.

HDR	= debug.h tqsort.h xstdint.h xmtime.h smem.h
SRC	= $(HDR:.h=.c)

# default target: the test
default: test

# test program compilation
%.c	: %.h
	cp $< $@
xstdint	: xstdint.c
	$(CC) -D_XSTDINT_TEST $< -I. -o $@

test	: xstdint.test

################################################
# xstdint test

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

.PHONY	: xstdint.test xstdint.cctest
# compiler test
xstdint.test	:
	@$(MAKE) -s CC="$(GCC) $(GCC_C89) $(GCC_32)" xstdint.cctest
	@$(MAKE) -s CC="$(GCC) $(GCC_C99) $(GCC_32)" xstdint.cctest
	@$(MAKE) -s CC="$(GCC) $(GCC_C89) $(GCC_64)" xstdint.cctest
	@$(MAKE) -s CC="$(GCC) $(GCC_C99) $(GCC_64)" xstdint.cctest
#        icc -m32 requires another compiler binary
#        @$(MAKE) -s CC="$(ICC) $(ICC_C89) $(ICC_32)" xstdint.cctest
#        @$(MAKE) -s CC="$(ICC) $(ICC_C99) $(ICC_32)" xstdint.cctest
	@$(MAKE) -s CC="$(ICC) $(ICC_C89) $(ICC_64)" xstdint.cctest
	@$(MAKE) -s CC="$(ICC) $(ICC_C99) $(ICC_64)" xstdint.cctest
	@$(MAKE) -s CC="$(SUNCC) $(SUNCC_C89) $(SUNCC_32)" xstdint.cctest
	@$(MAKE) -s CC="$(SUNCC) $(SUNCC_C99) $(SUNCC_32)" xstdint.cctest
	@$(MAKE) -s CC="$(SUNCC) $(SUNCC_C89) $(SUNCC_64)" xstdint.cctest
	@$(MAKE) -s CC="$(SUNCC) $(SUNCC_C99) $(SUNCC_64)" xstdint.cctest
	@$(MAKE) -s CC="$(PATHCC) $(PATHCC_C89)" xstdint.cctest
	@$(MAKE) -s CC="$(PATHCC) $(PATHCC_C99)" xstdint.cctest
#        nwcc uses the gcc preprocessor
#        @$(MAKE) -s CC="$(NWCC) $(NWCC_C89)" xstdint.cctest
#        @$(MAKE) -s CC="$(NWCC) $(NWCC_C99)" xstdint.cctest
	@$(MAKE) -s CC="$(TCC) $(TCC_C89)" xstdint.cctest
xstdint.cctest	:
	@if [ $$(which $(CC)) ]; then \
		($(MAKE) -s -B xstdint && ./xstdint) \
			&& echo passed: $(CC) \
			|| echo FAILED: $(CC); \
	fi
	@$(MAKE) -s distclean

# cleanup
.PHONY	: clean distclean
clean	:
	$(RM) xstdint
	$(RM) $(SRC)
distclean	: clean
	$(RM) -r srcdoc

################################################
# dev tasks
PROJECT	= hmish
-include	makefile.dev
