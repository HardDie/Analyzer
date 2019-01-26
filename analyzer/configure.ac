#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([analyzer], [1.0], [oleg1995sysoev@yandex.ru])
AC_CONFIG_SRCDIR([src/main.c])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC
AM_INIT_AUTOMAKE([subdir-objects])
CFLAGS="$CFLAGS -I./include"
LDFLAGS="$LDFLAGS -lpthread"

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([arpa/inet.h stdint.h stdlib.h string.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_INT32_T
AC_TYPE_INT8_T
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT64_T
AC_TYPE_UINT8_T

# Checks for library functions.
AC_CHECK_FUNCS([memset])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
