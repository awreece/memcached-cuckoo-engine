#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.61])
AC_INIT(cuckoo-engine, 0.1, awreece@gmail.com)
AC_CONFIG_SRCDIR([src])
AC_CONFIG_AUX_DIR(config)
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIR([m4])

PANDORA_CANONICAL_TARGET

AC_CHECK_HEADERS([memcached/engine.h])
AS_IF([test "x$ac_cv_header_memcached_engine_h" = "xno"],
      [AC_MSG_ERROR([You need to install the engine interface to build
                     engines.])])


# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_INT64_T
AC_TYPE_SIZE_T
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT64_T
AC_TYPE_UINT8_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_CHECK_FUNCS([memset strerror])

AC_CONFIG_FILES(Makefile)
AC_OUTPUT
