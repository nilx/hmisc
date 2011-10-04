#!/bin/sh
#
# Test the code compilation and execution.

# Nothing to test yet
_test_run() {
    FOO=foo
}

################################################

_log_init

echo "* default build, test, clean, rebuild"
#_log make -B debug
_log _test_run
_log make -B
_log _test_run
_log make
_log make clean
_log make

echo "* compiler support"
#for CC in cc c++ c99 gcc g++ tcc nwcc clang icc pathcc suncc \
#    i586-mingw32msvc-cc; do
for CC in c99 tcc nwcc clang suncc i586-mingw32msvc-cc; do
    which $CC || continue
    echo "* $CC compiler"
    _log make distclean
    case $CC in
	"gcc"|"g++")
	    _log make CC=$CC ;;
	*)
	    _log make CC=$CC CFLAGS= ;;
    esac
    _log _test_run
done

_log make distclean

_log_clean
