#!/bin/sh
#
# Test xstdint

_test_xstdint() {
    ./hmisc && echo passed || echo FAILED
}

################################################

_log_init

echo "* xstdint"

for CC in cc c++ c99 gcc g++ tcc nwcc clang icc pathcc suncc \
    i586-mingw32msvc-cc; do
    which $CC || continue
    echo "* $CC compiler"
    case $CC in
	"gcc")
	    _log make -B CC=$CC CFLAGS="-std=c89 -m32" LDFLAGS="-m32"
	    _test_xstdint
	    _log make -B CC=$CC CFLAGS="-std=c99 -m32" LDFLAGS="-m32"
	    _test_xstdint
	    _log make -B CC=$CC CFLAGS="-std=c89 -m64" LDFLAGS="-m64"
	    _test_xstdint
	    _log make -B CC=$CC CFLAGS="-std=c99 -m64" LDFLAGS="-m64"
	    _test_xstdint
	    ;;
	"icc")
            #icc -m32 requires another compiler binary
	    #_log make -B CC=$CC CFLAGS="-std=c89 -m64" LDFLAGS="-m32"
	    #_log make -B CC=$CC CFLAGS="-std=c99 -m64" LDFLAGS="-m32"
	    _log make -B CC=$CC CFLAGS="-std=c89 -m64" LDFLAGS="-m64"
	    _test_xstdint
	    _log make -B CC=$CC CFLAGS="-std=c99 -m64" LDFLAGS="-m64"
	    _test_xstdint
	    ;;
	"suncc")
	    _log make -B CC=$CC CFLAGS="-Xc -xc99=none -m32" LDFLAGS="-m32"
	    _test_xstdint
	    _log make -B CC=$CC CFLAGS="-Xc -xc99=all -m32" LDFLAGS="-m32"
	    _test_xstdint
	    _log make -B CC=$CC CFLAGS="-Xc -xc99=none -m64" LDFLAGS="-m64"
	    _test_xstdint
	    _log make -B CC=$CC CFLAGS="-Xc -xc99=all -m64" LDFLAGS="-m64"
	    _test_xstdint
	    ;;
	"pathcc")
	    #64bit only
	    _log make -B CC=$CC CFLAGS="-std=c89"
	    _test_xstdint
	    _log make -B CC=$CC CFLAGS="-std=c99"
	    _test_xstdint
	    ;;
	"tcc")
	    #no c99, no arch selection
	    _log make -B CC=$CC CFLAGS=
	    _test_xstdint
	    ;;
	"nwcc")
	    #nwcc uses the gcc preprocessor
	    #_log make -B CC="$(CC) -ansi"
	    #_test_xstdint
	    ;;
	"i586-mingw32msvc-cc")
	    _log make -B CC=$CC CFLAGS=
	    _test_xstdint
	    ;;
	*)
	    #_log make -B CC=$CC CFLAGS=
	    #_test_xstdint
	    ;;
    esac
done

_log make distclean

_log_clean
