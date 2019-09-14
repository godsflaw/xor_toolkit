#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.57)
AC_INIT(xor_toolkit, 0.0.0, chris@dod.net)
AC_CONFIG_SRCDIR([src/xor_toolkit.c])
AC_CONFIG_HEADER([config.h])
AM_INIT_AUTOMAKE


# Checks for programs.
AC_PROG_CC
AM_PROG_CC_C_O
AC_PROG_LIBTOOL


# Checks for libraries.
AM_WITH_DMALLOC


# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([stdio.h stdlib.h string.h unistd.h errno.h dmalloc.h \
                  sys/types.h sys/stat.h fcntl.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST


# Checks for library functions.
AC_FUNC_MALLOC


# Write output
AC_CONFIG_FILES([Makefile src/Makefile])
AC_OUTPUT
