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
PKG_CHECK_MODULES([DEPS], [libmicrohttpd >= 0.9])
#AC_SUBST([DEPS_CFLAGS])
#AC_SUBST([DEPS_LIBS])

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h string.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T

# Checks for library functions.

# Output time!
AC_CONFIG_FILES([Makefile
                 doc/Makefile
		 doc/tutorial-ch2/Makefile
		 doc/tutorial-ch2-pedantic/Makefile
		 doc/tutorial-ch2-argv/Makefile
		 doc/tutorial-ch2-time/Makefile
                 src/Makefile
                 test/Makefile])
AC_OUTPUT
