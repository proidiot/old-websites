
if TUTORIAL

noinst_PROGRAMS = mhd-example

if DEBUG
MORE_LIBS =
AM_CFLAGS = -include config.h -g3 -ggdb -O0 $(DEPS_CFLAGS)
mhd_example_SOURCES = main.c \
		      answer.c \
		      bad_method.c \
		      method_options.c \
		      not_found.c \
		      server_error.c \
		      debug.c
else
MORE_LIBS =
AM_CFLAGS = -include config.h $(DEPS_CFLAGS)
mhd_example_SOURCES = main.c \
		      answer.c \
		      bad_method.c \
		      method_options.c \
		      not_found.c \
		      server_error.c
endif

endif

LIBS = $(DEPS_LIBS) -lm -lJudy $(MORE_LIBS)

