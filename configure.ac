#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([customer_credit_check], [1.0], [])
AC_CONFIG_SRCDIR([src/main.cpp])
#AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE
# Checks for programs.
AC_PROG_CXX
AC_PROG_CC

# Checks for libraries.
AC_PROG_RANLIB
# Checks for libraries. -DBOOST_ASIO_ENABLE_HANDLER_TRACKING
CXXFLAGS="-std=c++11 -pg -O3 -Isrc -Iinclude -Werror -lboost_program_options -lboost_filesystem -lboost_coroutine -lboost_system -lboost_thread -lpthread -lboost_context -lboost_date_time -lboost_log_setup -lboost_log -lssl -lcrypto -lboost_regex -lcurl -lboost_timer -lmysqlclient_r -DBUILD_SSL"
SUBDIRS = src include
# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_SIZE_T

# Checks for library functions.
AC_CHECK_FUNCS([socket])
AC_CONFIG_FILES([Makefile])
AC_OUTPUT
