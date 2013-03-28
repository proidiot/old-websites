#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.68])
AC_INIT([websites], [0.1a], [charlie@stuphlabs.com])
AC_CONFIG_SRCDIR([src/main.c])
AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE([-Wall -Werror])

# Checks for programs.
AC_PROG_CC
AC_PROG_INSTALL
AC_PROG_MAKE_SET

# Checks for libraries.
AC_CHECK_LIB([m], [ceil])
AC_CHECK_LIB([Judy], [JudySLGet])
PKG_CHECK_MODULES([DEPS], [libmicrohttpd >= 0.9])
#AC_SUBST([DEPS_CFLAGS])
#AC_SUBST([DEPS_LIBS])

# Checks for header files.
AC_CHECK_HEADERS([arpa/inet.h fcntl.h netinet/in.h stdlib.h string.h sys/socket.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([inet_ntoa stpcpy strnlen])

AC_ARG_ENABLE(debug,
AS_HELP_STRING([--enable-debug],
               [enable debugging, default: no]),
[case "${enableval}" in
             yes) AC_DEFINE([DEBUG], [1], [Enable debug mode])
	     	  debug=true ;;
             no)  debug=false ;;
             *)   AC_MSG_ERROR([bad value ${enableval} for --enable-debug]) ;;
esac],
[debug=false])
AM_CONDITIONAL(DEBUG, test x"$debug" = x"true")

AC_ARG_ENABLE(tutorial,
AS_HELP_STRING([--enable-tutorial],
               [enable tutorial examples, default: no]),
[case "${enableval}" in
             yes) tutorial=true ;;
             no)  tutorial=false ;;
             *)   AC_MSG_ERROR([bad value ${enableval} for --enable-tutorial]) ;;
esac],
[tutorial=false])
AM_CONDITIONAL(TUTORIAL, test x"$tutorial" = x"true")

# Output time!
AC_CONFIG_FILES([Makefile
                 doc/Makefile
		 doc/tutorial-ch2/Makefile
		 doc/tutorial-ch2-pedantic/Makefile
		 doc/tutorial-ch2-argv/Makefile
		 doc/tutorial-ch2-time/Makefile
		 doc/tutorial-ch3/Makefile
		 doc/tutorial-ch3-pages/Makefile
		 doc/tutorial-ch3-ipaddr/Makefile
		 doc/tutorial-ch4/Makefile
		 doc/tutorial-ch4-sleep/Makefile
		 doc/tutorial-ch4-timer/Makefile
		 doc/tutorial-ch5/Makefile
		 doc/tutorial-ch5-ipblock/Makefile
                 src/Makefile
                 test/Makefile])
AC_OUTPUT
